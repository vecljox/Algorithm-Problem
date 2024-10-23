#include <iostream>
#include <memory>

class Singleton {
private:
	Singleton() {
		std::cout << "Singleton created\n";
	}

	~Singleton() {
		std::cout << "Singleton destroyed\n";
	}

	static std::shared_ptr<Singleton> instance;

public:
	static std::shared_ptr<Singleton> get_instance() {
		if (instance == nullptr) {
			instance = std::shared_ptr<Singleton>(new Singleton(), [](Singleton* p) {
				delete p; // 自定义删除器，能访问私有析构函数
				});
		}
		return instance;
	}

	void some_method() {
		std::cout << "Singleton method called." << std::endl;
	}
};

std::shared_ptr<Singleton> Singleton::instance = nullptr;

int main() {
	std::shared_ptr<Singleton> s1 = Singleton::get_instance();
	std::shared_ptr<Singleton> s2 = Singleton::get_instance();

	s1->some_method();
	s2->some_method();

	return 0;
}
