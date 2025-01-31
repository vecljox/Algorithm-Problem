// 枚举数组中的每个数x,去尝试匹配x+1,x+2,x+3...
// 若数组中存在x-1，则x必定不是连续序列的头部，不用匹配跳过即可。
// 因为有大量的查询操作，可以用哈希表存储

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int res = 0;
        unordered_set<int> num_set;
        for (auto num : nums) {
            num_set.insert(num);
        }

        for (auto num : num_set) {
            if (num_set.count(num - 1))
                continue;
            int len = 1;
            while (num_set.count(++num)) {
                ++len;
            }
            res = max(res, len);
        }
        return res;
    }
};
