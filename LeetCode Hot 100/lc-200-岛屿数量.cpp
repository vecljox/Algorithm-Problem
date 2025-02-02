// 深度优先遍历
// 时间复杂度：O(MN)，其中 M 和 N 分别为行数和列数。
// 空间复杂度：O(MN)，在最坏情况下，整个网格均为陆地，深度优先搜索的深度达到 MN。
// 其实广度优先遍历在空间复杂度上表现更好，但是感觉深度优先容易写就放前面了

class Solution {
public:
    int m;
    int n;

    int numIslands(vector<vector<char>>& grid) {
        int res = 0;
        m = grid.size();
        n = grid[0].size();

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1') {
                    ++res;
                    dfs(grid, i, j);
                }
            }
        }
        return res;
    }

    void dfs(vector<vector<char>>& grid, int i, int j) {

        grid[i][j] = '0';
        if (i - 1 >= 0 && grid[i - 1][j] == '1')
            dfs(grid, i - 1, j);
        if (i + 1 < m && grid[i + 1][j] == '1')
            dfs(grid, i + 1, j);
        if (j - 1 >= 0 && grid[i][j - 1] == '1')
            dfs(grid, i, j - 1);
        if (j + 1 < n && grid[i][j + 1] == '1')
            dfs(grid, i, j + 1);
    }
};

// 广度优先遍历
// 时间复杂度：O(MN)，其中 M 和 N 分别为行数和列数。
// 空间复杂度：O(min(M,N))，在最坏情况下，整个网格均为陆地，队列的大小可以达到 min(M,N)
// 注意将要处理的节点推进队列后得把该点的值置为'0'，而不是在while循环的开头再去置'0'，否则可能会超时

class SolutionB {
public:
    int numIslands(vector<vector<char>>& grid) {
        int res = 0;
        int m = grid.size();
        int n = grid[0].size();

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1') {
                    ++res;
                    queue<pair<int, int>> q;
                    q.push({i, j});
                    grid[i][j] = '0';
                    while (!q.empty()) {
                        auto tmp = q.front();
                        q.pop();
                        int row = tmp.first, col = tmp.second;

                        if (row - 1 >= 0 && grid[row - 1][col] == '1') {
                            q.push({row - 1, col});
                            grid[row - 1][col] = '0';
                        }
                        if (row + 1 < m && grid[row + 1][col] == '1') {
                            q.push({row + 1, col});
                            grid[row + 1][col] = '0';
                        }
                        if (col - 1 >= 0 && grid[row][col - 1] == '1') {
                            q.push({row, col - 1});
                            grid[row][col - 1] = '0';
                        }
                        if (col + 1 < n && grid[row][col + 1] == '1') {
                            q.push({row, col + 1});
                            grid[row][col + 1] = '0';
                        }
                    }
                }
            }
        }
        return res;
    }
};
