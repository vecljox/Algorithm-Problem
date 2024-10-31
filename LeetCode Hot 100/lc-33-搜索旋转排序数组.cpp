// 先二分找到最小值，然后根据target是在左半段还是右半段再进行二分，注意最后判断nums[l]是否和target相等时必须填的是l，因为如果数组是单调的，填r可能导致越界（r=-1）
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int l = 0, r = n - 1;
        while (l < r) {
            int mid = l + r >> 1;
            if (nums[mid] <= nums.back())
                r = mid;
            else
                l = mid + 1;
        }
        if (target <= nums.back())
            r = n - 1;
        else
            l = 0, --r;
        while (l < r) {
            int mid = l + r >> 1;
            if (nums[mid] >= target)
                r = mid;
            else
                l = mid + 1;
        }
        return nums[l] == target ? l : -1;
    }
};
