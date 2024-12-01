// 回溯，标准做法
class Solution {
public:
    vector<vector<int>> res;
    vector<int> t;
    
    vector<vector<int>> subsets(vector<int>& nums) {
        backtrack(0, nums);
        return res;
    }

    void backtrack(int cur, vector<int>& nums) {
        if (cur == nums.size()){
            res.push_back(t);
            return;
        }
            
        t.push_back(nums[cur]);
        backtrack(cur + 1, nums);
        t.pop_back();
        backtrack(cur + 1, nums);
    }
};

// 自己想的，感觉也不错
class SolutionB {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res{{}, {nums[0]}};
        for (int i = 1; i < nums.size(); i++) {
            int n = res.size();
            for (int j = 0; j < n; j++) {
                auto temp = res[j];
                temp.push_back(nums[i]);
                res.push_back(move(temp));
            }
        }
        return res;
    }
};
