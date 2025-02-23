// 最基础的读写锁版本，需要对写者饿死的情况进行优化

#include <cassert>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _rwlock_t {
	sem_t lock;        // binary semaphore (basic lock)
	sem_t roomEmpty;   // allow ONE writer/MANY readers
	int readers;       // #readers in critical section
} rwlock_t;

void rwlock_init(rwlock_t* rw) {
	rw->readers = 0;
	sem_init(&rw->lock, 0, 1);
	sem_init(&rw->roomEmpty, 0, 1);
}

void rwlock_acquire_readlock(rwlock_t* rw) {
	sem_wait(&rw->lock);
	rw->readers++;
	if (rw->readers == 1) // first reader gets roomEmpty
		sem_wait(&rw->roomEmpty);
	sem_post(&rw->lock);
}

void rwlock_release_readlock(rwlock_t* rw) {
	sem_wait(&rw->lock);
	rw->readers--;
	if (rw->readers == 0) // last reader lets it go
		sem_post(&rw->roomEmpty);
	sem_post(&rw->lock);
}

void rwlock_acquire_roomEmpty(rwlock_t* rw) {
	sem_wait(&rw->roomEmpty);
}

void rwlock_release_roomEmpty(rwlock_t* rw) {
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
		rwlock_acquire_roomEmpty(&lock);
		value++;
		printf("write %d\n", value);
		rwlock_release_roomEmpty(&lock);
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
