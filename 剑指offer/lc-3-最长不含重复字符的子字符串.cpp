// 滑动窗口+哈希表
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int res = 0;
        unordered_map<char, int> dic;
        int i = -1;
        for (int j = 0; j < s.size(); ++j) {
            if (dic.count(s[j]) && dic[s[j]] > i)
                i = dic[s[j]];
            else
                res = max(res, j - i);
            dic[s[j]] = j;
        }
        return res;
    }
};

// 动态规划+哈希表
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> dic;
        int res = 0;
        int pre = 0;    //pre为末尾字符索引值为i-1的不含有重复字符的最长子串的长度
        int len = s.size();
        for (int i = 0; i < len; ++i) {
            if (dic.find(s[i]) != dic.end() && dic[s[i]]>=i-pre) {
                pre = i - dic[s[i]];
            } else {
                ++pre;
                res = max(res, pre);
            }
            dic[s[i]] = i;
        }
        return res;
    }
};
