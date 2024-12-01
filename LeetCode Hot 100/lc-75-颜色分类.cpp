// 双指针法
// 因为是从左往右遍历，当遇到2需要和右边界交换，且交换出来的元素不为1时，需要处理该元素，具体代码表现上为不自增i

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        int l = 0, r = n - 1;
        for (int i = 0; i <= r;) {
            if (nums[i] == 0) {
                swap(nums[i], nums[l]);
                ++l;
                ++i;

            } else if (nums[i] == 2) {
                swap(nums[i], nums[r]);
                // if (nums[i] != 1)
                --r;
            } else {
                ++i;
            }
        }
    }
};
