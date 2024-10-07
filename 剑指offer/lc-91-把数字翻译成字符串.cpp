class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        // a = f[i - 2], b = f[i - 1], c = f[i]
        int a = 1;
        int b = s[0] == '0' ? 0 : 1;

        for (int i = 1; i < n; ++i) {
            int c = 0;
            if (s[i] != '0') {
                c += b;
            }
            if (s[i - 1] == '1' || s[i - 1] == '2' && s[i] < '7') {
                c += a;
            }
            tie(a, b) = {b, c};
        }

        return b;
    }
};

// 自己做的，思路是从字符串尾部开始动态规划，还是推荐第一种做法
class SolutionB {
public:
    int numDecodings(string s) {
        int pre = 1;
        int cur = s.back() == '0' ? 0 : 1;
        for (int i = s.size() - 2; i >= 0; --i) {
            if (s[i] == '0') {
                pre = cur;
                cur = 0;
            } else {
                int tmp = cur;
                if (s[i] == '1' || s[i] == '2' && s[i + 1] < '7')
                    tmp += pre;
                pre = cur;
                cur = tmp;
            }
        }
        return cur;
    }
};
