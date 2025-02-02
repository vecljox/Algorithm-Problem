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
