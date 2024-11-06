// 时间复杂度 ：O(mn)
// 空间复杂度 ：O(n)

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        vector<int> pre(n + 1), cur(n + 1);
        // 初始化第一行
        for (int j = 0; j <= n; ++j)
            pre[j] = j;
        for (int i = 1; i <= m; ++i) {
            cur[0] = i;  // 初始化第一列
            for (int j = 1; j <= n; ++j) {
                if (word1[i - 1] == word2[j - 1])
                    cur[j] = pre[j - 1];
                else
                    cur[j] = min({
                        pre[j - 1], //替换
                        cur[j - 1], //插入
                        pre[j]      //删除
                    }) + 1;
            }
            pre = cur;
        }
        return pre[n];
    }
};

// 时间复杂度 ：O(mn)
// 空间复杂度 ：O(mn)

class SolutionB {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int j = 0; j <= n; ++j)
            dp[0][j] = j;
        for (int i = 1; i <= m; ++i) {
            dp[i][0] = i;
            for (int j = 1; j <= n; ++j) {
                if (word1[i - 1] == word2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] =
                        min({dp[i - 1][j - 1], dp[i][j - 1], dp[i - 1][j]}) + 1;
            }
        }
        return dp[m][n];
    }
};
