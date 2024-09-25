/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        return isSymmetric(root->left,root->right);
    }

    bool isSymmetric(TreeNode* A,TreeNode* B)
    {
        if(A==nullptr&&B==nullptr)
            return true;

        if(A==nullptr||B==nullptr)
            return false;

        return A->val==B->val&&isSymmetric(A->left,B->right)&&isSymmetric(A->right,B->left);
    }
};
