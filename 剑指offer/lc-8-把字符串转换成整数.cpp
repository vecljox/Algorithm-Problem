// 状态机，https://leetcode.cn/problems/string-to-integer-atoi/solutions/183164/zi-fu-chuan-zhuan-huan-zheng-shu-atoi-by-leetcode-
class Solution {
public:
    int myAtoi(string s) {
        string state = "start";
        unordered_map<string, vector<string>> table = {
            {"start", {"start", "signed", "in_number", "end"}},
            {"signed", {"end", "end", "in_number", "end"}},
            {"in_number", {"end", "end", "in_number", "end"}},
            {"end", {"end", "end", "end", "end"}},
        };
        int sign = 1;
        int res = 0;
        for (auto ch : s) {
            state = table[state][get_col(ch)];
            if (state == "in_number") {
                int digit = ch - '0';
                if (res > (INT_MAX - digit) / 10)
                    return sign == 1 ? INT_MAX : INT_MIN;
                res = res * 10 + digit;
            } else if (state == "signed") {
                sign = ch == '+' ? 1 : -1;
            } else if (state == "end")
                break;
        }
        return sign * res;
    }

    int get_col(char c) {
        if (c == ' ')
            return 0;
        if (c == '+' || c == '-')
            return 1;
        if (isdigit(c))
            return 2;
        return 3;
    }
};

class SolutionB {
public:
    int myAtoi(string s) {
        int n = s.size();
        int i = 0;
        while (i < n && s[i] == ' ') {
            ++i;
        }
        int sign = 1;
        if (s[i] == '+') {
            sign = 1;
            ++i;
        } else if (s[i] == '-') {
            sign = -1;
            ++i;
        }
        int res = 0;
        while (i < n && s[i] >= '0' && s[i] <= '9') {
            int digit = s[i] - '0';
            if (res > (INT_MAX - digit) / 10)
                return sign == 1 ? INT_MAX : INT_MIN;
            res = res * 10 + digit;
            ++i;
        }
        return sign * res;
    }
};
