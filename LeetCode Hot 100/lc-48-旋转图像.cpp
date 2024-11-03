// 先以左下-右上对角条线为轴做翻转
// 再以中心的竖线为轴做翻转
// 时间复杂度：O(n^2)
// 空间复杂度：O(1)
  
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for (int i = 1; i < n; ++i)
            for (int j = 0; j < i; ++j)
                swap(matrix[i][j], matrix[j][i]);

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n / 2; ++j)  //这里本是j<n-1-j,即2*j<n-1,考虑到除法向下取整则转换为j<((n-1)+1)/2
                swap(matrix[i][j], matrix[i][n - 1 - j]);
    }
};
