// https://leetcode.cn/problems/gou-jian-cheng-ji-shu-zu-lcof/solutions/208840/mian-shi-ti-66-gou-jian-cheng-ji-shu-zu-biao-ge-fe
class Solution {
public:
    vector<int> statisticalResult(vector<int>& arrayA) {
        int n = arrayA.size();
        vector<int> arrayB(n, 1);
        int tmp = 1;
        for (int i = 1; i < n; ++i) {
            // tmp *= arrayA[i - 1];
            arrayB[i] = arrayB[i - 1] * arrayA[i - 1];
        }
        tmp = 1;
        for (int i = n - 2; i >= 0; --i) {
            tmp *= arrayA[i + 1];
            arrayB[i] *= tmp;
        }
        return arrayB;
    }
};
