// 当有写者在等待时阻塞更多的读者防止写者饿死

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

struct rwlock_t {
	pthread_mutex_t mutex;
	pthread_cond_t readers_ok;
	pthread_cond_t writers_ok;
	int readers;
	int writers;
	int waiting_writers;
};

void rw_lock_init(rwlock_t* rw) {
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
// 共享资源
int shared_data = 0;

// 读写锁
rwlock_t rwlock;

// 模拟读操作
void* reader(void* arg) {
	int id = *(int*)arg;
	for (int i = 0; i < 50; i++) {
		rwlock_acquire_readlock(&rwlock); // 获取读锁
		printf("Reader %d: Read shared_data = %d\n", id, shared_data);
		rwlock_release_readlock(&rwlock); // 释放读锁
		usleep(100000); // 模拟读操作耗时
	}
	return NULL;
}

// 模拟写操作
void* writer(void* arg) {
	int id = *(int*)arg;
	for (int i = 0; i < 50; i++) {
		rwlock_acquire_writelock(&rwlock); // 获取写锁
		shared_data += 1; // 修改共享数据
		printf("Writer %d: Updated shared_data to %d\n", id, shared_data);
		rwlock_release_writelock(&rwlock); // 释放写锁
		usleep(200000); // 模拟写操作耗时
	}
	return NULL;
}

int main() {
	// 初始化读写锁
	rw_lock_init(&rwlock);

	// 创建线程
	pthread_t readers[3], writers[2];
	int reader_ids[3] = { 1, 2, 3 };
	int writer_ids[2] = { 1, 2 };

	// 启动读者线程
	for (int i = 0; i < 3; i++) {
		pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
	}

	// 启动写者线程
	for (int i = 0; i < 2; i++) {
		pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
	}

	// 等待所有线程完成
	for (int i = 0; i < 3; i++) {
		pthread_join(readers[i], NULL);
	}
	for (int i = 0; i < 2; i++) {
		pthread_join(writers[i], NULL);
	}

	return 0;
}
