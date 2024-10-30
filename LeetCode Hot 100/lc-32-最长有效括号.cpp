// 时间复杂度： O(n)
// 空间复杂度： O(1)
// 前后两次扫描
class Solution {
public:
    int longestValidParentheses(string s) {
        int res = 0, n = s.size(), left = 0, right = 0;
        for (int i = 0; i < n; ++i) {
            s[i] == '(' ? ++left : ++right;
            if (left == right)
                res = max(res, left + right);
            else if (right > left)
                left = right = 0;
        }
        left = right = 0;
        for (int i = n - 1; i >= 0; --i) {
            s[i] == '(' ? ++left : ++right;
            if (left == right)
                res = max(res, left + right);
            else if (left > right)
                left = right = 0;
        }
        return res;
    }
};

// 动态规划
// dp[i] 表示以下标 i 字符结尾的最长有效括号的长度
// 时间复杂度： O(n)
// 空间复杂度： O(n)
class SolutionB {
public:
    int longestValidParentheses(string s) {
        int res = 0;
        int n = s.size();
        vector<int> dp(n, 0);
        for (int i = 1; i < n; ++i) {
            if (s[i] == ')') {
                if (s[i - 1] == '(') {
                    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
                } else {
                    int j = i - dp[i - 1] - 1;
                    if (j >= 0 && s[j] == '(') {
                        dp[i] = dp[i - 1] + (j >= 1 ? dp[j - 1] : 0) + 2;
                    }
                }
                res = max(res, dp[i]);
            }
        }
        return res;
    }
};
