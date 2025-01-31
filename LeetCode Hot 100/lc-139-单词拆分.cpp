// 动态规划，dp[i]表示s的前i个字符是否能被拆分，所以要求的就是dp[s.size()]
// 当dp[i]为true时，为了判断后续的dp[i+1],dp[i+2]...是否为true，我们需要判断相应的子字符串是否在字符串列表里
// 注意我们用j来表示这个子字符串的长度

// 其实SolutionB是对这种方法的优化方案，但是为了答案的简洁性，放在了前面
// 具体优化思路是根据字符串列表中字符串的长度范围来限制j
// 以及当dp[i + j]本来就是true时就不用去更新dp[i+j]了

// 时间复杂度：O(n^2)    我们一共有 O(n) 个状态需要计算，每次计算需要枚举 O(n) 次，哈希表判断一个字符串是否出现在给定的字符串列表需要 O(1) 的时间，
// 空间复杂度：O(n)      其中 n 为字符串 s 的长度。我们需要 O(n) 的空间存放 dp 值以及哈希表亦需要 O(n) 的空间复杂度，因此总空间复杂度为 O(n)。

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet;
        for (const auto& word : wordDict) {
            wordSet.insert(word);
        }

        int n = s.size();
        vector<char> dp(n + 1, false);
        dp[0] = true;

        for (int i = 0; i < n; ++i) {
            for (int j = 1; j <= n - i; ++j) {
                if (dp[i] && wordSet.count(s.substr(i, j))) {
                    dp[i + j] = true;
                }
            }
        }

        return dp[n];
    }
};

class SolutionB {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet;
        int maxLen = 0;
        int minLen = INT_MAX;
        for (const auto& word : wordDict) {
            wordSet.insert(word);
            int len = word.size();
            if (len > maxLen)
                maxLen = len;
            if (len < minLen)
                minLen = len;
        }

        int n = s.size();
        vector<char> dp(n + 1, false);
        dp[0] = true;

        for (int i = 0; i < n; ++i) {
            for (int j = minLen; j <= n - i && j <= maxLen; ++j) {
                if (dp[i] && !dp[i + j] && wordSet.count(s.substr(i, j))) {
                    dp[i + j] = true;
                }
            }
        }

        return dp[n];
    }
};
