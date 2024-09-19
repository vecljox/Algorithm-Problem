class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0 ;
        int right = nums.size()-1;
        int center;

        while((left<right)&&(nums[left]>=nums[right]))
        {
            center = (left+right)/2;

            if(nums[center]<nums[left])
                right = center;

            else if(nums[center]>nums[right])
                left = center+1;
                
            else
                ++left;
        }

        return nums[left];

    }
    
};
