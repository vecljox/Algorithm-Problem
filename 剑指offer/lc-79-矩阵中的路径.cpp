class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {

        int row = board.size();
        int col  = board[0].size();
        int len = word.length();

        for(int i =0;i<row;++i)
        {
            for(int j =0;j<col;++j)
            {
                if(dfs(board,i,j,word,0))
                    return true;
            }
        }

        return false;
    }

    bool dfs(vector<vector<char>>& board,int i, int j, string word,int len)
    {
        int row = board.size();
        int col  = board[0].size();

        if(i<0||i>=row||j<0||j>=col||board[i][j]!=word[len])
            return false;

        if(len == word.length()-1)
            return true;

        board[i][j]='\v';

        bool res = dfs(board,i,j+1,word,len+1)
            ||dfs(board,i+1,j,word,len+1)
            ||dfs(board,i,j-1,word,len+1)
            ||dfs(board,i-1,j,word,len+1);

        board[i][j]=word[len];

        return res;
    }
};
