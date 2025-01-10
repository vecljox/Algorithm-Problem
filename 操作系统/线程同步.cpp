#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define THREAD_COUNT 5

pthread_barrier_t barrier;

void *thread_func(void *arg)
{
    int thread_num = *(int *)arg;
    printf("Thread %d: Before barrier\n", thread_num);

    pthread_barrier_wait(&barrier);

    printf("Thread %d: After barrier\n", thread_num);
    return NULL;
}

int main()
{
    pthread_t threads[THREAD_COUNT];
    int thread_nums[THREAD_COUNT];

    // 初始化屏障，等待5个线程
    pthread_barrier_init(&barrier, NULL, THREAD_COUNT);

    // 创建线程
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        thread_nums[i] = i;
        pthread_create(&threads[i], NULL, thread_func, &thread_nums[i]);
    }

    // 等待线程结束
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // 销毁屏障
    pthread_barrier_destroy(&barrier);

    return 0;
}
