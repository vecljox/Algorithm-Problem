#include <iostream>
#include <pthread.h>
#include <semaphore.h>

sem_t sem_A;
sem_t sem_B;

void *thread_func1(void *arg)
{
    int n = 50;
    while (n--)
    {
        sem_wait(&sem_A);
        std::cout << 'A';
        sem_post(&sem_B);
    }
    return NULL;
}

void *thread_func2(void *arg)
{
    int n = 50;
    while (n--)
    {
        sem_wait(&sem_B);
        std::cout << 'B';
        sem_post(&sem_A);
    }
    return NULL;
}

int main()
{
    sem_init(&sem_A, 0, 1);
    sem_init(&sem_B, 0, 0);
    pthread_t t1, t2;
    pthread_create(&t1, NULL, &thread_func1, NULL);
    pthread_create(&t2, NULL, &thread_func2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    sem_destroy(&sem_A);
    sem_destroy(&sem_B);
    return 0;
}
