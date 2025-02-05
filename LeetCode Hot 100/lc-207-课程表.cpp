// 广度优先搜索
// 我们使用一个队列来进行广度优先搜索。初始时，所有入度为 0 的节点都被放入队列中，它们就是可以作为拓扑排序最前面的节点，并且它们之间的相对顺序是无关紧要的。
// 在广度优先搜索的每一步中，我们取出队首的节点 u：
// 我们将 u 放入答案中；
// 我们移除 u 的所有出边，也就是将 u 的所有相邻节点的入度减少 1。如果某个相邻节点 v 的入度变为 0，那么我们就将 v 放入队列中。
// 在广度优先搜索的过程结束后。如果答案中包含了这 n 个节点，那么我们就找到了一种拓扑排序，否则说明图中存在环，也就不存在拓扑排序了。

// 由于我们只需要判断是否存在一种拓扑排序，因此我们省去存放答案数组，而是只用一个变量visited记录被放入答案数组的节点个数。在广度优先搜索结束之后，我们判断该变量的值是否等于课程数，就能知道是否存在一种拓扑排序。


class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> edges(numCourses);
        vector<int> indeg(numCourses);
        for (const auto& info : prerequisites) {
            edges[info[1]].push_back(info[0]);
            ++indeg[info[0]];
        }

        queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (indeg[i] == 0)
                q.push(i);
        }

        int visited = 0;
        while (!q.empty()) {
            ++visited;
            auto course = q.front();
            q.pop();
            for (int v : edges[course]) {
                --indeg[v];
                if (indeg[v] == 0)
                    q.push(v);
            }
        }

        return visited == numCourses;
    }
};
