#include <iostream>
#include <mutex>
#include <memory>

class Singleton {
public:
	static std::shared_ptr<Singleton>  getInstance() {
		if (m_instance == nullptr) {
			m_mutex.lock();
			if (m_instance == nullptr) {
				m_instance = std::shared_ptr<Singleton>(new Singleton(), [](Singleton* p) {
					delete p;
					});
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

	static std::shared_ptr<Singleton> m_instance;
	static std::mutex m_mutex;
};

std::shared_ptr<Singleton> Singleton::m_instance = nullptr;
std::mutex Singleton::m_mutex;

int main() {
	Singleton::getInstance()->some_method();
	Singleton::getInstance()->some_method();
	return 0;
}
