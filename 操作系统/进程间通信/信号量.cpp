#include <cstring>
#include <errno.h>
#include <iostream>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// 定义信号量操作的联合体
union semun {
    int val;               // 用于 SETVAL
    struct semid_ds *buf;  // 用于 IPC_STAT 和 IPC_SET
    unsigned short *array; // 用于 GETALL 和 SETALL
    struct seminfo *__buf; // 用于 Linux 特有的 SEM_INFO
};

int main()
{
    key_t key = ftok("semfile", 65); // 生成一个唯一的键值
    if (key == -1)
    {
        std::cerr << "ftok failed: " << strerror(errno) << std::endl;
        return 1;
    }

    // 创建一个包含1个信号量的信号量集
    int semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1)
    {
        std::cerr << "semget failed: " << strerror(errno) << std::endl;
        return 1;
    }

    // 初始化信号量值为1
    semun sem_union;
    sem_union.val = 1;
    if (semctl(semid, 0, SETVAL, sem_union) == -1)
    {
        std::cerr << "semctl SETVAL failed: " << strerror(errno) << std::endl;
        // 删除信号量集
        semctl(semid, 0, IPC_RMID);
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        std::cerr << "fork failed: " << strerror(errno) << std::endl;
        // 删除信号量集
        semctl(semid, 0, IPC_RMID);
        return 1;
    }
    else if (pid == 0)
    {
        // 子进程
        struct sembuf sem_op;

        // 等待信号量（P 操作）
        sem_op.sem_num = 0;
        sem_op.sem_op = -1; // P 操作
        sem_op.sem_flg = 0;
        if (semop(semid, &sem_op, 1) == -1)
        {
            std::cerr << "子进程 semop P 操作失败: " << strerror(errno) << std::endl;
            exit(1);
        }

        // 临界区
        std::cout << "子进程进入临界区。\n";
        sleep(2); // 模拟处理时间
        std::cout << "子进程离开临界区。\n";

        // 释放信号量（V 操作）
        sem_op.sem_op = 1; // V 操作
        if (semop(semid, &sem_op, 1) == -1)
        {
            std::cerr << "子进程 semop V 操作失败: " << strerror(errno) << std::endl;
            exit(1);
        }

        exit(0);
    }
    else
    {
        // 父进程
        struct sembuf sem_op;

        // 等待信号量（P 操作）
        sem_op.sem_num = 0;
        sem_op.sem_op = -1; // P 操作
        sem_op.sem_flg = 0;
        if (semop(semid, &sem_op, 1) == -1)
        {
            std::cerr << "父进程 semop P 操作失败: " << strerror(errno) << std::endl;
            // 删除信号量集
            semctl(semid, 0, IPC_RMID);
            return 1;
        }

        // 临界区
        std::cout << "父进程进入临界区。\n";
        sleep(2); // 模拟处理时间
        std::cout << "父进程离开临界区。\n";

        // 释放信号量（V 操作）
        sem_op.sem_op = 1; // V 操作
        if (semop(semid, &sem_op, 1) == -1)
        {
            std::cerr << "父进程 semop V 操作失败: " << strerror(errno) << std::endl;
            // 删除信号量集
            semctl(semid, 0, IPC_RMID);
            return 1;
        }

        // 等待子进程结束
        wait(NULL);

        // 删除信号量集
        if (semctl(semid, 0, IPC_RMID) == -1)
        {
            std::cerr << "semctl IPC_RMID 失败: " << strerror(errno) << std::endl;
            return 1;
        }
    }

    return 0;
}
