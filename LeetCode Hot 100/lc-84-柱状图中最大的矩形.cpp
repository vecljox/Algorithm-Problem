// https://www.acwing.com/solution/content/140/
// 此题的本质是找到每个柱形条左侧第一个比自己低或相等，以及右侧第一个严格比自己低的矩形条，然后用宽度乘上当前柱形条的高度作为备选答案
// 为了算法书写方便，在数组末尾添加高度 0
// 这会使得栈中所有数字在最后出栈。

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int res = 0;
        int n = heights.size();
        heights.push_back(0);
        stack<int> stk;
        for (int i = 0; i <= n; i++) {
            while (!stk.empty() && heights[i] < heights[stk.top()]) {
                int cur = stk.top();
                stk.pop();
                if (stk.empty())
                    res = max(res, heights[cur] * i);
                else
                    res = max(res, heights[cur] * (i - stk.top() - 1));
            }
            stk.push(i);
        }
        return res;
    }
};
