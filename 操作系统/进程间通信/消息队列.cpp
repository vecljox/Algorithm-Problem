// parent_child_msgqueue.cpp
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

struct message
{
    long mtype;
    char mtext[100];
};

int main()
{
    key_t key;
    int msgid;

    // 生成唯一键值
    key = ftok("msgqueuefile", 65);
    if (key == -1)
    {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // 创建消息队列，权限设置为0666，若不存在则创建
    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1)
    {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        // 删除消息队列
        msgctl(msgid, IPC_RMID, NULL);
        exit(EXIT_FAILURE);
    }

    if (pid > 0)
    {
        // 父进程：发送消息
        message msg;
        msg.mtype = 1;

        std::cout << "父进程请输入要发送的消息: ";
        std::cin.getline(msg.mtext, sizeof(msg.mtext));

        if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) == -1)
        {
            perror("msgsnd");
            // 删除消息队列
            msgctl(msgid, IPC_RMID, NULL);
            exit(EXIT_FAILURE);
        }

        std::cout << "父进程已发送消息。\n";

        // 等待子进程结束
        wait(NULL);

        // 删除消息队列
        if (msgctl(msgid, IPC_RMID, NULL) == -1)
        {
            perror("msgctl");
            exit(EXIT_FAILURE);
        }

        std::cout << "消息队列已删除，父进程退出。" << std::endl;
    }
    else
    {
        // 子进程：接收消息
        message msg;

        std::cout << "子进程等待接收消息..." << std::endl;

        if (msgrcv(msgid, &msg, sizeof(msg.mtext), 1, 0) == -1)
        {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }

        std::cout << "子进程接收到消息: " << msg.mtext << std::endl;

        exit(EXIT_SUCCESS);
    }

    return 0;
}
