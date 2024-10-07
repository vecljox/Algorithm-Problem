// 直接将动态规划中计算出的状态值存储到frame中，空间复杂度为O(1)
class Solution {
public:
    int jewelleryValue(vector<vector<int>>& frame) {
        int m = frame.size();
        int n = frame[0].size();

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 && j == 0)
                    continue;
                if (i == 0) {
                    frame[i][j] += frame[i][j - 1];
                } else if (j == 0) {
                    frame[i][j] += frame[i - 1][j];
                } else {
                    frame[i][j] += max(frame[i][j - 1], frame[i - 1][j]);
                }
            }
        }
        return frame[m - 1][n - 1];
    }
};


// 相比于原矩阵多开一行一列更优雅地处理边界条件，代码看起来更简洁，不过空间复杂度为O(mn)
class SolutionB {
public:
    int jewelleryValue(vector<vector<int>>& frame) {
        int m = frame.size();
        int n = frame[0].size();
        vector<vector<int>> dp =
            vector<vector<int>>(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                dp[i][j] =
                    frame[i - 1][j - 1] + max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[m][n];
    }
};
