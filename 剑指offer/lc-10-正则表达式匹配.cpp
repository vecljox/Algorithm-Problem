// 动态规划
// dp[i][j] : s 的前 i 个字符与 p 中的前 j 个字符是否能够匹配

class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        auto matches = [&](int i, int j) {
            if (i == 0)
                return false;
            return p[j - 1] == '.' || p[j - 1] == s[i - 1];
        };
        vector<vector<char>> dp(m + 1, vector<char>(n + 1, false));
        dp[0][0] = true;
        for (int i = 0; i <= m; ++i)
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] != '*') {
                    if (matches(i, j))
                        dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = dp[i][j - 2];
                    if (matches(i, j - 1))
                        dp[i][j] |= dp[i - 1][j];
                }
            }
        return dp[m][n];
    }
};
