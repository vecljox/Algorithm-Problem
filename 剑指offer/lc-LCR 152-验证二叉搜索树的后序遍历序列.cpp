//辅助单调栈
class Solution {
public:
    bool verifyTreeOrder(vector<int>& postorder) {
        stack<int> stk;
        int root = INT_MAX;
        for(int i =postorder.size()-1;i>=0;--i)
        {
            if(postorder[i]>root)   return false;
            while(!stk.empty()&&stk.top()>postorder[i])
            {
                root = stk.top();
                stk.pop();
            }
            stk.push(postorder[i]);
        }
        return true;
    }
};

//递归
class SolutionB {
public:
    bool verifyTreeOrder(vector<int>& postorder) {
        return verifyTreeOrder(postorder,0,postorder.size()-1);
    }

    bool verifyTreeOrder(vector<int>& postorder,int i,int j)
    {
        if(i>=j-1)    return true;  //序列大小不超过2一定满足后序遍历
        int p=i;
        while(postorder[p]<postorder[j])    ++p;
        int m = p;
        while(postorder[p]>postorder[j])    ++p;
        return p==j&&verifyTreeOrder(postorder,i,m-1)&&verifyTreeOrder(postorder,m,j-1);
    }
};
