// 正向处理，这样就不用考虑边界
class Solution {
public:
    vector<double> statisticsProbability(int num) {
        vector<double> dp(6, 1.0 / 6.0);
        for (int n = 2; n <= num; ++n) {
            int len = dp.size();
            vector<double> tmp(len + 5, 0.0);
            for (int i = 0; i < len; ++i) {
                for (int j = 0; j < 6; ++j) {
                    tmp[i + j] += (dp[i] / 6.0);
                }
            }
            dp = tmp;
        }
        return dp;
    }
};

// 自己做的
// 逆向处理，注意骰子的值从0到5,边界的话当骰子为最大值时dp的索引值j为最小值，但也要大于等于0，即j = max(i - 5, 0)，同理骰子最小时,j最大，所以j<min(i + 1, len)
class SolutionB {
public:
    vector<double> statisticsProbability(int num) {
        vector<double> dp(6, 1.0 / 6.0);
        for (int n = 2; n <= num; ++n) {
            int len = dp.size();
            vector<double> tmp(len + 5);
            for (int i = 0; i < len + 5; ++i) {
                double p = 0.0;
                int end = min(i + 1, len);
                for (int j = max(i - 5, 0); j < end; ++j) {
                    p += dp[j] / 6.0;
                }
                tmp[i] = p;
            }
            dp = tmp;
        }
        return dp;
    }
};
