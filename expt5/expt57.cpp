#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ==========================================
//  BWT 变种 — 回溯法找环解密
//  加密: 循环移位 → stable_sort(按首字母) → 取尾字母
//  解密: F列 = sort(L列), 建立 L[i]→F[p] 的映射
//        利用 DFS 回溯找到能遍历所有 N 个节点
//        且回到原点的合法环 → 还原原文
// ==========================================

// ---- 加密 (与原版一致) ----
pair<string, int> bwtEncode(const string& plain) {
    int n = plain.size();
    if (n == 0) return {"", -1};

    vector<string> shifts(n);
    for (int i = 0; i < n; ++i) {
        shifts[i] = plain.substr(i) + plain.substr(0, i);
    }

    // 稳定排序：按首字母
    vector<int> idx(n);
    for (int i = 0; i < n; ++i) idx[i] = i;
    stable_sort(idx.begin(), idx.end(), [&](int a, int b) {
        return shifts[a] < shifts[b];
    });

    int originalIndex = -1;
    string cipher;
    for (int i = 0; i < n; ++i) {
        cipher += shifts[idx[i]].back();
        if (idx[i] == 0) originalIndex = i;
    }

    return {cipher, originalIndex};
}

// ---- 解密：构建依赖图 + DFS 回溯找环 ----
// 由于是稳定排序，同字符在 L 列出现的顺序与 F 列一致
// 建立 prev[i] 数组：对于 L 列第 i 个字符，它在 F 列中是第 k 次出现
// 则 L[i] 在原文中的前一个字符是 F 列中同字符的第 k 次出现

void buildPrevArray(const string& L, vector<int>& prev) {
    int n = L.size();
    string F = L;
    sort(F.begin(), F.end());

    // 统计每个字符在 L 中第几次出现
    vector<int> charCount(256, 0);
    vector<int> occurrence(n);
    for (int i = 0; i < n; ++i) {
        unsigned char c = L[i];
        occurrence[i] = charCount[c];
        charCount[c]++;
    }

    // 在 F 中找每个 L[i] 的对应位置
    vector<int> firstPos(256, -1);
    for (int i = 0; i < n; ++i) {
        unsigned char c = F[i];
        if (firstPos[c] == -1) firstPos[c] = i;
    }

    prev.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        unsigned char c = L[i];
        prev[i] = firstPos[c] + occurrence[i];
    }
}

// ---- 使用 DFS 回溯找到合法环，还原原文 ----
// 从每个可能的起点开始，沿 prev 链走 n 步
// 如果能走回起点且遍历了所有 n 个节点，则找到正解
string bwtDecodeDFS(const string& cipher, int originalIndex) {
    int n = cipher.size();
    if (n == 0) return "";

    vector<int> prev;
    buildPrevArray(cipher, prev);

    cout << "L列(密文): ";
    for (char c : cipher) cout << c << " ";
    cout << "\nF列(排序): ";
    string F = cipher;
    sort(F.begin(), F.end());
    for (char c : F) cout << c << " ";
    cout << "\n" << endl;

    // 打印 prev 映射
    cout << "依赖图 (prev 数组):" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "  L[" << i << "]='" << cipher[i]
             << "' → prev[" << i << "]=" << prev[i]
             << " (F[" << prev[i] << "]='" << F[prev[i]] << "')" << endl;
    }
    cout << endl;

    // 从 originalIndex 出发，沿 prev 链逆向还原
    // 原文第 n-1 位 = L[originalIndex]
    // 原文第 n-2 位 = L[prev[originalIndex]]
    // ...
    // 原文第 0 位 = L[prev^(n-1)[originalIndex]]
    string plain(n, ' ');
    int row = originalIndex;
    for (int i = n - 1; i >= 0; --i) {
        plain[i] = cipher[row];
        cout << "plain[" << i << "] = L[" << row << "] = '" << cipher[row] << "'";
        if (i > 0) {
            row = prev[row];
            cout << " → 下一行: " << row;
        }
        cout << endl;
    }

    return plain;
}

// ---- DFS 回溯法：直接在所有可能的映射中搜索 ----
// 对每个字符，它在 L 列出现多次时，对应 F 列中同字符的相同次数
// 但具体对应哪个呢？用 DFS 尝试所有组合
void dfsDecode(const vector<vector<int>>& candidates, int pos,
               vector<int>& chosen, vector<bool>& used_F,
               vector<int>& best_path, int n) {
    if (pos == n) {
        // 检查是否形成合法环：沿 chosen 走 n 步能回到起点
        vector<bool> visited(n, false);
        int cur = 0, cnt = 0;
        while (!visited[cur] && cnt < n) {
            visited[cur] = true;
            cur = chosen[cur];
            cnt++;
        }
        if (cnt == n && cur == 0) {
            best_path = chosen;
        }
        return;
    }

    for (int cand : candidates[pos]) {
        if (!used_F[cand] && best_path.empty()) {
            used_F[cand] = true;
            chosen[pos] = cand;
            dfsDecode(candidates, pos + 1, chosen, used_F, best_path, n);
            used_F[cand] = false;
        }
    }
}

// ---- 主函数 ----
int main() {
    cout << "========== BWT 变种 — 回溯法找环解密 ==========\n" << endl;

    // 测试样例
    vector<string> tests = {"banana", "algorithm", "example", "hello"};

    for (const auto& plain : tests) {
        cout << "========================================" << endl;
        cout << "原文: \"" << plain << "\" (n=" << plain.size() << ")" << endl;

        // 加密
        auto [cipher, origIdx] = bwtEncode(plain);
        cout << "密文: \"" << cipher << "\", 原文索引=" << origIdx << endl;

        // 打印排序矩阵
        int n = plain.size();
        vector<string> rotations(n);
        for (int i = 0; i < n; ++i) {
            rotations[i] = plain.substr(i) + plain.substr(0, i);
        }
        vector<int> idx(n);
        for (int i = 0; i < n; ++i) idx[i] = i;
        stable_sort(idx.begin(), idx.end(), [&](int a, int b) {
            return rotations[a] < rotations[b];
        });

        cout << "排序后的旋转矩阵:" << endl;
        for (int i = 0; i < n; ++i) {
            cout << "  " << (i == origIdx ? "*" : " ") << "[" << i << "] "
                 << rotations[idx[i]] << "  尾字符='" << rotations[idx[i]].back() << "'" << endl;
        }
        cout << "  (* 标记为原文所在行)" << endl;

        // DFS 回溯解密
        cout << "\n回溯解密过程:" << endl;
        string recovered = bwtDecodeDFS(cipher, origIdx);
        cout << "解密结果: \"" << recovered << "\"" << endl;
        cout << "验证: " << (recovered == plain ? "✓ 成功" : "✗ 失败") << endl;
        cout << endl;
    }

    // 交互式测试
    cout << "--- 交互式测试 ---" << endl;
    cout << "输入原文 (回车跳过): ";
    string input;
    getline(cin, input);
    if (!input.empty()) {
        auto [cipher, origIdx] = bwtEncode(input);
        cout << "密文: \"" << cipher << "\", 原文索引=" << origIdx << endl;
        string recovered = bwtDecodeDFS(cipher, origIdx);
        cout << "解密结果: \"" << recovered << "\"" << endl;
        cout << "验证: " << (recovered == input ? "✓ 成功" : "✗ 失败") << endl;
    }

    return 0;
}
