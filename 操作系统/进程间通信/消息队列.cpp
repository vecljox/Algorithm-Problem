// posix_message_queue_fork.cpp
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <mqueue.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

const char *QUEUE_NAME = "/my_fork_posix_queue";
const int MAX_SIZE = 1024;

int main()
{
    // 定义消息队列属性
    struct mq_attr attr;
    attr.mq_flags = 0;          // 阻塞模式
    attr.mq_maxmsg = 10;        // 最大消息数
    attr.mq_msgsize = MAX_SIZE; // 单个消息的最大大小
    attr.mq_curmsgs = 0;        // 当前消息数

    // 创建消息队列
    mqd_t mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0644, &attr);
    if (mq == (mqd_t)-1)
    {
        perror("mq_open");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        mq_close(mq);
        mq_unlink(QUEUE_NAME);
        exit(1);
    }

    if (pid > 0)
    {
        // 父进程：发送消息
        std::cout << "父进程，子进程PID：" << pid << std::endl;

        // 获取用户输入的消息
        std::cout << "请输入要发送的消息：";
        std::string message;
        std::getline(std::cin, message);

        // 发送消息到队列
        if (mq_send(mq, message.c_str(), message.size() + 1, 0) == -1)
        { // +1 包括终止符
            perror("mq_send");
            mq_close(mq);
            mq_unlink(QUEUE_NAME);
            exit(1);
        }

        std::cout << "父进程已发送消息。\n";

        // 等待子进程结束
        wait(NULL);

        // 关闭并删除消息队列
        mq_close(mq);
        mq_unlink(QUEUE_NAME);
    }
    else
    {
        // 子进程：接收消息
        std::cout << "子进程开始等待接收消息...\n";

        char buffer[MAX_SIZE];
        memset(buffer, 0, sizeof(buffer));

        // 接收消息
        ssize_t bytes_read = mq_receive(mq, buffer, MAX_SIZE, nullptr);
        if (bytes_read >= 0)
        {
            std::cout << "子进程接收到消息：" << buffer << std::endl;
        }
        else
        {
            perror("mq_receive");
        }

        // 子进程关闭消息队列
        mq_close(mq);

        exit(0);
    }

    return 0;
}
