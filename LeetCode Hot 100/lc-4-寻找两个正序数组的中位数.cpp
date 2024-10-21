// 二分
// https://www.acwing.com/solution/content/50/
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int total = nums1.size() + nums2.size();
        if (total % 2 == 0)
        {
            int left = findKthNumber(nums1, 0, nums2, 0, total / 2);
            int right = findKthNumber(nums1, 0, nums2, 0, total / 2 + 1);
            return (left + right) / 2.0;
        }
        else
        {
            return findKthNumber(nums1, 0, nums2, 0, total / 2 + 1);
        }
    }

    int findKthNumber(vector<int> &nums1, int i, vector<int> &nums2, int j, int k)
    {
        if (nums1.size() - i > nums2.size() - j) return findKthNumber(nums2, j, nums1, i, k);
        if (nums1.size() == i) return nums2[j + k - 1];
        if (k == 1) return min(nums1[i], nums2[j]);
        int si = min(i + k / 2, int(nums1.size())), sj = j + k / 2;
        if (nums1[si - 1] > nums2[sj - 1])
        {
            return findKthNumber(nums1, i, nums2, sj, k - k / 2);
        }
        else
        {
            return findKthNumber(nums1, si, nums2, j, k - (si - i));
        }
    }
};

// //findKthNumber迭代版本
// int findKthNumber(vector<int>& nums1, int i, vector<int>& nums2, int j, int k) {
//     while (true) {
//         if (nums1.size() - i > nums2.size() - j) {
//             swap(nums1, nums2);
//             swap(i, j);
//         }
//         if (nums1.size() == i)
//             return nums2[j + k - 1];
//         if (k == 1)
//             return min(nums1[i], nums2[j]);
//         int si = min(i + k / 2, int(nums1.size())), sj = j + k / 2;
//         if (nums1[si - 1] > nums2[sj - 1]) {
//             k -= k / 2;
//             j = sj;
//         } else {
//             k -= (si - i);
//             i = si;
//         }
//     }
// }
