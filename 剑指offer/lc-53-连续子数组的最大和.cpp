class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int res = nums[0], n = nums.size();
        for (int i = 1; i < n; ++i) {
            if (nums[i - 1] > 0)
                nums[i] += nums[i - 1];
            res = max(res, nums[i]);
        }
        return res;
    }
};

class SolutionB {
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

// https://www.acwing.com/solution/content/133/
// 分治：y总 时间O(n), 空间 O(logn)
class SolutionC {
public:

    struct status {
        int sum, s, ls, rs; // 区间总和, 最大子段和, 最大前缀和, 最大后缀和
    };

    status build(vector<int>& nums, int l, int r) {
        if (l == r) return {nums[l], nums[l], nums[l], nums[l]};

        int mid = l + r >> 1;
        auto L = build(nums, l, mid), R = build(nums, mid + 1, r);
        status LR;
        LR.sum = L.sum + R.sum;
        LR.s = max(max(L.s, R.s), L.rs + R.ls);
        LR.ls = max(L.ls, L.sum + R.ls);
        LR.rs = max(R.rs, R.sum + L.rs);
        return LR;
    }

    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        auto res = build(nums, 0, n - 1);
        return res.s;
    }
};

