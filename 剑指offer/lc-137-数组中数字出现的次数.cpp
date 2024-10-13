// 位运算，具体状态图见：https://leetcode.cn/problems/single-number-ii/solutions/8944/single-number-ii-mo-ni-san-jin-zhi-fa-by-jin407891
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int one = 0;
        int two = 0;
        for (auto n : nums) {
            one = (one ^ n) & (~two);
            two = (two ^ n) & (~one);
        }
        return one;
    }
};

class SolutionB {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for (int i = 0; i < 32; ++i) {
            int count = 0;
            for (auto n : nums) {
                if ((n >> i) & 1)
                    ++count;
            }
            if (count % 3)
                res |= (1 << i);
        }
        return res;
    }
};
