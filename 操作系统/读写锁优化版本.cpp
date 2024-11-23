// 当有写者在等待时阻塞更多的读者防止写者饿死

#include <cassert>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

struct rwlock_t {
	pthread_mutex_t mutex;
	pthread_cond_t readers_ok;
	pthread_cond_t writers_ok;
	int readers;
	int writers;
	int waiting_writers;
};

void rwlock_init(rwlock_t* rw) {
	pthread_mutex_init(&rw->mutex, NULL);
	pthread_cond_init(&rw->readers_ok, NULL);
	pthread_cond_init(&rw->writers_ok, NULL);
	rw->readers = 0;
	rw->writers = 0;
	rw->waiting_writers = 0;
}

void rwlock_acquire_readlock(rwlock_t* rw) {
	pthread_mutex_lock(&rw->mutex);
	while (rw->writers > 0 || rw->waiting_writers > 0) {
		pthread_cond_wait(&rw->readers_ok, &rw->mutex);
	}
	rw->readers++;
	pthread_mutex_unlock(&rw->mutex);
}

void rwlock_release_readlock(rwlock_t* rw) {
	pthread_mutex_lock(&rw->mutex);
	rw->readers--;
	if (rw->readers == 0 && rw->waiting_writers > 0) {
		pthread_cond_signal(&rw->writers_ok);
	}
	pthread_mutex_unlock(&rw->mutex);
}

void rwlock_acquire_writelock(rwlock_t* rw) {
	pthread_mutex_lock(&rw->mutex);
	rw->waiting_writers++;
	while (rw->readers > 0 || rw->writers > 0) {
		pthread_cond_wait(&rw->writers_ok, &rw->mutex);
	}
	rw->waiting_writers--;
	rw->writers++;
	pthread_mutex_unlock(&rw->mutex);
}

void rwlock_release_writelock(rwlock_t* rw) {
	pthread_mutex_lock(&rw->mutex);
	rw->writers--;
	if (rw->waiting_writers > 0) {
		pthread_cond_signal(&rw->writers_ok);
	}
	else {
		pthread_cond_broadcast(&rw->readers_ok);
	}
	pthread_mutex_unlock(&rw->mutex);
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
