#include <cstring> // 包含 strlen()
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h> // 包含 wait()
#include <unistd.h>   // 包含 pipe(), fork(), read(), write()

int main()
{
    int fd[2]; // fd[0]: 读端，fd[1]: 写端

    // 创建管道
    if (pipe(fd) == -1)
    {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork(); // 创建子进程

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid > 0)
    {
        // 父进程：写数据到管道
        close(fd[0]); // 关闭读端

        const char *message = "Hello from parent!";
        write(fd[1], message, strlen(message) + 1); // +1 包括终止符

        close(fd[1]); // 关闭写端

        wait(NULL); // 等待子进程结束
    }
    else
    {
        // 子进程：从管道读数据
        close(fd[1]); // 关闭写端

        char buffer[100];
        ssize_t bytesRead = read(fd[0], buffer, sizeof(buffer));
        if (bytesRead > 0)
        {
            std::cout << "Child received message: " << buffer << std::endl;
        }
        else
        {
            std::cerr << "Child: read error or no data." << std::endl;
        }

        close(fd[0]); // 关闭读端
    }

    return 0;
}
