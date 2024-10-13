// 自底向上处理  时间复杂度：O(N)  空间复杂度O(N)

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
public:
    bool isBalanced(TreeNode* root) { return recur(root) != -1; }

    int recur(TreeNode* root) {
        if (root == nullptr)
            return 0;
        int left = recur(root->left);
        if (left == -1)
            return -1;
        int right = recur(root->right);
        if (right == -1)
            return -1;
        return abs(left - right) <= 1 ? 1 + max(left, right) : -1;
    }
};

// 自顶向下递归  时间复杂度：O(NlogN)  空间复杂度O(N)

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class SolutionB {
public:
    bool isBalanced(TreeNode* root) {
        if (root == nullptr)
            return true;
        return abs(getHeight(root->left) - getHeight(root->right)) <= 1 &&
               isBalanced(root->left) && isBalanced(root->right);
    }

    int getHeight(TreeNode* root) {
        if (root == nullptr)
            return 0;
        return 1 + max(getHeight(root->left), getHeight(root->right));
    }
};
