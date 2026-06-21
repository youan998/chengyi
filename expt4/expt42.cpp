#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// ========== 2. 字符串编辑距离 ==========
void solveEditDistance() {
    cout << "========== 2. 字符串编辑距离 ==========" << endl;
    string a = "horse";
    string b = "ros";
    int m = a.length(), n = b.length();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // 边界条件初始化
    for (int i = 0; i <= m; i++) dp[i][0] = i; // a 全部删除变成空串
    for (int j = 0; j <= n; j++) dp[0][j] = j; // 空串全部插入变成 b

    // 状态转移
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min({dp[i - 1][j - 1],    // 替换
                                    dp[i - 1][j],          // 删除
                                    dp[i][j - 1]});        // 插入
            }
        }
    }

    cout << "将 '" << a << "' 转换为 '" << b << "' 的最少操作次数: " << dp[m][n] << endl;

    // 回溯输出步骤
    cout << "变换步骤如下：" << endl;
    int i = m, j = n;
    vector<string> steps;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && a[i - 1] == b[j - 1]) {
            i--; j--; // 字符相同，无操作
        } else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1) {
            steps.push_back("替换: 将 " + string(1, a[i - 1]) + " 替换为 " + string(1, b[j - 1]));
            i--; j--;
        } else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
            steps.push_back("删除: 删除字符 " + string(1, a[i - 1]));
            i--;
        } else if (j > 0 && dp[i][j] == dp[i][j - 1] + 1) {
            steps.push_back("插入: 插入字符 " + string(1, b[j - 1]));
            j--;
        }
    }
    // 步骤是逆向回溯的，需要倒序输出
    for (int k = steps.size() - 1; k >= 0; k--) {
        cout << " -> " << steps[k] << endl;
    }
}

int main() {
    solveEditDistance();
    return 0;
}
