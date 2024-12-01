// 滑动窗口+哈希表
// 当字符串的右边界i递增时，左边界j呈非单调递减性
// hash[c]表示的是当前c这个字母还缺多少个
// 使用res_start和res_len是为了减少字符串内存的分配

class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> hash;
        for (auto c : t) {
            hash[c]++;
        }
        int count = hash.size();
        int res_start = 0, res_len = 0;
        for (int i = 0, j = 0, c = 0; i < s.size(); i++) {
            hash[s[i]]--;
            if (hash[s[i]] == 0)
                c++;
            while (c == count && hash[s[j]] < 0)
                hash[s[j++]]++;
            if (c == count) {
                int len = i - j + 1;
                if (res_len == 0 || res_len > len) {
                    res_start = j;
                    res_len = len;
                }
            }
        }
        return s.substr(res_start, res_len);
    }
};
