// 这种做法的思想是当左子数组的当前元素小于等于右子数组的当前元素时，左子数组的当前元素会和右子数组中当前元素的左边任一元素构成逆序对，所以增加的逆序对数量为j-(mid+1)
// 关于这个做法的对称思想是当左子数组的当前元素大于于右子数组的当前元素时，左子数组中当前元素的右边任一元素(包含自己本身)会和右子数组中当前元素构成逆序对，所以增加的逆序对数量为mid-i+1，具体代码修改很简单(相比前者可以少写一行更新数对数量的代码)，不再赘述

class Solution {
public:
    int reversePairs(vector<int>& record) {
        int n = record.size();
        vector<int> tmp(n);
        return mergeSort(record, tmp, 0, n - 1);
    }

    int mergeSort(vector<int>& record, vector<int>& tmp, int l, int r) {
        if (l >= r)
            return 0;

        int mid = (l + r) / 2;
        int inv_count =
            mergeSort(record, tmp, l, mid) + mergeSort(record, tmp, mid + 1, r);
        int i = l, j = mid + 1, pos = l;
        while (i <= mid && j <= r) {
            if (record[i] <= record[j]) {
                tmp[pos] = record[i];
                ++i;
                inv_count += (j - (mid + 1));
            } else {
                tmp[pos] = record[j];
                ++j;
            }
            ++pos;
        }
        for (int k = i; k <= mid; ++k) {
            tmp[pos++] = record[k];
            inv_count += (j - (mid + 1));
        }
        for (int k = j; k <= r; ++k) {
            tmp[pos++] = record[k];
        }
        copy(tmp.begin() + l, tmp.begin() + r + 1, record.begin() + l);
        return inv_count;
    }
};
