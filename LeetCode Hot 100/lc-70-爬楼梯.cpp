// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 初始化p=0,q=f(0),r=f(1)

class Solution {
public:
    int climbStairs(int n) {
        int p = 0, q = 1, r;
        for (int i = 1; i <= n; ++i) {
            r = p + q;
            p = q;
            q = r;
        }
        return r;
    }
};

// 时间复杂度：O(logn)
// 空间复杂度：O(1)
// 虽然时间复杂度更低，但不如第一种简洁

class SolutionB {
public:
    int climbStairs(int n) {
        vector<vector<long long>> matrix{{1, 1}, {1, 0}};
        matrix = matrixPow(matrix, n);
        return matrix[0][0];
    }

    vector<vector<long long>> matrixPow(vector<vector<long long>>& a, int n) {
        vector<vector<long long>> res{{1, 0}, {0, 1}};
        while (n) {
            if (n & 1)
                res = multiply(res, a);
            a = multiply(a, a);
            n >>= 1;
        }
        return res;
    }

    vector<vector<long long>> multiply(vector<vector<long long>>& a,
                                       vector<vector<long long>>& b) {
        vector<vector<long long>> c(2, vector<long long>(2));
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                c[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j];
            }
        }
        return c;
    }
};
