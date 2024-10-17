#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

void bubbleSort(std::vector<int>& arr)
{
	for (int i = 0; i < arr.size() - 1; ++i)
	{
		bool swapped = false;
		for (int j = 0; j < arr.size() - i - 1; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				std::swap(arr[j], arr[j + 1]);
				swapped = true;
			}
		}
		if (!swapped)	break;
	}
}

// // 自己做的，记录最后一次交换的位置，可以进一步优化，记录第一次交换的位置
// void bubbleSort(std::vector<int>& arr)
// {
// 	int end = arr.size() - 1;
// 	while (end)
// 	{
// 		int tmp = end;
// 		end = 0;
// 		for (int i = 0; i < tmp; ++i)
// 		{
// 			if (arr[i] > arr[i + 1])
// 			{
// 				std::swap(arr[i], arr[i + 1]);
// 				end = i;
// 			}
// 		}
// 	}
// }

int main() {
	std::vector<int> v{ 3,5,2,1,4 };
	bubbleSort(v);
	for (auto i : v)
	{
		std::cout << i << '\t';
	}
	return 0;
}
