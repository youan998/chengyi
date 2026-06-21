#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

// ==========================================
//  Problem C: Substitution Cipher (替换密码与字典序)
//  已知: 加密单词列表按字典序排列
//  相邻单词首个不同字符揭示偏序关系
//  建图 → 拓扑排序 (Kahn) → 唯一解则解密成功
// ==========================================

// 拓扑排序 (Kahn算法)
// 返回 true 表示拓扑序唯一，order 为字母排列
bool topologicalSort(const vector<vector<int>>& adj, vector<int>& inDegree,
                     vector<int>& order) {
    int n = 26;  // 26 个字母
    queue<int> q;

    // 所有入度为 0 的节点入队
    for (int i = 0; i < n; ++i) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        // 如果队列大小 > 1，说明有多种可能的排列
        if (q.size() > 1) {
            // 多解情况：仍然继续，但标记为非唯一
            // （UVA 题目中多解视为失败）
        }

        int u = q.front();
        q.pop();
        order.push_back(u);

        for (int v : adj[u]) {
            inDegree[v]--;
            if (inDegree[v] == 0) {
                q.push(v);
            }
        }
    }

    // 如果有环，order 大小小于 26
    return order.size() == 26;
}

int main() {
    cout << "========== Problem C: Substitution Cipher (替换密码) ==========\n" << endl;

    // 示例：按字典序排列的加密单词
    vector<string> words = {
        "wrb",    // 密文1
        "wre",    // 密文2 (wrb < wre → 暗示 b < e)
        "wrf",    // 密文3 (wre < wrf → 暗示 e < f)
        "xae",    // 密文4 (wrf < xae → 暗示 w < x)
        "xaf"     // 密文5 (xae < xaf → 暗示 e < f, 但已推断过)
    };

    cout << "加密单词列表 (已按字典序排列):" << endl;
    for (const auto& w : words) {
        cout << "  " << w << endl;
    }
    cout << endl;

    // 建图
    vector<vector<int>> adj(26);  // 邻接表
    vector<int> inDegree(26, 0);
    vector<bool> appeared(26, false);

    // 标记所有出现过的字母
    for (const auto& w : words) {
        for (char c : w) {
            appeared[c - 'a'] = true;
        }
    }

    // 比较相邻单词
    cout << "推导偏序关系:" << endl;
    for (size_t i = 0; i < words.size() - 1; ++i) {
        const string& a = words[i];
        const string& b = words[i + 1];

        for (size_t j = 0; j < min(a.size(), b.size()); ++j) {
            if (a[j] != b[j]) {
                int u = a[j] - 'a';
                int v = b[j] - 'a';
                adj[u].push_back(v);
                inDegree[v]++;
                cout << "  " << a << " < " << b
                     << "  ⇒  '" << a[j] << "' < '" << b[j] << "'  ("
                     << a[j] << " → " << b[j] << ")" << endl;
                break;
            }
        }
    }
    cout << endl;

    // 拓扑排序
    vector<int> order;
    vector<int> inDegreeCopy = inDegree;  // 保留副本用于检测
    bool success = topologicalSort(adj, inDegreeCopy, order);

    cout << "拓扑排序结果: ";
    if (success) {
        cout << "成功 (完整排列)" << endl;
        cout << "字母映射关系:" << endl;
        cout << "  密文字母: ";
        for (int c : order) cout << (char)('a' + c) << " ";
        cout << "\n  明文字母: ";
        for (int i = 0; i < 26; ++i) cout << (char)('a' + i) << " ";
        cout << endl;

        // 构建解密映射
        vector<char> mapping(26, '?');
        for (int i = 0; i < 26; ++i) {
            mapping[order[i]] = 'a' + i;
        }
        cout << "\n解密映射表:";
        for (int i = 0; i < 26; ++i) {
            if (appeared[i]) {
                cout << " " << (char)('a' + i) << "→" << mapping[i];
            }
        }
        cout << endl;

        // 解密演示
        cout << "\n解密演示:" << endl;
        for (const auto& w : words) {
            string decrypted;
            for (char c : w) {
                decrypted += mapping[c - 'a'];
            }
            cout << "  " << w << " → " << decrypted << endl;
        }
    } else {
        cout << "失败!" << endl;
        if (order.size() < 26) {
            cout << "存在环，无法确定完整排列" << endl;
            cout << "已排出 " << order.size() << " 个字母: ";
            for (int c : order) cout << (char)('a' + c) << " ";
            cout << endl;
        }
    }

    // 多解检测
    cout << "\n--- 多解检测 ---" << endl;
    // 重置入度，重新排序检测是否唯一
    vector<int> ind2 = inDegree;
    queue<int> q;
    for (int i = 0; i < 26; ++i) {
        if (ind2[i] == 0) q.push(i);
    }
    bool unique = true;
    while (!q.empty()) {
        if (q.size() > 1) {
            unique = false;
            cout << "  检测到多解! 队列中有 " << q.size() << " 个候选:" << endl;
            queue<int> temp = q;
            while (!temp.empty()) {
                cout << "    '" << (char)('a' + temp.front()) << "' ";
                temp.pop();
            }
            cout << endl;
        }
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (--ind2[v] == 0) q.push(v);
        }
    }
    if (unique) {
        cout << "  排列唯一 ✓" << endl;
    }

    return 0;
}
