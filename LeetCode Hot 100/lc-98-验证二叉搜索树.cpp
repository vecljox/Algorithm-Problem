// helper函数的意义是如果以root为根节点的二叉树是搜索树且每个节点值都处于区间(l,r)时，返回true，否则返回false
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return helper(root, LLONG_MIN, LLONG_MAX);
    }

    bool helper(TreeNode* root, long long l, long long r) {
        if (root == nullptr)
            return true;

        if (root->val <= l || root->val >= r)
            return false;

        return helper(root->left, l, root->val) &&
               helper(root->right, root->val, r);
    }
};

// 中序遍历，验证遍历的序列是否单调递增
class SolutionB {
public:
    bool isValidBST(TreeNode* root) {
        long long cur = (long long)INT_MIN - 1;
        stack<TreeNode*> stk;
        while (root || !stk.empty()) {
            while (root) {
                stk.push(root);
                root = root->left;
            }
            root = stk.top();
            stk.pop();
            if (root->val <= cur)
                return false;
            cur = root->val;
            root = root->right;
        }
        return true;
    }
};
