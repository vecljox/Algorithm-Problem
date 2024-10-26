// 双指针，贪心，只有移动较低的板子才有机会增大值
class Solution {
public:
    int maxArea(vector<int>& height) {
        int res = 0;
        int i = 0;
        int j = height.size() - 1;
        while (i < j) {
            res = max(res, min(height[i], height[j]) * (j - i));
            if (height[i] < height[j])
                ++i;
            else
                --j;
        }
        return res;
    }
};
