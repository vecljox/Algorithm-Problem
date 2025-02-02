// 对于第 k (k>2) 间房屋，有两个选项：
// 偷窃第 k 间房屋，那么就不能偷窃第 k−1 间房屋，偷窃总金额为前 k−2 间房屋的最高总金额与第 k 间房屋的金额之和。
// 不偷窃第 k 间房屋，偷窃总金额为前 k−1 间房屋的最高总金额。

// 用 dp[i] 表示前 i 间房屋能偷窃到的最高总金额，那么就有如下的状态转移方程：
// dp[i]=max(dp[i−2]+nums[i],dp[i−1])

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1)
            return nums[0];

        int first = nums[0];
        int second = max(nums[0], nums[1]);
        for (int i = 2; i < n; ++i) {
            int tmp = max(nums[i] + first, second);
            first = second;
            second = tmp;
        }

        return second;
    }
};
