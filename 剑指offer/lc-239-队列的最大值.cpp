class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        deque<int> q;
        for (int i = 0; i < nums.size(); ++i) {
            if (q.size() && q.front() <= i - k)
                q.pop_front();
            while (q.size() && nums[i] >= nums[q.back()])
                q.pop_back();
            q.push_back(i);
            if (i >= k - 1)
                res.push_back(nums[q.front()]);
        }
        return res;
    }
};
