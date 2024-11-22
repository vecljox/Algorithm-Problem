#include <iostream>
#include <pthread.h>

#define MAX 8
#define LOOPS 64

int buffer[MAX];
int fill_ptr = 0;
int use_ptr = 0;
int count = 0;

void put(int value)
{
	buffer[fill_ptr] = value;
	fill_ptr = (fill_ptr + 1) % MAX;
	++count;
}

int get()
{
	int tmp = buffer[use_ptr];
	use_ptr = (use_ptr + 1) % MAX;
	--count;
	return tmp;
}

pthread_cond_t empty = PTHREAD_COND_INITIALIZER, fill = PTHREAD_COND_INITIALIZER;
pthread_mutex_t  mutex = PTHREAD_MUTEX_INITIALIZER;

void* producer(void* arg)
{
	for (int i = 0; i < LOOPS; ++i)
	{
		pthread_mutex_lock(&mutex);
		while (count == MAX)
		{
			pthread_cond_wait(&empty, &mutex);
		}
		put(i);
		pthread_cond_signal(&fill);
		pthread_mutex_unlock(&mutex);
	}
}

void* consumer(void* arg)
{
	for (int i = 0; i < LOOPS; ++i)
	{
		pthread_mutex_lock(&mutex);
		while (count == 0)
		{
			pthread_cond_wait(&fill, &mutex);
		}
		int tmp = get();
		pthread_cond_signal(&empty);
		pthread_mutex_unlock(&mutex);
		std::cout << "consumed value: " << tmp << '\n';
	}
}

int main() {
	pthread_t p1, p2, c1, c2;
	pthread_create(&p1, NULL, producer, NULL);
	pthread_create(&c1, NULL, consumer, NULL);
	//pthread_create(&p2, NULL, producer, NULL);
	//pthread_create(&c2, NULL, consumer, NULL);
	pthread_join(p1, NULL);
	pthread_join(c1, NULL);
	//pthread_join(p2, NULL);
	//pthread_join(c2, NULL);
	printf("parent: end\n");
	return 0;
}
