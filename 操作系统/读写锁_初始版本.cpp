#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

typedef struct _rwlock_t {
	sem_t lock;        // binary semaphore (basic lock)
	sem_t writelock;   // allow ONE writer/MANY readers
	int readers;       // #readers in critical section
} rwlock_t;

void rwlock_init(rwlock_t* rw) {
	rw->readers = 0;
	sem_init(&rw->lock, 0, 1);
	sem_init(&rw->writelock, 0, 1);
}

void rwlock_acquire_readlock(rwlock_t* rw) {
	sem_wait(&rw->lock);
	rw->readers++;
	if (rw->readers == 1) // first reader gets writelock
		sem_wait(&rw->writelock);
	sem_post(&rw->lock);
}

void rwlock_release_readlock(rwlock_t* rw) {
	sem_wait(&rw->lock);
	rw->readers--;
	if (rw->readers == 0) // last reader lets it go
		sem_post(&rw->writelock);
	sem_post(&rw->lock);
}

void rwlock_acquire_writelock(rwlock_t* rw) {
	sem_wait(&rw->writelock);
}

void rwlock_release_writelock(rwlock_t* rw) {
	sem_post(&rw->writelock);
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
	rwlock_init(&rwlock);

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

