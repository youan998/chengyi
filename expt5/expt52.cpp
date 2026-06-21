#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ==========================================
//  The Same Game (消消方块)
//  三个独立动作:
//    1. DFS 连通块消除
//    2. 垂直压缩 (Gravity)
//    3. 水平平移 (Shift)
// ==========================================

int r_max = 5, c_max = 5;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// ---- 1. DFS 清除同色连通块 ----
void dfs_clear(vector<string>& grid, int r, int c, char color) {
    if (r < 0 || r >= r_max || c < 0 || c >= c_max) return;
    if (grid[r][c] != color) return;
    grid[r][c] = '.';
    for (int i = 0; i < 4; ++i) {
        dfs_clear(grid, r + dx[i], c + dy[i], color);
    }
}

// ---- 2. 下落 (Gravity)：非空方块下沉 ----
void applyGravity(vector<string>& grid) {
    for (int c = 0; c < c_max; ++c) {
        int write_idx = r_max - 1;  // 从最底部开始写
        for (int r = r_max - 1; r >= 0; --r) {
            if (grid[r][c] != '.') {
                grid[write_idx][c] = grid[r][c];
                write_idx--;
            }
        }
        // 剩余位置填充空白
        while (write_idx >= 0) {
            grid[write_idx][c] = '.';
            write_idx--;
        }
    }
}

// ---- 3. 左移 (Shift)：空列右侧左移 ----
void shiftLeft(vector<string>& grid) {
    int write_col = 0;
    for (int c = 0; c < c_max; ++c) {
        // 检查该列是否为空（看最底部是否有方块）
        if (grid[r_max - 1][c] != '.') {
            if (write_col != c) {
                for (int r = 0; r < r_max; ++r) {
                    grid[r][write_col] = grid[r][c];
                    grid[r][c] = '.';
                }
            }
            write_col++;
        }
    }
}

// ---- 打印网格 ----
void printGrid(const vector<string>& grid, const string& title) {
    cout << title << ":" << endl;
    for (int r = 0; r < r_max; ++r) {
        cout << "  ";
        for (int c = 0; c < c_max; ++c) {
            cout << grid[r][c] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    cout << "========== b. The Same Game (消消方块) ==========\n" << endl;

    // 初始游戏状态
    vector<string> grid = {
        "ABBAA",
        "BBABB",
        "ABABA",
        "BBBAA",
        "ABABB"
    };

    printGrid(grid, "初始状态");

    // 示例：点击 (2,2) 位置，颜色为 'A'
    int clickR = 2, clickC = 2;
    char color = grid[clickR][clickC];
    cout << "点击位置 (" << clickR << ", " << clickC << ") 颜色='" << color << "'" << endl;

    // 步骤1: 消除连通块
    dfs_clear(grid, clickR, clickC, color);
    printGrid(grid, "步骤1: 消除连通块后");

    // 步骤2: 垂直下落
    applyGravity(grid);
    printGrid(grid, "步骤2: 重力下落后");

    // 步骤3: 水平左移
    shiftLeft(grid);
    printGrid(grid, "步骤3: 左移后");

    // ---- 第二轮演示 ----
    cout << "---------- 第二轮 ----------" << endl;
    if (grid[r_max - 1][1] != '.') {
        dfs_clear(grid, r_max - 1, 1, grid[r_max - 1][1]);
        printGrid(grid, "步骤1: 消除连通块后");
        applyGravity(grid);
        printGrid(grid, "步骤2: 重力下落后");
        shiftLeft(grid);
        printGrid(grid, "步骤3: 左移后");
    }

    return 0;
}
