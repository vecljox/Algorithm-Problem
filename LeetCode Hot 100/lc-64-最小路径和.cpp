// 时间复杂度 O(M×N) ： 遍历整个 grid 矩阵元素。
// 空间复杂度 O(1) ： 直接修改原矩阵，不使用额外空间。

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (i == 0 && j == 0)
                    continue;
                else if (i == 0)
                    grid[i][j] += grid[i][j - 1];
                else if (j == 0)
                    grid[i][j] += grid[i - 1][j];
                else
                    grid[i][j] += min(grid[i][j - 1], grid[i - 1][j]);
        return grid[m - 1][n - 1];
    }
};

// 时间复杂度 O(M×N) ： 遍历整个 grid 矩阵元素。
// 空间复杂度 O(N) ： 不修改原矩阵，使用滚动数组。

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<int> dp(n);
        dp[0] = grid[0][0];
        for (int j = 1; j < n; ++j)
            dp[j] = dp[j - 1] + grid[0][j];
        for (int i = 1; i < m; ++i) {
            dp[0] += grid[i][0]; // 单独计算第0列
            for (int j = 1; j < n; ++j)
                dp[j] = min(dp[j], dp[j - 1]) + grid[i][j];
        }
        return dp[n - 1];
    }
};
