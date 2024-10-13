class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int xorsum = 0;
        for (auto num : nums) {
            xorsum ^= num;
        }
        // 防止溢出
        int lsb = (xorsum == INT_MIN ? xorsum : xorsum & -xorsum);  //当xorsum为INT_MIN时，最低有效位就是自己
        int a = 0;
        int b = 0;
        for (auto num : nums) {
            if (num & lsb)
                a ^= num;
            else
                b ^= num;
        }
        return {a, b};
    }
};
