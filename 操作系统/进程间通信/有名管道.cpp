// named_pipe_fork.cpp
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

const char *fifoPath = "/tmp/my_fork_fifo";

int main()
{
    // 创建有名管道
    if (mkfifo(fifoPath, 0666) == -1)
    {
        perror("mkfifo");
        // 如果FIFO已存在则忽略错误
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid > 0)
    {
        // 父进程：写数据
        int fd = open(fifoPath, O_WRONLY);
        if (fd == -1)
        {
            perror("open write");
            return 1;
        }

        const char *message = "Hello from parent via FIFO!";
        write(fd, message, strlen(message) + 1);
        std::cout << "父进程已发送消息。\n";

        close(fd);
        wait(NULL); // 等待子进程结束
    }
    else
    {
        // 子进程：读数据
        int fd = open(fifoPath, O_RDONLY);
        if (fd == -1)
        {
            perror("open read");
            return 1;
        }

        char buffer[256];
        ssize_t bytesRead = read(fd, buffer, sizeof(buffer));
        if (bytesRead > 0)
        {
            std::cout << "子进程接收到消息：" << buffer << std::endl;
        }
        else
        {
            std::cerr << "子进程读取错误或无数据。" << std::endl;
        }

        close(fd);
    }

    // 删除有名管道
    unlink(fifoPath);

    return 0;
}
