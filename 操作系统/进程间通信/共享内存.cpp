// shared_memory_example.cpp
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// 定义共享数据结构
struct shared_data
{
    int counter;
    char message[100];
};

int main()
{
    key_t key;
    int shmid;

    // 生成唯一键值，确保"shmfile"存在
    key = ftok("shmfile", 65);
    if (key == -1)
    {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // 创建共享内存段，大小为shared_data结构体大小
    shmid = shmget(key, sizeof(shared_data), IPC_CREAT | 0666);
    if (shmid == -1)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        // 删除共享内存段
        shmctl(shmid, IPC_RMID, NULL);
        exit(EXIT_FAILURE);
    }

    if (pid > 0)
    {
        // 父进程：写入共享内存
        // 附加共享内存到父进程地址空间
        void *shmem = shmat(shmid, NULL, 0);
        if (shmem == (void *)-1)
        {
            perror("shmat");
            // 删除共享内存段
            shmctl(shmid, IPC_RMID, NULL);
            exit(EXIT_FAILURE);
        }

        shared_data *data = static_cast<shared_data *>(shmem);

        // 初始化数据
        data->counter = 42;
        strncpy(data->message, "Hello from parent via shared memory!", sizeof(data->message));
        data->message[sizeof(data->message) - 1] = '\0'; // 确保字符串终止

        std::cout << "父进程已写入共享内存。" << std::endl;

        // 分离共享内存
        if (shmdt(shmem) == -1)
        {
            perror("shmdt");
            // 删除共享内存段
            shmctl(shmid, IPC_RMID, NULL);
            exit(EXIT_FAILURE);
        }

        // 等待子进程完成
        wait(NULL);

        // 删除共享内存段
        if (shmctl(shmid, IPC_RMID, NULL) == -1)
        {
            perror("shmctl");
            exit(EXIT_FAILURE);
        }

        std::cout << "父进程删除共享内存段，退出。" << std::endl;
    }
    else
    {
        // 子进程：读取共享内存
        // 给父进程一些时间确保数据已写入
        sleep(1);

        // 附加共享内存到子进程地址空间
        void *shmem = shmat(shmid, NULL, 0);
        if (shmem == (void *)-1)
        {
            perror("shmat");
            exit(EXIT_FAILURE);
        }

        shared_data *data = static_cast<shared_data *>(shmem);

        // 读取数据
        std::cout << "子进程读取共享内存中的数据:" << std::endl;
        std::cout << "Counter: " << data->counter << std::endl;
        std::cout << "Message: " << data->message << std::endl;

        // 分离共享内存
        if (shmdt(shmem) == -1)
        {
            perror("shmdt");
            exit(EXIT_FAILURE);
        }

        std::cout << "子进程分离共享内存，退出。" << std::endl;
    }

    return 0;
}
