#include <iostream>
#include <stack>
#include <vector>

void quickSort(std::vector<int>& arr, int left, int right)
{
	if (left >= right)	return;
	int i = left - 1;
	int j = right + 1;
	int p = arr[left + right >> 1];
	while (i < j)
	{
		do ++i; while (arr[i] < p);
		do --j; while (arr[j] > p);
		if (i < j)	std::swap(arr[i], arr[j]);
		else quickSort(arr, left, j), quickSort(arr, j + 1, right);
	}
}


namespace Normal
{
	int partition(std::vector<int>& arr, int low, int high) {

		// Choose the pivot
		int pivot = arr[high];

		// Index of smaller element and indicates 
		// the right position of pivot found so far
		int i = low - 1;

		// Traverse arr[;ow..high] and move all smaller
		// elements on left side. Elements from low to 
		// i are smaller after every iteration
		for (int j = low; j <= high - 1; j++) {
			if (arr[j] < pivot) {
				i++;
				std::swap(arr[i], arr[j]);
			}
		}

		// Move pivot after smaller elements and
		// return its position
		std::swap(arr[i + 1], arr[high]);
		return i + 1;
	}

	// The QuickSort function implementation
	void quickSort(std::vector<int>& arr, int low, int high) {

		if (low < high) {

			// pi is the partition return index of pivot
			int pi = partition(arr, low, high);

			// Recursion calls for smaller elements
			// and greater or equals elements
			quickSort(arr, low, pi - 1);
			quickSort(arr, pi + 1, high);
		}
	}
}

namespace NonRecursion
{
	void swap(int& a, int& b) {
		int temp = a;
		a = b;
		b = temp;
	}

	int partition(std::vector<int>& arr, int low, int high) {
		int pivot = arr[high]; // 选择最后一个元素作为枢轴
		int i = low - 1; // i 是小于枢轴元素的最后一个元素的索引

		for (int j = low; j < high; ++j) {
			if (arr[j] < pivot) {
				++i;
				swap(arr[i], arr[j]);
			}
		}
		swap(arr[i + 1], arr[high]);
		return i + 1; // 返回枢轴的正确位置
	}

	void quickSortIterative(std::vector<int>& arr, int low, int high) {
		std::stack<int> stack;

		// 初始范围入栈
		stack.push(low);
		stack.push(high);

		while (!stack.empty()) {
			// 取出栈顶的 high 和 low
			high = stack.top(); stack.pop();
			low = stack.top(); stack.pop();

			// 对当前区间进行划分
			int pivotIndex = partition(arr, low, high);

			// 如果左侧有元素，入栈左侧范围
			if (pivotIndex - 1 > low) {
				stack.push(low);
				stack.push(pivotIndex - 1);
			}

			// 如果右侧有元素，入栈右侧范围
			if (pivotIndex + 1 < high) {
				stack.push(pivotIndex + 1);
				stack.push(high);
			}
		}
	}
}

namespace Median
{
	/**
 * Internal insertion sort routine for subarrays
 * that is used by quicksort.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
	template <typename Comparable>
	void insertionSort(std::vector<Comparable>& a, int left, int right)
	{
		for (int p = left + 1; p <= right; ++p)
		{
			Comparable tmp = std::move(a[p]);
			int j;

			for (j = p; j > left && tmp < a[j - 1]; --j)
				a[j] = std::move(a[j - 1]);
			a[j] = std::move(tmp);
		}
	}

	/**
 * Return median of left, center, and right.
 * Order these and hide the pivot.
 */
	template <typename Comparable>
	const Comparable& median3(std::vector<Comparable>& a, int left, int right)
	{
		int center = (left + right) / 2;

		if (a[center] < a[left])
			std::swap(a[left], a[center]);
		if (a[right] < a[left])
			std::swap(a[left], a[right]);
		if (a[right] < a[center])
			std::swap(a[center], a[right]);

		// Place pivot at position right - 1
		std::swap(a[center], a[right - 1]);
		return a[right - 1];
	}

	/**
	 * Internal quicksort method that makes recursive calls.
	 * Uses median-of-three partitioning and a cutoff of 10.
	 * a is an array of Comparable items.
	 * left is the left-most index of the subarray.
	 * right is the right-most index of the subarray.
	 */
	template <typename Comparable>
	void quicksort(std::vector<Comparable>& a, int left, int right)
	{
		if (left + 10 <= right)
		{

			//if (left >= right)
			//	return;

			//if (left + 1 == right)
			//{
			//	if (v[left] > v[right])
			//	{
			//		std::swap(v[left], v[right]);
			//	}
			//	return;
			//}


			const Comparable& pivot = median3(a, left, right);

			// Begin partitioning
			int i = left, j = right - 1;
			for (; ; )
			{
				while (a[++i] < pivot) {}
				while (pivot < a[--j]) {}
				if (i < j)
					std::swap(a[i], a[j]);
				else
					break;
			}

			std::swap(a[i], a[right - 1]);  // Restore pivot

			quicksort(a, left, i - 1);     // Sort small elements
			quicksort(a, i + 1, right);    // Sort large elements
		}
		else  // Do an insertion sort on the subarray
			insertionSort(a, left, right);
	}

	/**
	 * Quicksort algorithm (driver).
	 */
	template <typename Comparable>
	void quicksort(std::vector<Comparable>& a)
	{
		quicksort(a, 0, a.size() - 1);
	}
}


int main() {
	std::vector<int> arr = { 8 ,1 ,4, 9 ,0 ,3 ,5 ,2 ,7 ,6 };
	//std::vector<int> arr = { 2,2,2,2 };
	int n = arr.size();
	Median::quicksort(arr, 0, n - 1);
	std::cout << "Sorted array: ";
	for (int i = 0; i < n; i++) {
		std::cout << arr[i] << " ";
	}
	return 0;
}



