// critical section是windows专用的线程同步机制，相比于mutex是一种更轻量级的同步机制，仅在同一进程内有效。
// 用户态的轻量级锁，当没有竞争时开销很低，当线程竞争导致阻塞时会切换到内核态，适合频繁访问的场景

#include <windows.h>
#include <iostream>
#include <thread>

CRITICAL_SECTION criticalSection; // 定义临界区对象
int sharedResource = 0;          // 共享资源

void threadFunction(int threadID) {
    for (int i = 0; i < 5; ++i) {
        // 进入临界区
        EnterCriticalSection(&criticalSection);
        std::cout << "Thread " << threadID << " entering critical section.\n";
        ++sharedResource; // 修改共享资源
        std::cout << "Thread " << threadID << " incremented sharedResource to " << sharedResource << ".\n";
        std::cout << "Thread " << threadID << " leaving critical section.\n";
        // 离开临界区
        LeaveCriticalSection(&criticalSection);

        // 模拟其他工作
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    // 初始化临界区
    InitializeCriticalSection(&criticalSection);

    // 创建线程
    std::thread t1(threadFunction, 1);
    std::thread t2(threadFunction, 2);

    // 等待线程结束
    t1.join();
    t2.join();

    // 删除临界区
    DeleteCriticalSection(&criticalSection);

    std::cout << "Final sharedResource value: " << sharedResource << std::endl;
    return 0;
}
