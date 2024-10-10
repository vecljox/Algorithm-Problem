class Solution {
public:
    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        vector<int> tmp(n);
        return mergeSort(nums, tmp, 0, n - 1);
    }

    int mergeSort(vector<int>& nums, vector<int>& tmp, int l, int r) {
        if (l >= r)
            return 0;

        int mid = (l + r) / 2;
        int res =
            mergeSort(nums, tmp, l, mid) + mergeSort(nums, tmp, mid + 1, r);
        int j = mid + 1;
        for (int i = l; i <= mid; ++i) {
            while (j <= r && (long)nums[i] > (long)2 * nums[j])
                ++j;

            res += (j - (mid + 1));
        }
        int i = l;
        j = mid + 1;
        int pos = l;
        while (i <= mid && j <= r) {
            if (nums[i] <= nums[j]) {
                tmp[pos++] = nums[i++];
            } else {
                tmp[pos++] = nums[j++];
            }
        }
        for (int k = i; k <= mid; ++k) {
            tmp[pos++] = nums[k];
        }
        for (int k = j; k <= r; ++k) {
            tmp[pos++] = nums[k];
        }
        copy(tmp.begin() + l, tmp.begin() + r + 1, nums.begin() + l);
        return res;
    }
};
