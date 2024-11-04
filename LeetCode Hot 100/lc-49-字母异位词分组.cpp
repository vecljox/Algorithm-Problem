//哈希
// n：strs 中的字符串的数量
// k：strs 中的字符串的的最大长度。
// 时间复杂度：O(nklogk)
// 空间复杂度：O(nk)

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> dict;
        for (auto& str : strs) {
            auto key = str;
            sort(key.begin(), key.end());
            dict[key].push_back(move(str));
        }
        vector<vector<string>> res;
        for (auto it = dict.begin(); it != dict.end(); ++it)
            res.push_back(move(it->second));
        return res;
    }
};
