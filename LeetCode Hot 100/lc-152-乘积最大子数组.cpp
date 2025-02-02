// 动态规划
// 连续子数组的最大乘积需要考虑正负数的交替情况。负负得正可能使得乘积更大，因此需要同时跟踪当前的最大和最小乘积。
// 如果只跟踪最大乘积，会发现当前位置的最大乘积未必是由前一个位置的最大乘积转移得到的，也就是不满足最优子结构

cur_min表示以当前元素结尾的最小子数组的乘积
cur_max表示以当前元素结尾的最大子数组的乘积

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int res = nums[0];
        int cur_min = nums[0], cur_max = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            int tmp_min =
                min(nums[i], min(cur_min * nums[i], cur_max * nums[i]));
            int tmp_max =
                max(nums[i], max(cur_min * nums[i], cur_max * nums[i]));

            cur_min = tmp_min;
            cur_max = tmp_max;

            res = max(res, cur_max);
        }
        return res;
    }
};
