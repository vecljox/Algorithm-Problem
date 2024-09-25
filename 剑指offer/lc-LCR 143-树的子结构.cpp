/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if(A==nullptr||B==nullptr)
            return false;

        return isSameStructure(A,B)||isSubStructure(A->left,B)||isSubStructure(A->right,B);
    }

    bool isSameStructure(TreeNode* A, TreeNode* B)
    {
        if(B==nullptr)
            return true;

        if(A==nullptr)
            return false;

        return A->val==B->val&&isSameStructure(A->left,B->left)&&isSameStructure(A->right,B->right);
    }
};
