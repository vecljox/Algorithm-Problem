// signal_example.cpp
#include <csignal>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// 全局变量用于信号处理
volatile sig_atomic_t signal_received = 0;

// 信号处理函数
void handle_sigusr1(int sig)
{
    std::cout << "子进程收到SIGUSR1信号，信号编号：" << sig << std::endl;
    signal_received = 1; // 设置标志位
}

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid > 0)
    {
        // 父进程
        std::cout << "父进程，子进程PID：" << pid << std::endl;

        // 父进程可以执行其他任务，这里简化为sleep
        sleep(2); // 等待2秒

        // 向子进程发送SIGUSR1信号
        std::cout << "父进程发送SIGUSR1信号给子进程。" << std::endl;
        if (kill(pid, SIGUSR1) == -1)
        {
            perror("kill");
            return 1;
        }

        // 等待子进程结束
        wait(NULL);
        std::cout << "子进程已结束，父进程退出。" << std::endl;
    }
    else
    {
        // 子进程

        // 设置SIGUSR1信号的处理器
        struct sigaction sa;
        sa.sa_handler = handle_sigusr1;
        sa.sa_flags = 0; // 或者使用SA_RESTART
        sigemptyset(&sa.sa_mask);

        if (sigaction(SIGUSR1, &sa, NULL) == -1)
        {
            perror("sigaction");
            return 1;
        }

        std::cout << "子进程开始等待信号..." << std::endl;

        // 等待信号到来
        while (!signal_received)
        {
            pause(); // 挂起，等待信号
        }

        std::cout << "子进程处理完信号，继续执行其他任务..." << std::endl;

        // 子进程可以执行其他任务，这里简化为sleep
        sleep(1);

        std::cout << "子进程退出。" << std::endl;
        return 0;
    }

    return 0;
}
