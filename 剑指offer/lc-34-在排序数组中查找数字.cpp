// 套用二分查找2个模版即可，注意下第二个模版的mid要+1
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.empty())
            return {-1, -1};
        int n = nums.size();
        int l = 0, r = n - 1;
        while (l < r) {
            int mid = l + r >> 1;
            if (nums[mid] >= target)
                r = mid;
            else
                l = mid + 1;
        }
        if (nums[l] != target)
            return {-1, -1};
        int start = l;
        l = 0, r = n - 1;
        while (l < r) {
            int mid = l + r + 1 >> 1;
            if (nums[mid] <= target)
                l = mid;
            else
                r = mid - 1;
        }
        return {start, l};
    }
};
