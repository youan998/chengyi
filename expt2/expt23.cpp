#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int SIZE = 8;
int board[SIZE][SIZE];// 棋盘，-1表示未访问，其他数字表示走的步数   
// 骑士走日字的8个方向
int cx[8] = {1, 1, 2, 2, -1, -1, -2, -2};
int cy[8] = {2, -2, 1, -1, 2, -2, 1, -1};

bool isSafe(int x, int y) {
    return (x >= 0 && x < SIZE && y >= 0 && y < SIZE && board[x][y] == -1);
}

// 计算某位置下一步的可走位置数量
int getDegree(int x, int y) {
    int count = 0;
    for (int i = 0; i < 8; ++i) {
        if (isSafe(x + cx[i], y + cy[i])) count++;
    }
    return count;
}

bool solveKnightTour(int x, int y, int step) {
    board[x][y] = step;
    if (step == SIZE * SIZE) return true; // 已遍历满64格

    // 收集所有可走的下一步
    vector<pair<int, int>> next_moves;
    for (int i = 0; i < 8; ++i) {
        int nx = x + cx[i];
        int ny = y + cy[i];
        if (isSafe(nx, ny)) {
            next_moves.push_back({getDegree(nx, ny), i}); // 存储 (度数, 方向索引)
        }
    }

    // 按照 Warnsdorff 规则，根据下一步的可走度数升序排序
    sort(next_moves.begin(), next_moves.end());

    // 优先走度数最小的分支
    for (auto move : next_moves) {
        int dir = move.second;
        if (solveKnightTour(x + cx[dir], y + cy[dir], step + 1)) {
            return true;
        }
    }
    // 回溯
    board[x][y] = -1;
    return false;
}

int main() {
    cout << "==========骑士游历问题 ==========" << endl;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = -1;

    int start_x = 0, start_y = 0; // 给定起始顶点
    if (solveKnightTour(start_x, start_y, 1)) {
        cout << "找到一条游历路径（数字代表走步顺序）：" << endl;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                printf("%2d ", board[i][j]);
            }
            cout << endl;
        }
    } else {
        cout << "无法完成游历" << endl;
    }
    return 0;
}