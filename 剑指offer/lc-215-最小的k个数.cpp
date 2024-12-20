//堆
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

//快速排序的分区方法
class SolutionB {
public:
    int quickselect(vector<int>& nums, int l, int r, int k) {
        int pivot = nums[r], i = l - 1, j = r;
        for (;;) {
            while (++i < j && nums[i] < pivot) {
            }
            while (--j > i && nums[j] > pivot) {
            }
            if (i < j)
                swap(nums[i], nums[j]);
            else
                break;
        }
        swap(nums[i], nums[r]);
        if (i < k)
            return quickselect(nums, i + 1, r, k);
        else if (i > k)
            return quickselect(nums, l, i - 1, k);
        else
            return nums[i];
    }

    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        return quickselect(nums, 0, n - 1, n - k);
    }
};
