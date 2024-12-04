// 双指针
// 注意循环条件不能写l<=r，否则可能会导致越界
// 不用考虑l=r的原因是此时柱子为最高柱子(left和right中总是有一个停留的位置是当前已遍历过列中最高的柱子)，没有雨水
// 如果想写成l<=r则要把更新lmax和rmax的代码放在l++,r--前面，不过不推荐这样做，因为反而没现在简洁
// 时间复杂度：O(n)
// 空间复杂度：O(1)
class Solution {
public:
    int trap(vector<int>& height) {
        int res = 0, n = height.size();
        int l = 0, r = n - 1, lmax = height[l], rmax = height[r];
        while (l < r) {
            if (lmax < rmax) {
                res += lmax - height[l++];
                lmax = max(lmax, height[l]);
            } 
            else {
                res += rmax - height[r--];
                rmax = max(rmax, height[r]);
            }
        }
        return res;
    }
};

// (三次线性扫描) 
// 时间复杂度：O(n)
// 空间复杂度：O(n)
class SolutionB {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        vector<int> lmax(n), rmax(n);
        lmax[0] = height[0];
        for (int i = 1; i < n; ++i) {
            lmax[i] = max(lmax[i - 1], height[i]);
        }
        rmax[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            rmax[i] = max(rmax[i + 1], height[i]);
        }
        int res = 0;
        for (int i = 1; i < n - 1; ++i) {
            res += min(lmax[i], rmax[i]) - height[i];
        }
        return res;
    }
};

// 单调栈,个人感觉挺简洁但思路有点难
// 若当前柱子的高度height[i]大于栈顶柱子的高度height[stk.top()]时，意味着找到一个可能的右边界，可以计算雨水
// 弹出栈顶柱子的索引top，然后检查新的栈顶是否存在。如果栈为空，表示没有左边界，无法形成容器，跳出循环。
// 时间复杂度：O(n)
// 空间复杂度：O(n)
class SolutionC {
public:
    int trap(vector<int>& height) {
        int n = height.size(), res = 0;
        stack<int> stk;
        for (int i = 0; i < n; ++i) {
            while (!stk.empty() && height[i] > height[stk.top()]) {
                int top = stk.top();
                stk.pop();
                if (stk.empty())
                    break;
                res += (i - stk.top() - 1) *
                       (min(height[i], height[stk.top()]) - height[top]);
            }
            stk.push(i);
        }
        return res;
    }
};
