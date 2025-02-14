// 动态规划
// dp[i][j]表示从数组的 [0,i] 下标范围内选取若干个正整数（可以是 0 个），是否存在一种选取方案使得被选取的正整数的和等于 j。初始时，dp 中的全部元素都是 false。
// dp[i][0] = true  dp[0][nums[0]] = true
// 如果 j<nums[i]，则在选取的数字的和等于 j 的情况下无法选取当前的数字 nums[i]，因此有 dp[i][j]=dp[i−1][j]
// 如果 j≥nums[i]，则对于当前的数字 nums[i]，可以选取也可以不选取，dp[i][j]  =  dp[i−1][j]  |  dp[i−1][j−nums[i]]
// 可以用滚动数组对空间复杂度进行优化从O(n*target)到O(target)，注意的时候内部循环更新dp时需要从右往左更新，避免在计算 dp[j] 值的时候，dp[j−nums[i]] 已经是被更新过的状态

// 时间复杂度：O(n*target)
// 空间复杂度：O(target)

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        int sum = 0;
        int maxNum = -1;
        for (auto num : nums) {
            sum += num;
            maxNum = max(maxNum, num);
        }
        if (sum % 2 == 1)
            return false;
        int target = sum / 2;
        if (maxNum > target)
            return false;
        vector<char> dp(target + 1, false);
        dp[0] = true, dp[nums[0]] = true;
        for (int i = 1; i < n; ++i) {
            for (int j = target; j >= nums[i]; --j) {
                dp[j] |= dp[j - nums[i]];
            }
        }
        return dp[target];
    }
};
