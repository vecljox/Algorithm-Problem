class Solution {
public:
    int m, n;
    bool exist(vector<vector<char>>& board, string word) {
        m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (dfs(board, i, j, word, 0))
                    return true;
            }
        }
        return false;
    }

    bool dfs(vector<vector<char>>& board, int i, int j, const string& word,
             int len) {
        if (i < 0 || i >= m || j < 0 || j >= n || board[i][j] != word[len])
            return false;

        if (len == word.size() - 1)
            return true;

        board[i][j] = '\0';    //标记被访问过

        bool res = dfs(board, i, j + 1, word, len + 1) ||
                   dfs(board, i + 1, j, word, len + 1) ||
                   dfs(board, i, j - 1, word, len + 1) ||
                   dfs(board, i - 1, j, word, len + 1);

        board[i][j] = word[len];

        return res;
    }
};
