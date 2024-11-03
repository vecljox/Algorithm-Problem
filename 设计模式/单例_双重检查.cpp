// 无法保证Singleton析构函数的调用

#include <iostream>
#include <mutex>
#include <memory>

class Singleton {
public:
	static Singleton* getInstance() {
		if (m_instance == nullptr) {
			m_mutex.lock();
			if (m_instance == nullptr) {
				m_instance = new Singleton();
			}
			m_mutex.unlock();
		}
		return m_instance;
	}

	void some_method() {
		std::cout << "Singleton method called." << std::endl;
	}

private:
	Singleton() {
		std::cout << "Singleton created\n";
	}

	~Singleton() {
		std::cout << "Singleton destroyed\n";
	}

	static Singleton* m_instance;
	static std::mutex m_mutex;
};

Singleton* Singleton::m_instance = nullptr;
std::mutex Singleton::m_mutex;

int main() {
	Singleton::getInstance()->some_method();

	return 0;
}
