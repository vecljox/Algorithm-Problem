// O(1)空间复杂度 具体图解见：https://leetcode.cn/problems/reverse-words-in-a-string/solutions/194450/fan-zhuan-zi-fu-chuan-li-de-dan-ci-by-leetcode-sol
class Solution {
public:
    string reverseWords(string s) {
        reverse(s.begin(), s.end());
        int idx = 0;
        int n = s.size();
        for (int start = 0; start < n; ++start) {
            if (s[start] != ' ') {
                // 填一个空白字符然后将idx移动到下一个单词的开头位置
                if (idx != 0)
                    s[idx++] = ' ';
                // 循环遍历至单词的末尾
                int end = start;
                while (end < n && s[end] != ' ')
                    s[idx++] = s[end++];
                // 反转整个单词
                reverse(s.begin() + idx - (end - start), s.begin() + idx);
                // 更新start，去找下一个单词
                start = end;
            }
        }
        s.erase(idx);
        return s;
    }
};
