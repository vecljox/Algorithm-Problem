// 找下一个排列就是从后往前寻找第一个出现降的地方，把这个地方的数字与后边第一个比它大(从右往左数)的的数字交换，再把该位置之后整理为升序。
// https://www.acwing.com/solution/content/103/
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int i = -1;
        for (int j = n - 2; j >= 0; --j) {
            if (nums[j] < nums[j + 1]) {
                i = j;
                break;
            }
        }
        if (i == -1)
            reverse(nums.begin(), nums.end());
        else {
            for (int j = n - 1; j >= 0; --j) {
                if (nums[j] > nums[i]) {
                    swap(nums[i], nums[j]);
                    break;
                }
            }
            reverse(nums.begin() + i + 1, nums.end());
        }
    }
};
