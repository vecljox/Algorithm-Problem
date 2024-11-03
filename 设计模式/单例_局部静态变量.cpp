#include <iostream>
// 线程安全（在 C++11 及以后）
// 自动管理生命周期，无需手动删除
class Singleton
{
public:
	static Singleton* getInstance()
	{
		static Singleton instance;
		return &instance;
	}

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	void doSomeOperation()	const
	{
		std::cout << m_string << " do Some Operation\n";
	}

private:
	std::string m_string;
	Singleton() {
		m_string = "test";
		std::cout << "Singleton created!\n";
	};
	~Singleton() {
		std::cout << "Singleton destroyed!\n";
	}
};

int main()
{
	Singleton::getInstance()->doSomeOperation();
	Singleton::getInstance()->doSomeOperation();
	return 0;
}
