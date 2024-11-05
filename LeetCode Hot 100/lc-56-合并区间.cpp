// 先排序再合并
// 对于 vector<int> 类型，std::sort 会默认使用 operator< 进行排序
// 具体而言，std::sort 会比较每个子向量的第一个元素，并在遇到相等的情况下再比较第二个元素，这样保证了排序的稳定性。

// 时间复杂度：O(nlogn)
// 空间复杂度：O(n),若不考虑存储答案的空间,则为O(logn)

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> merge{intervals[0]};
        for (int i = 1; i < intervals.size(); ++i) {
            auto& pre = merge.back();
            if (pre[1] >= intervals[i][0])
                pre[1] = max(pre[1], intervals[i][1]);
            else
                merge.push_back(intervals[i]);  //这里可以使用move减少开销
        }
        return merge;
    }
};
