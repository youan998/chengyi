#include <iostream>
#include <vector>

using namespace std;

int N = 8;
int total_solutions = 0;
vector<int> queen_pos; // 记录每行皇后的列号
vector<bool> col_used, diag1_used, diag2_used;// 记录列和对角线是否被占用   

void printSolution() {
    // 这里只打印前2种解的具体布局，但统计所有解的数量
    if (total_solutions <= 2) {
        cout << "第 " << total_solutions << " 种解：" << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (queen_pos[i] == j) cout << "Q ";
                else cout << ". ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

void solveNQueens(int row) {
    if (row == N) {
        total_solutions++;// 找到一个解，统计数量并打印前2种解
        printSolution();
        return;
    }
    for (int col = 0; col < N; col++) {
        // diag1: row + col;  diag2: row - col + N - 1
        if (!col_used[col] && !diag1_used[row + col] && !diag2_used[row - col + N - 1]) {
            // 放置皇后
            queen_pos[row] = col;
            col_used[col] = diag1_used[row + col] = diag2_used[row - col + N - 1] = true;
            
            solveNQueens(row + 1); // 递归到下一行
            
            // 回溯，撤销放置
            col_used[col] = diag1_used[row + col] = diag2_used[row - col + N - 1] = false;
        }
    }
}

int main() {
    cout << "========== 八皇后问题 ==========" << endl;
    N = 8;
    queen_pos.assign(N, 0);
    col_used.assign(N, false);// 记录列是否被占用   
    diag1_used.assign(2 * N - 1, false);// 记录主对角线是否被占用   
    diag2_used.assign(2 * N - 1, false);// 记录副对角线是否被占用                   
    
    solveNQueens(0);
    cout << N << " 皇后问题共有 " << total_solutions << " 种解法。" << endl;
    return 0;
}