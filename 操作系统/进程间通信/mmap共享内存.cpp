#include <cstring>
#include <fcntl.h> /* For O_* constants */
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <sys/wait.h>
#include <unistd.h>

struct SharedData
{
    int number;
    char message[256];
};

int main()
{
    const char *shm_name = "/my_shared_memory";
    const size_t SIZE = sizeof(SharedData);

    // 创建共享内存对象
    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1)
    {
        std::cerr << "shm_open failed: " << strerror(errno) << std::endl;
        return 1;
    }

    // 配置共享内存大小
    if (ftruncate(shm_fd, SIZE) == -1)
    {
        std::cerr << "ftruncate failed: " << strerror(errno) << std::endl;
        shm_unlink(shm_name);
        return 1;
    }

    // 映射共享内存
    void *ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED)
    {
        std::cerr << "mmap failed: " << strerror(errno) << std::endl;
        shm_unlink(shm_name);
        return 1;
    }

    // 关闭文件描述符，因为已经映射到内存
    close(shm_fd);

    SharedData *data = static_cast<SharedData *>(ptr);

    pid_t pid = fork();
    if (pid < 0)
    {
        std::cerr << "fork failed: " << strerror(errno) << std::endl;
        munmap(ptr, SIZE);
        shm_unlink(shm_name);
        return 1;
    }
    else if (pid == 0)
    {
        // 子进程
        // 打开共享内存（在 fork 后，子进程已继承映射）
        SharedData *child_data = data;

        // 等待父进程写入数据（简单的 sleep）
        sleep(1);

        std::cout << "子进程读取数据:\n";
        std::cout << "Number: " << child_data->number << std::endl;
        std::cout << "Message: " << child_data->message << std::endl;

        // 子进程可以修改共享数据（可选）
        child_data->number += 100;
        strcat(child_data->message, " - Modified by child");

        // 解除映射
        munmap(ptr, SIZE);
        exit(0);
    }
    else
    {
        // 父进程
        // 向共享内存写入数据
        data->number = 42;
        strcpy(data->message, "Hello from parent");

        std::cout << "父进程写入数据到共享内存。\n";

        // 等待子进程完成
        wait(NULL);

        // 读取子进程修改后的数据
        std::cout << "父进程读取修改后的数据:\n";
        std::cout << "Number: " << data->number << std::endl;
        std::cout << "Message: " << data->message << std::endl;

        // 解除映射
        munmap(ptr, SIZE);

        // 删除共享内存对象
        shm_unlink(shm_name);
    }

    return 0;
}
