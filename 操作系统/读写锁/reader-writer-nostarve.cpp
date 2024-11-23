// 当有写者在等待时阻塞更多的读者防止写者饿死
// 但是当写者完成后无法保证下一个唤醒的是等待的写者（若有的话），还可以优化，对写线程赋予更高优先级，具体见《The Little Book of Semaphores》中 Writer-priority readers-writers solution这一节 

#include <cassert>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#include "Lightswitch.h"

struct rwlock_t {
	Lightswitch readSwitch;
	sem_t roomEmpty;
	sem_t turnstile;
};

void rwlock_init(rwlock_t* rw) {
	sem_init(&rw->roomEmpty, 0, 1);
	sem_init(&rw->turnstile, 0, 1);
}

void rwlock_acquire_readlock(rwlock_t* rw) {
	sem_wait(&rw->turnstile);
	sem_post(&rw->turnstile);

	rw->readSwitch.lock(rw->roomEmpty);
}

void rwlock_release_readlock(rwlock_t* rw) {
	rw->readSwitch.unlock(rw->roomEmpty);
}

void rwlock_acquire_writelock(rwlock_t* rw) {
	sem_wait(&rw->turnstile);
	sem_wait(&rw->roomEmpty);
}

void rwlock_release_writelock(rwlock_t* rw) {
	sem_post(&rw->turnstile);
	sem_post(&rw->roomEmpty);
}

//
// Don't change the code below (just use it!)
// 

int loops;
int value = 0;

rwlock_t lock;

void* reader(void* arg) {
	int i;
	for (i = 0; i < loops; i++) {
		rwlock_acquire_readlock(&lock);
		printf("read %d\n", value);
		rwlock_release_readlock(&lock);
	}
	return NULL;
}

void* writer(void* arg) {
	int i;
	for (i = 0; i < loops; i++) {
		rwlock_acquire_writelock(&lock);
		value++;
		printf("write %d\n", value);
		rwlock_release_writelock(&lock);
	}
	return NULL;
}

int main(int argc, char* argv[]) {
	assert(argc == 4);
	int num_readers = atoi(argv[1]);
	int num_writers = atoi(argv[2]);
	loops = atoi(argv[3]);

	pthread_t pr[num_readers], pw[num_writers];

	rwlock_init(&lock);

	printf("begin\n");

	int i;
	for (i = 0; i < num_readers; i++)
		pthread_create(&pr[i], NULL, reader, NULL);
	for (i = 0; i < num_writers; i++)
		pthread_create(&pw[i], NULL, writer, NULL);

	for (i = 0; i < num_readers; i++)
		pthread_join(pr[i], NULL);
	for (i = 0; i < num_writers; i++)
		pthread_join(pw[i], NULL);

	printf("end: value %d\n", value);

	return 0;
}
