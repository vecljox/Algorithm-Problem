class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int len = nums.size();
        //建堆
        for (int i = len / 2 - 1; i >= 0; --i) {
            percDown(nums, i, len);
        }
        //弹出k-1个最大元素
        for (int j = len - 1; --k > 0; --j) {
            nums[0] = nums[j];
            percDown(nums, 0, j);
        }
        return nums[0];
    }

    //下滤  i:下滤的起点索引值 n:堆的逻辑大小 
    void percDown(vector<int>& nums, int i, int n) {
        int tmp = nums[i];
        int child;
        for (; leftChild(i) < n; i = child) {
            child = leftChild(i);
            if (child != n - 1 && nums[child] < nums[child + 1])
                ++child;
            if (tmp < nums[child])
                nums[i] = nums[child];
            else
                break;
        }
        nums[i] = tmp;
    }

    inline int leftChild(int i) { return 2 * i + 1; }
};
