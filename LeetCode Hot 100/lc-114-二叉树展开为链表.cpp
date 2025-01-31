// 反前序遍历
// 因为处理当前节点会破坏子树结构，所以把处理逻辑放在递归后面
// 并且递归的时候先递归右子树再递归左子树，那么顺序就变成了右左根，最后展开成链表时反着连接就是根左右，和前序遍历一样了

class Solution {
    TreeNode* pre = nullptr;

public:
    void flatten(TreeNode* root) {
        if (root == nullptr)
            return;
        flatten(root->right);
        flatten(root->left);
        root->left =nullptr;
        root->right=pre;
        pre = root;
    }
};


// 先前序遍历完再展开链表

class SolutionB {
    vector<TreeNode*> v;

public:
    void flatten(TreeNode* root) {
        preorder(root);
        v.push_back(nullptr);
        for (int i = 0; i < v.size() - 1; ++i) {
            v[i]->left = nullptr;
            v[i]->right = v[i + 1];
        }
    }

    void preorder(TreeNode* root) {
        if (root == nullptr)
            return;
        v.push_back(root);
        preorder(root->left);
        preorder(root->right);
    }
};
