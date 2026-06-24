#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
//  最长公共子序列 (LCS)，不要求连续，但要求相对 
void solveLCS() {
    cout << "========== 1. 最长公共子序列 (LCS) ==========" << endl;
    string X = "pear";
    string Y = "peach";
    int m = X.length();
    int n = Y.length();

    // dp[i][j] 记录 X 前 i 个字符和 Y 前 j 个字符的 LCS 长度
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // 填充 DP 表
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // 回溯寻找具体的公共子序列
    int i = m, j = n;
    string lcs = "";
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs += X[i - 1];
            i--; j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            //说明跳过了 X 的当前字符
            i--;
        } else {
            j--;
            //说明跳过了 Y 的当前字符
        }
    }
    reverse(lcs.begin(), lcs.end());

    cout << "输入字符串 1: " << X << "\n输入字符串 2: " << Y << endl;
    cout << "最长公共子序列长度为: " << dp[m][n] << endl;
    cout << "最长公共子序列为: " << lcs << endl;
}

int main() {
    solveLCS();
    return 0;
}
