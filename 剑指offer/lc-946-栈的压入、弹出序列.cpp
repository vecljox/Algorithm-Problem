class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        int stackIndex = -1;
        int len = pushed.size();

        for(int i=0,j=0;i<len;++i)
        {
            pushed[++stackIndex]=pushed[i];
            while(stackIndex>=0&&pushed[stackIndex]==popped[j])
            {
                --stackIndex;
                ++j;
            }
        }

        return stackIndex==-1;
    }
};

//pushed原地模拟栈
