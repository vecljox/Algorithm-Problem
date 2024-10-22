#include <iostream>

class Singleton
{
public:
	static Singleton* getInstance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new Singleton();
		}
		return m_pInstance;
	}

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	void doSomeOperation()	const
	{
		std::cout << m_string << " do Some Operation\n";
	}

private:
	static Singleton* m_pInstance;
	std::string m_string;
	Singleton() {
		m_string = "test";
		std::cout << "Singleton created!\n";
	};
	~Singleton() {
		std::cout << "Singleton destroyed!\n";
	}
};

Singleton* Singleton::m_pInstance = nullptr;

int main()
{
	Singleton::getInstance()->doSomeOperation();
	return 0;
}

