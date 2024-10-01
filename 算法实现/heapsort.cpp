#include <iostream>
#include <vector>

inline int leftChild(int i)
{
	return 2 * i + 1;
}

template <typename T>
void percDown(std::vector<T>& a, int i, int n)
{
	int child;
	T tmp = std::move(a[i]);
	for (; leftChild(i) < n; i = child)
	{
		child = leftChild(i);
		if (child != n - 1 && a[child] < a[child + 1])
			++child;
		if (tmp < a[child])
			a[i] = std::move(a[child]);
		else
			break;
	}
	a[i] = std::move(tmp);
}


template <typename T>
void heapsort(std::vector<T>& a)
{
	for (int i = a.size() / 2 - 1; i >= 0; --i)
		percDown(a, i, a.size());

	for (int j = a.size() - 1; j > 0; --j)
	{
		std::swap(a[0], a[j]);
		percDown(a, 0, j);
	}
}


int main() {
	std::vector<int> vec = { 10, 20, 5, 30, 15 };

	heapsort(vec);

	for (auto v : vec)
	{
		std::cout << v << '\t';
	}

	return 0;
}
