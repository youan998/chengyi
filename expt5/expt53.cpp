#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ==========================================
//  机器人运动情况
//  用 visited[row][col] 记录到达每个格子的步数
//  越界 → 成功走出
//  visited > 0 → 陷入死循环，循环长度 = 当前步数+1 - 历史步数
// ==========================================

void solveRobot() {
    vector<string> grid = {
        "NEESWE",
        "WWWESS",
        "SNWWWW"
    };
    int rows = grid.size();
    int cols = grid[0].size();
    int r = 0, c = 0;   // 从 (0,0) 出发
    int steps = 0;

    // visited 记录到达每个格子的步数（从1开始），0表示未访问
    vector<vector<int>> visited(rows, vector<int>(cols, 0));

    cout << "网格 (" << rows << " x " << cols << "):" << endl;
    for (const auto& row : grid) {
        cout << "  ";
        for (char ch : row) cout << ch << " ";
        cout << endl;
    }
    cout << "\n从 (0,0) 出发...\n" << endl;

    while (true) {
        // 检查是否越界
        if (r < 0 || r >= rows || c < 0 || c >= cols) {
            cout << "✓ 走出网格！共 " << steps << " 步。" << endl;
            break;
        }

        // 检查是否陷入循环
        if (visited[r][c] > 0) {
            int loopStart = visited[r][c];      // 循环开始时的步数
            int loopLen = steps + 1 - loopStart; // 循环长度
            cout << "✗ 陷入循环！" << endl;
            cout << "  循环前走了 " << (loopStart - 1) << " 步" << endl;
            cout << "  循环长度: " << loopLen << " 步" << endl;
            cout << "  循环涉及格子步数范围: [" << loopStart << ", " << steps << "]" << endl;
            break;
        }

        steps++;
        visited[r][c] = steps;
        char dir = grid[r][c];

        cout << "第" << steps << "步: 到达 (" << r << "," << c
             << ") 方向='" << dir << "' → ";

        // 按方向移动
        if (dir == 'N')      { r--; cout << "向上"; }
        else if (dir == 'S') { r++; cout << "向下"; }
        else if (dir == 'E') { c++; cout << "向右"; }
        else if (dir == 'W') { c--; cout << "向左"; }

        cout << " → 下一位置 (" << r << "," << c << ")" << endl;
    }

    // 打印 visited 矩阵
    cout << "\nvisited 步数矩阵:" << endl;
    for (int i = 0; i < rows; ++i) {
        cout << "  ";
        for (int j = 0; j < cols; ++j) {
            printf("%2d ", visited[i][j]);
        }
        cout << endl;
    }
}

int main() {
    cout << "========== a(3). 机器人运动情况 ==========\n" << endl;
    solveRobot();
    return 0;
}
