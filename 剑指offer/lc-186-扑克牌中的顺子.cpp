// 哈希表判别是否有重复元素
class Solution {
public:
    bool checkDynasty(vector<int>& places) {
        unordered_set<int> repeat;
        int mi = 13;
        int ma = 0;
        for (auto p : places) {
            if (p == 0)
                continue;
            if (repeat.count(p))
                return false;
            repeat.insert(p);
            mi = min(mi, p);
            ma = max(ma, p);
        }
        return ma - mi < 5;
    }
};
