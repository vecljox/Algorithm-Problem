// 递归

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 如果根节点为空或找到目标节点，直接返回当前节点
        if (root == nullptr || root == p || root == q)
            return root;

        // 递归查找左右子树
        auto left = lowestCommonAncestor(root->left, p, q);
        auto right = lowestCommonAncestor(root->right, p, q);

        // 如果左右子树都返回非空节点，说明当前节点是最近公共祖先
        if (left && right)
            return root;

        // 否则返回非空的子树
        return left ? left : right;
    }
};
