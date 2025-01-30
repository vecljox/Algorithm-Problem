// 用哈希表存储根节点元素在inorder中的索引


class Solution {
    unordered_map<int, int> index;

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        for (int i = 0; i < n; ++i)
            index[inorder[i]] = i;
        return buildTree(preorder, inorder, 0, n - 1, 0, n - 1);
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder, int pl,
                        int pr, int il, int ir) {
        if (pl > pr)
            return nullptr;

        int val = preorder[pl];
        int rootIndexInInorder = index[val];
        auto root = new TreeNode(val);

        int left_pr = pl + (rootIndexInInorder - il);
        root->left = buildTree(preorder, inorder, pl + 1, left_pr, il,
                               rootIndexInInorder - 1);
        root->right = buildTree(preorder, inorder, left_pr + 1, pr,
                                rootIndexInInorder + 1, ir);

        return root;
    }
};
