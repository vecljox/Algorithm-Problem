// 递归版本，自顶向下
void mergeSort(vector<int> &nums, int l, int r)
{
    if (l >= r)
        return;
    int mid = l + r >> 1;
    mergeSort(nums, l, mid);
    mergeSort(nums, mid + 1, r);

    std::vector<int> tmp(r - l + 1);
    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r)
    {
        if (nums[i] <= nums[j])
            tmp[k++] = nums[i++];
        else
            tmp[k++] = nums[j++];
    }
    while (i <= mid)
        tmp[k++] = nums[i++];
    while (j <= r)
        tmp[k++] = nums[j++];

    for (int i = l, j = 0; i <= r; ++i, ++j)
        nums[i] = tmp[j];
}

// 迭代版本，自底向上
std::vector<int> mergeSort(std::vector<int> &nums)
{
    int n = nums.size();
    std::vector<int> tmp(n);
    for (int i = 1; i < n; i *= 2)
    {
        int k = 0;
        for (int j = 0; j < n; j += 2 * i)
        {
            int p = j, q = j + i;
            int end_p = std::min(j + i, n), end_q = std::min(j + 2 * i, n);

            while (p < end_p && q < end_q)
            {
                if (nums[p] <= nums[q])
                    tmp[k++] = nums[p++];
                else
                    tmp[k++] = nums[q++];
            }
            while (p < end_p)
            {
                tmp[k++] = nums[p++];
            }
            while (q < end_q)
            {
                tmp[k++] = nums[q++];
            }
        }
        nums.swap(tmp);
    }
    return nums;
}

