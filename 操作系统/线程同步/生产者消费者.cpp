#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define MAX 10
const int loops = 20;

int buffer[MAX];
int fill_ptr = 0;
int use_ptr = 0;
int count = 0;

void put(int value)
{
    buffer[fill_ptr] = value;
    fill_ptr = (fill_ptr + 1) % MAX;
    count++;
}

int get()
{
    int tmp = buffer[use_ptr];
    use_ptr = (use_ptr + 1) % MAX;
    count--;
    return tmp;
}
pthread_cond_t empty, fill;
pthread_mutex_t mutex;

void *producer(void *arg)
{
    int i;
    for (i = 0; i < loops; i++)
    {
        pthread_mutex_lock(&mutex);            // p1
        while (count == MAX)                   // p2
            pthread_cond_wait(&empty, &mutex); // p3
        put(i);                                // p4
        pthread_cond_signal(&fill);            // p5
        pthread_mutex_unlock(&mutex);          // p6
    }
}
void *consumer(void *arg)
{
    int i;
    for (i = 0; i < loops; i++)
    {
        pthread_mutex_lock(&mutex);           // c1
        while (count == 0)                    // c2
            pthread_cond_wait(&fill, &mutex); // c3
        int tmp = get();                      // c4
        pthread_cond_signal(&empty);          // c5
        pthread_mutex_unlock(&mutex);         // c6
        printf("%d\n", tmp);
    }
}

int main()
{
    pthread_t prod, cons;

    // 初始化互斥锁和条件变量
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_cond_init(&fill, NULL);

    // 创建生产者和消费者线程
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // 等待线程结束
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // 销毁互斥锁和条件变量
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&empty);
    pthread_cond_destroy(&fill);
    return 0;
}
