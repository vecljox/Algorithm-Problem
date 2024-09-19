class Solution {
public: 
    int m;
    int n;
    int cnt;

    vector<vector<char>> visited;
    
    int wardrobeFinishing(int m, int n, int cnt) {
        this->m = m;
        this->n = n;
        this->cnt = cnt;

        visited = vector<vector<char>>(m,vector<char>(n,0));
    
        return dfs(0,0);
    }

    int dfs(int i,int j)
    {
        if(i<0||i>=m||j<0||j>=n||visited[i][j]||digit(i)+digit(j)>cnt)
            return 0;

        visited[i][j] = 1;
        
        return 1
        +dfs(i,j+1)
        +dfs(i+1,j)
        +dfs(i,j-1)
        +dfs(i-1,j);
        
    }

    int digit(int n)
    {
        int res = 0;
        while (n)
        {
            res += n % 10;
            n /= 10;
        }
        return res;
    }
};
