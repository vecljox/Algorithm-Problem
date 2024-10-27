// 回溯法
// 卡特兰数
// https://zhuanlan.zhihu.com/p/97619085
class Solution {
public:
    vector<string> res;
    vector<string> generateParenthesis(int n) {
        string cur;
        backtrack(0, 0, n, cur);
        return res;
    }

    void backtrack(int l, int r, int n, string& cur) {
        if (l == n && r == n) {
            res.push_back(cur);
            return;
        }
        if (l < n) {
            cur.push_back('(');
            backtrack(l + 1, r, n, cur);
            cur.pop_back();
        }
        if (r < l) {
            cur.push_back(')');
            backtrack(l, r + 1, n, cur);
            cur.pop_back();
        }
    }
};
