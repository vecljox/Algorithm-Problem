// 先查找哈希表，若未查找到再把自己插入进去，避免和自己匹配
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hashtable;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            auto it = hashtable.find(target - nums[i]);
            if (it != hashtable.end())
                return {i, it->second};
            hashtable[nums[i]] = i;
        }
        return {};
    }
};
