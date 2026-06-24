#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// ==========================================
//  3. Tight Word 问题
//  dp[i][j]: 长度为 i，以数字 j 结尾的 tight word 数量
//  转移: dp[i][j] = dp[i-1][j-1] + dp[i-1][j] + dp[i-1][j+1]
//  比率 = sum(dp[n][j]) / (k+1)^n * 100%
// ==========================================

void solveTightWord(int k, int n) {
    // dp[i][j] 表示长度为 i，以数字 j 结尾的 tight word 数量
    vector<vector<double>> dp(n + 1, vector<double>(k + 1, 0.0));

    // 初始化：长度为 1 时，每种数字各一个
    for (int j = 0; j <= k; ++j)
        dp[1][j] = 1.0;

    // DP 转移
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j <= k; ++j) {
            if (j > 0) dp[i][j] += dp[i - 1][j - 1];// 来源于小一点的数字
            dp[i][j] += dp[i - 1][j];// 来源于相同的数字
            if (j < k) dp[i][j] += dp[i - 1][j + 1];// 来源于大一点的数字
        }
    }

    // 统计 tight word 总数
    double tight_sum = 0.0;
    for (int j = 0; j <= k; ++j)
        tight_sum += dp[n][j];

    // 总可能单词数
    double total_words = pow(k + 1, n);//k+1

    // 比率
    double ratio = (tight_sum / total_words) * 100.0;

    cout << fixed << setprecision(5);
    cout << "  k=" << k << ", n=" << n << endl;
    cout << "  Tight 词数量: " << (long long)tight_sum << endl;
    cout << "  总词数量:     " << total_words << endl;
    cout << "  比率:         " << ratio << "%" << endl << endl;
}

int main() {
    cout << "========== 3. Tight Word 问题 ==========\n" << endl;

    // 多组测试样例
    solveTightWord(2, 4);   // k=2 (数字 0,1,2), n=4
    solveTightWord(3, 3);   // k=3 (数字 0,1,2,3), n=3
    solveTightWord(9, 5);   // k=9 (数字 0-9), n=5
    solveTightWord(5, 8);   // k=5, n=8

    // 交互式输入
    cout << "--- 自定义测试 ---" << endl;
    int k, n;
    cout << "输入 k n (回车跳过): ";
    if (cin >> k >> n) {
        solveTightWord(k, n);
    }

    return 0;
}
