//摩尔投票法
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int candidate;
        int count = 0;
        for(int num:nums)
        {
            if(count==0)
            {
                candidate =num;
                count = 1;
            }
            else
                num==candidate?++count:--count;

        }

        return candidate;
    }
};

//哈希表
class SolutionB {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int,int>  counts;
        int majority;

        for(int num:nums)
        {
            ++counts[num];
            if(counts[num]>counts[majority])
                majority = num;
        }

        return majority;
    }
};
