#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// ==========================================
//  4. 巧克力问题 (概率 DP)
//  dp[i][j]: 抽取 i 次后，桌面上有 j 块巧克力的概率
//  转移:
//    从 j-1 → j: 抽到新颜色，概率 (c - j + 1) / c
//    从 j+1 → j: 抽到已有颜色，概率 (j + 1) / c
//  奇偶性剪枝: 若 (n-m) 为奇数，概率必为 0
// ==========================================

void solveChocolate(int c, int n, int m) {
    cout << "  c=" << c << " (颜色数), n=" << n << " (抽取次数), m=" << m << " (目标桌面数)" << endl;

    // 剪枝：奇偶性不匹配或目标不合理
    if (m > c || m > n || (n - m) % 2 != 0) {
        cout << "  概率 = 0.000 (";
        if (m > c) cout << "m > c";
        else if (m > n) cout << "m > n";
        else cout << "奇偶性不匹配: n-m=" << (n - m) << " 为奇数";
        cout << ")" << endl << endl;
        return;
    }

    // dp[i][j]: 抽取 i 次后桌面上有 j 块的概率
    vector<vector<double>> dp(n + 1, vector<double>(c + 2, 0.0));
    dp[0][0] = 1.0;  // 初始状态

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= c; ++j) {
            // 从 j-1 转移：抽到新颜色，放在桌面上
            if (j > 0) {
                double p_new = (double)(c - (j - 1)) / c;
                dp[i][j] += dp[i - 1][j - 1] * p_new;
            }
            // 从 j+1 转移：抽到已有颜色，两块抵消
            if (j < c) {
                double p_old = (double)(j + 1) / c;
                dp[i][j] += dp[i - 1][j + 1] * p_old;
            }
        }
    }

    cout << fixed << setprecision(6);
    cout << "  概率 = " << dp[n][m] << endl << endl;
}

int main() {
    cout << "========== 4. 巧克力问题 (概率DP) ==========\n" << endl;

    // 测试样例
    cout << "--- 测试样例 ---" << endl;
    solveChocolate(5, 2, 2);   // 小数据
    solveChocolate(10, 4, 2);  // 中等数据
    solveChocolate(5, 3, 1);   // 奇偶性剪枝测试
    solveChocolate(5, 3, 3);   // 正常测试
    solveChocolate(10, 10, 4); // 大数据

    // 交互式测试
    cout << "--- 自定义测试 ---" << endl;
    int c, n, m;
    cout << "输入 c n m (回车跳过): ";
    if (cin >> c >> n >> m) {
        solveChocolate(c, n, m);
    }

    return 0;
}
