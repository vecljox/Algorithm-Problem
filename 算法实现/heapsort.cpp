// percDown(下滤)时间复杂度: O(logN)
// percUp(上滤)时间复杂度: O(logN)，平均时间复杂度为O(1)
	
// 插入：将新元素插入到堆末尾，然后上滤
// 删除：将堆顶元素替换为堆尾元素，然后下滤

// 建堆分为自顶向下和自底向上两种
// 自顶向下：向堆末尾不断插入元素然后进行上滤操作，时间复杂度：O(NlogN)
// 自底向上：从最后一个非叶子节点开始到堆顶，下滤每个元素，时间复杂度：O(N)

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
