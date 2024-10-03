class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int res = nums[0];
        int pre = nums[0];
        for(int i=1;i<nums.size();++i)
        {
            pre = max(pre+nums[i],nums[i]);
            res = max(res,pre);
        }
        return res;
    }
};
