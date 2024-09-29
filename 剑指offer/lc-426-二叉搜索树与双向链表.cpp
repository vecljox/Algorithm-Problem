/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/

// 中序遍历
class Solution {
    Node* head = nullptr;
    Node* pre = nullptr;
public:
    Node* treeToDoublyList(Node* root) {
        if(root==nullptr)   return nullptr;
        inorder(root);
        head->left = pre;
        pre->right =head;
        return head;
    }

    void inorder(Node* root)
    {
        if(root==nullptr)   return;
        inorder(root->left);
        if(pre==nullptr)
            head=root;
        else
        {
            pre->right = root;
            root->left = pre;
        }
        pre = root;
        inorder(root->right);
    }

};

// 递归，我自己的做法
class SolutionB {
public:
    Node* treeToDoublyList(Node* root) {
        if(root==nullptr)   return nullptr;
        Node* l = treeToDoublyList(root->left);
        Node* r = treeToDoublyList(root->right);
        root->left=root;
        root->right=root;
        return merge(merge(l,root),r);
    }

    Node* merge(Node* l,Node* r)
    {
        if(l==nullptr)  return r;
        if(r==nullptr)  return l;

        Node* lEnd = l->left;
        Node* rEnd = r->left;

        lEnd->right = r;
        r->left=lEnd;

        l->left=rEnd;
        rEnd->right=l;

        return l;
    }
};
