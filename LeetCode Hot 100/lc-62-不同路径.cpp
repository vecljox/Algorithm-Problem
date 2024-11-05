m：行数
n：列数

// 时间复杂度：O(m)
// 空间复杂度：O(1)
// 由于我们交换行列的值并不会对答案产生影响，因此我们总可以通过交换 m 和 n 使得 m≤n，这样时间复杂度降低至 O(min(m,n))。
// res = res * y / x 这里有个细节，每次都能保证整除，n*((n+1)/2)*((n+2)/3)...
// n~n+k-1中一定有个数能被k整除
// 或者可以这么理解，因为每一步算完都是一个组合数，第一步的结果是C(n,1)，第二步是C(n+1,2)。。每一步都保证是整数

class Solution {
public:
    int uniquePaths(int m, int n) {
        long long res = 1;
        for (int x = 1, y = n; x < m; ++x, ++y) {
            res = res * y / x;
        }
        return res;
    }
};

// 时间复杂度：O(mn)
// 空间复杂度：O(n)
// 由于我们交换行列的值并不会对答案产生影响，因此我们总可以通过交换 m 和 n 使得 m≤n，这样空间复杂度降低至 O(min(m,n))

class SolutionB {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1);
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[j] += dp[j - 1];
            }
        }
        return dp[n - 1];
    }
};

// 时间复杂度：O(mn)
// 空间复杂度：O(mn)

class SolutionC {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i)
            dp[i][0] = 1;
        for (int j = 0; j < n; ++j)
            dp[0][j] = 1;
        for (int i = 1; i < m; ++i)
            for (int j = 1; j < n; ++j)
                dp[i][j] += dp[i - 1][j] + dp[i][j - 1];

        return dp[m - 1][n - 1];
    }
};
