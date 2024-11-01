// candidates：候选数字数组。
// target：当前需要达到的目标值。
// start：当前递归调用中开始选择数字的起始索引，确保组合的顺序性，避免重复。
// combination：当前的组合路径。
// res：存储所有符合条件的组合。

// 在回溯开始前可以对 candidates 进行排序。这有助于在递归过程中提前剪枝（当当前数字大于剩余目标值时，可以停止进一步探索，因为数组是有序的）。

class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> combination;
        // sort(candidates.begin(), candidates.end());
        backtrack(candidates, target, 0, combination);
        return res;
    }

    void backtrack(const vector<int>& candidates, int target, int start,
                   vector<int>& combination) {
        if (target == 0) {
            res.push_back(combination);
            return;
        }
        for (int i = start; i < candidates.size(); ++i) {
            if (candidates[i] > target)
                continue;
            combination.push_back(candidates[i]);
            backtrack(candidates, target - candidates[i], i, combination);
            combination.pop_back();
        }
    }
};
