// https://www.acwing.com/solution/content/141/
时间复杂度: O(mn)
空间复杂度: O(n) ,存放高度和用于单调栈。

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int res = 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<int> heights(n + 1, 0);
        heights[n] = -1;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == '0')
                    heights[j] = 0;
                else
                    ++heights[j];
            }

            stack<int> stk;
            for (int j = 0; j <= n; ++j) {
                while (!stk.empty() && heights[j] < heights[stk.top()]) {
                    int cur = stk.top();
                    stk.pop();
                    int width = stk.empty() ? j : j - stk.top() - 1;
                    res = max(res, heights[cur] * width);
                }
                stk.push(j);
            }
        }
        return res;
    }
};
