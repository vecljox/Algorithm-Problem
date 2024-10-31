// https://www.acwing.com/solution/content/6386/

// 直接二分
class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            int mid = l + r >> 1;
            if (nums[mid] < nums[r])
                r = mid;
            else if (nums[mid] > nums[r])
                l = mid + 1;
            else
                --r;
        }
        return nums[l];
    }
};

// 先去重再二分
class SolutionB {
public:
    int findMin(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;
        while (r > 0 && nums[0] == nums[r])
            --r;
        int check = nums[r];
        while (l < r) {
            int mid = l + r >> 1;
            if (nums[mid] <= check)
                r = mid;
            else
                l = mid + 1;
        }
        return nums[l];
    }
};
