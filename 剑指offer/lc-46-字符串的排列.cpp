// 回溯法
class Solution {
public:
    void backtrack(vector<vector<int>>& res,vector<int>&output,int first)
    {
        if(first == output.size())
        {
            res.push_back(output);
            return;
        }
        for(int i=first;i<output.size();++i)
        {
            swap(output[i],output[first]);
            backtrack(res,output,first+1);
            swap(output[i],output[first]);
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        backtrack(res,nums,0);
        return res;
    }
};
