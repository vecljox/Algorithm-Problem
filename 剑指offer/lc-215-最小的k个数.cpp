//堆
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        // 构建最大堆
        for (int i = (n - 1) / 2; i >= 0; --i) {
            percDown(nums, i, n);
        }
        // 执行 k-1 次删除堆顶操作
        for (int i = n - 1; --k > 0; --i) {
            nums[0] = nums[i];
            percDown(nums, 0, i);
        }
        return nums[0];
    }

    void percDown(vector<int>& nums, int i, int n) {
        int tmp = nums[i]; // 保存当前节点的值
        while (2 * i + 1 < n) {
            int child = 2 * i + 1; // 左子节点
            // 如果右子节点存在且比左子节点大，则选择右子节点
            if (child != n - 1 && nums[child] < nums[child + 1]) {
                ++child;
            }
            // 如果子节点比当前节点大，则交换
            if (tmp < nums[child]) {
                nums[i] = nums[child];
                i = child;
            } else {
                break;
            }
        }
        nums[i] = tmp; // 将 tmp 放到最终的位置
    }
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
