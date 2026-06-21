#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// ==========================================
//  1. 字符串处理: LCS + KMP
//  LCS: 动态规划 O(m*n)
//  KMP: next 数组 + 失配跳转 O(n+m)
// ==========================================

// ---------- 1.1 最长公共子序列 (LCS) ----------
void solveLCS() {
    cout << "--- LCS 最长公共子序列 ---" << endl;
    string X = "ABCBDAB";
    string Y = "BDCABA";
    int m = X.length(), n = Y.length();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // 填充 DP 表
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    cout << "  字符串1: " << X << endl;
    cout << "  字符串2: " << Y << endl;
    cout << "  LCS 长度: " << dp[m][n] << endl;

    // 回溯输出 LCS 序列
    string lcs;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs += X[i - 1];
            i--; j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    reverse(lcs.begin(), lcs.end());
    cout << "  LCS 序列: " << lcs << endl << endl;
}

// ---------- 1.2 KMP 模式匹配 ----------
// 构建 next 数组（前缀函数）
vector<int> getNext(const string& pattern) {
    int m = pattern.length();
    vector<int> next(m, 0);
    int j = 0;
    for (int i = 1; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j])
            j = next[j - 1];
        if (pattern[i] == pattern[j])
            j++;
        next[i] = j;
    }
    return next;
}

void solveKMP() {
    cout << "--- KMP 模式匹配 ---" << endl;
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";

    cout << "  主串:   " << text << endl;
    cout << "  模式串: " << pattern << endl;

    // 输出 next 数组
    vector<int> next = getNext(pattern);
    cout << "  next 数组: ";
    for (int i = 0; i < (int)pattern.length(); i++) {
        cout << "[" << i << "]" << pattern[i] << "=" << next[i] << " ";
    }
    cout << endl;

    // KMP 搜索
    int j = 0;
    bool found = false;
    for (int i = 0; i < (int)text.length(); i++) {
        while (j > 0 && text[i] != pattern[j])
            j = next[j - 1];
        if (text[i] == pattern[j])
            j++;
        if (j == (int)pattern.length()) {
            cout << "  匹配成功! 起始索引: " << i - j + 1 << endl;
            j = next[j - 1];  // 继续搜索下一个匹配
            found = true;
        }
    }
    if (!found) cout << "  匹配失败" << endl;
    cout << endl;
}

int main() {
    cout << "========== 1. 字符串处理 (LCS & KMP) ==========\n" << endl;
    solveLCS();
    solveKMP();
    return 0;
}
