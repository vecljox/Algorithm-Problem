// 回溯法，类成员为数组时需要指定数组长度
class Solution {
public:
    vector<string> res;
    string strs[8] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> letterCombinations(string digits) {
        if (digits.empty())
            return {};

        string current;
        backtrack(digits, 0, current);
        return res;
    }

    void backtrack(string& digits, int index, string& current) {
        if (index == digits.size()) {
            res.push_back(current);
            return;
        }
        for (auto c : strs[digits[index] - '2']) {
            current.push_back(c);
            backtrack(digits, index + 1, current);
            current.pop_back();
        }
    }
};

// 自己做的,个人感觉更快更简洁
class SolutionB {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty())
            return {};
        string strs[] = {"abc", "def",  "ghi", "jkl",
                         "mno", "pqrs", "tuv", "wxyz"};
        int count = 1;
        for (auto d : digits) {
            count *= strs[d - '2'].size();
        }
        vector<string> res(count);
        for (int i = 0; i < count; ++i) {
            int index = i;
            for (auto d : digits) {
                string& letters = strs[d - '2'];
                res[i] += letters[index % letters.size()];
                index /= letters.size();
            }
        }
        return res;
    }
};
