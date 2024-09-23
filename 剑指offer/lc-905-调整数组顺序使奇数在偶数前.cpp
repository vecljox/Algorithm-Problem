class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        int l=0;
        int r= nums.size()-1;

        for(;;)
        {
            while(l<r&&nums[l]%2==0)    ++l;
            while(l<r&&nums[r]%2==1)    --r;

            if(l>=r)
                return nums;

            swap(nums[l],nums[r]);
        }
        
    }
};
