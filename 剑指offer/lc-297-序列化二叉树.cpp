/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// 别人的做法，很简洁！
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(root == nullptr)
            return "#";
       
        return to_string(root->val)+' '+serialize(root->left)+' '+serialize(root->right);
    }

    TreeNode* redeserialize(istringstream& ss)
    {
        string str;
        ss>>str;
        if(str=="#")
            return nullptr;

        TreeNode* root = new TreeNode(stoi(str));
        root->left = redeserialize(ss);
        root->right = redeserialize(ss);
        return root;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream ss(data);

        return redeserialize(ss);
    }
};


//自己做的，vector和迭代器
class CodecB {
public:
    void reserialize(TreeNode* root,string& str)
    {
        if(root==nullptr)
        {
            str+="None,";
        }
        else
        {
            str+= to_string(root->val)+',';
            reserialize(root->left,str);
            reserialize(root->right,str);
        }
    }

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string ret;
        reserialize(root,ret);
        return ret;
    }

    void redeserialize(vector<string>::iterator& it,TreeNode*& root)
    {
        if(*it=="None")
        {
            // root = nullptr;
            ++it; 
            return;
        }
        root = new TreeNode(stoi(*it));
        ++it;
        redeserialize(it,root->left);
        redeserialize(it,root->right);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<string> strings;
        string temp;
        stringstream ss{data};
        while(getline(ss,temp,','))
        {
            strings.push_back(temp);
        }

        auto it = strings.begin();
        TreeNode* ret = nullptr;
        redeserialize(it,ret);

        return ret;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
