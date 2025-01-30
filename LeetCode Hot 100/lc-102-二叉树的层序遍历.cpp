// 利用队列的长度去判断每次遍历的次数，避免创建第二个队列带来的空间开销

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        queue<TreeNode*> q;
        if (root)
            q.push(root);
        while (!q.empty()) {
            int curLevelSize = q.size();
            res.push_back(vector<int>{});
            while (curLevelSize--) {
                auto curNode = q.front();
                q.pop();
                res.back().push_back(curNode->val);
                if (curNode->left)
                    q.push(curNode->left);
                if (curNode->right)
                    q.push(curNode->right);
            }
        }
        return res;
    }
};
