// https://www.acwing.com/solution/content/140/
// 此题的本质是找到每个柱形条左侧第一个比自己低或相等，以及右侧第一个严格比自己低的矩形条，然后用宽度乘上当前柱形条的高度作为备选答案
// 为了算法书写方便，在数组末尾添加高度 0
// 这会使得栈中所有数字在最后出栈。


//如果找到的是当前柱形条左侧第一个和自己相等的柱形条，虽然算出来的面积不是真正符合题意的矩形面积，但是当计算到相等的柱形条时会覆盖现在的情况，所以对于题目要求没有影响

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int res = 0;
        heights.push_back(-1);
        int n = heights.size();
        stack<int> stk;
        for (int i = 0; i < n; ++i) {
            while (!stk.empty() && heights[i] < heights[stk.top()]) {
                int cur = stk.top();
                stk.pop();
                int width = stk.empty() ? i : i - stk.top() - 1;
                res = max(res, heights[cur] * width);
            }
            stk.push(i);
        }
        return res;
    }
};
