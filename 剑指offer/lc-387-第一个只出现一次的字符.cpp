// 使用哈希表存储频数
class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> frequency;
        for (auto ch : s) {
            ++frequency[ch];
        }
        for (int i = 0; i < s.size(); ++i) {
            if (frequency[s[i]] == 1)
                return i;
        }
        return -1;
    }
};

// 使用哈希表存储索引
class SolutionB {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> position;
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            if (position.count(s[i]))
                position[s[i]] = n;
            else
                position[s[i]] = i;
        }
        int first = n;
        for (auto [_, pos] : position) {
            if (pos < first)
                first = pos;
        }

        return first == n ? -1 : first;
    }
};

// 队列
// 延迟删除:即使队列中有一些字符出现了超过一次，但它只要不位于队首，那么就不会对答案造成影响，我们也就可以不用去删除它。
class SolutionC {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> position;
        queue<pair<char, int>> q;
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            if (!position.count(s[i])) {
                position[s[i]] = i;
                q.emplace(s[i], i);
            } else {
                position[s[i]] = -1;
                while (!q.empty() && position[q.front().first] == -1) {
                    q.pop();
                }
            }
        }

        return q.empty() ? -1 : q.front().second;
    }
};
