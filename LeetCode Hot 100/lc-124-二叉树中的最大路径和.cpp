// 递归
// maxPathSumIncludeRoot表示以根节点为起点的路径的最大路径和，值得注意的是函数返回的是根节点值+左右子树中贡献值中的最大值，但是计算题目要求的最大路径和时要把左右子树的贡献值都算上

class Solution {
    int res = INT_MIN;

public:
    int maxPathSum(TreeNode* root) {
        maxPathSumIncludeRoot(root);
        return res;
    }

    int maxPathSumIncludeRoot(TreeNode* root) {
        if (root == nullptr)
            return 0;
        int l = max(0, maxPathSumIncludeRoot(root->left));
        int r = max(0, maxPathSumIncludeRoot(root->right));
        res = max(res, root->val + l + r);
        return root->val + max(l, r);
    }
};
