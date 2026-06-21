#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int ROW = 5;
const int COL = 5;

// 迷宫地图，0表示通，1表示墙
int maze[ROW][COL] = {
    {0, 1, 0, 0, 0},
    {0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0}
};

int visited[ROW][COL] = {0};
// 方向数组：上下左右
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

struct Point { int x, y; };
vector<Point> path1, path2;

// ========== DFS ==========
bool dfs(int x, int y) {
    if (x == ROW - 1 && y == COL - 1) {
        path1.push_back({x, y});
        return true;
    }

    visited[x][y] = 1;
    path1.push_back({x, y});

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < ROW && ny >= 0 && ny < COL
            && maze[nx][ny] == 0 && !visited[nx][ny]) {
            if (dfs(nx, ny)) return true;
        }
    }

    // 回溯
    path1.pop_back();
    visited[x][y] = 0;
    return false;
}

// ========== BFS ==========
bool bfs(int startX, int startY) {
    // BFS 用自己的 visited数组，避免与 DFS 冲突    
    int bfsVisited[ROW][COL] = {0};
    Point prev[ROW][COL];  // 记录每个点的前驱，用于反推路径

    queue<Point> q;
    q.push({startX, startY});
    bfsVisited[startX][startY] = 1;
    prev[startX][startY] = {-1, -1};  // 起点标记无前驱

    while (!q.empty()) {
        Point cur = q.front();
        q.pop();

        if (cur.x == ROW - 1 && cur.y == COL - 1) {
            // 反推路径，从终点回溯到起点
            Point p = cur;
            while (!(p.x == -1 && p.y == -1)) {
                path2.push_back(p);
                p = prev[p.x][p.y];
            }
            // 反转得到从起点到终点的顺序
            reverse(path2.begin(), path2.end());
            return true;
        }

        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (nx >= 0 && nx < ROW && ny >= 0 && ny < COL
                && maze[nx][ny] == 0 && !bfsVisited[nx][ny]) {
                bfsVisited[nx][ny] = 1;
                prev[nx][ny] = cur;
                q.push({nx, ny});
            }
        }
    }
    return false;
}

int main() {
    cout << "========== 走迷宫问题 ==========" << endl;

    // DFS
    if (dfs(0, 0)) {
        cout << "DFS 找到一条路径：" << endl;
        for (auto p : path1) {
            cout << "(" << p.x << ", " << p.y << ") -> ";
        }
        cout << "终点" << endl;
    } else {
        cout << "DFS 无路可走！" << endl;
    }

    // BFS（visited 独立，不受 DFS 影响）
    if (bfs(0, 0)) {
        cout << "BFS 找到最短路径！" << endl;
        for (auto p : path2) {
            cout << "(" << p.x << ", " << p.y << ") -> ";
        }
        cout << "终点" << endl;
    } else {
        cout << "BFS 无路可走！" << endl;
    }

    return 0;
}
