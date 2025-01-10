#include <iostream>
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int readyA = 1;

void *thread_func1(void *arg)
{
    int n = 50;
    while (n--)
    {
        pthread_mutex_lock(&lock);
        while (!readyA)
        {
            pthread_cond_wait(&cond, &lock);
        }
        std::cout << 'A';
        readyA = 0;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *thread_func2(void *arg)
{
    int n = 50;
    while (n--)
    {
        pthread_mutex_lock(&lock);
        while (readyA)
        {
            pthread_cond_wait(&cond, &lock);
        }
        std::cout << 'B';
        readyA = 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main()
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, &thread_func1, NULL);
    pthread_create(&t2, NULL, &thread_func2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
