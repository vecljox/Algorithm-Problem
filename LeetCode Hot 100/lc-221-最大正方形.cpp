// 动态规划
// dp(i,j) 表示以 (i,j) 为右下角，且只包含 1 的正方形的边长最大值。
// 如果该位置的值是 1，则 dp(i,j) 的值由其上方、左方和左上方的三个相邻位置的 dp 值决定。具体而言，当前位置的元素值等于三个相邻位置的元素中的最小值加 1，状态转移方程如下：
// dp(i,j)=min(dp(i−1,j),dp(i−1,j−1),dp(i,j−1))+1

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int maxLen = 0;

        int m = matrix.size();
        int n = matrix[0].size();

        vector<vector<int>> dp(m, vector<int>(n));

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == '1') {
                    if (i == 0 || j == 0) {
                        dp[i][j] = 1;
                    } else {
                        dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]),
                                       dp[i - 1][j - 1]) +
                                   1;
                    }
                    maxLen = max(maxLen, dp[i][j]);
                }
            }
        }

        return maxLen * maxLen;
    }
};
