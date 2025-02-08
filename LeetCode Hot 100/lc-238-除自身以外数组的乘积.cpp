// 分别计算当前索引左侧(前缀)和右侧(后缀)的所有数字的乘积放进数组L和R里，那么res[i]=L[i]*R[i]
// 利用输出数组空间复杂度上可以优化到O(1)

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, 1);
        for (int i = 1; i < n; ++i)
            res[i] = res[i - 1] * nums[i - 1];
        int tmp = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            res[i] *= tmp;
            tmp *= nums[i];
        }
        return res;
    }
};
