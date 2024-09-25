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
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if(subRoot==nullptr)
            return true;

        if(root==nullptr)
            return false;

        return isEqual(root,subRoot)||isSubtree(root->left,subRoot)||isSubtree(root->right,subRoot);
    }

    bool isEqual(TreeNode* root, TreeNode* subRoot)
    {
        if(root==nullptr&&subRoot==nullptr)
            return true;

        if(root==nullptr||subRoot==nullptr)
            return false;

        return root->val==subRoot->val&&isEqual(root->left,subRoot->left)&&isEqual(root->right,subRoot->right);
    }
};
