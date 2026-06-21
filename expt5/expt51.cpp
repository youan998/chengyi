#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// ==========================================
//  Kitty Fishing (小猫钓鱼)
//  玩家手牌: 队列 (FIFO) — 先进先出
//  桌面牌:   栈 (LIFO) — 后进先出
//  哈希桶:   快速判断桌面是否有重复牌
// ==========================================
void solveKittyFishing() {
    queue<int> q1, q2;
    vector<int> table;          // 桌面上的牌（栈）
    int book[10] = {0};         // 桶：记录桌面上每种牌是否存在

    // 初始手牌
    int cards1[] = {2, 4, 1, 2, 5, 6};
    int cards2[] = {3, 1, 3, 5, 6, 4};
    for (int i = 0; i < 6; ++i) {
        q1.push(cards1[i]);
        q2.push(cards2[i]);
    }

    cout << "玩家1初始手牌: ";
    for (int c : cards1) cout << c << " ";
    cout << "\n玩家2初始手牌: ";
    for (int c : cards2) cout << c << " ";
    cout << "\n" << endl;

    int turn = 0;  // 0 = 玩家1, 1 = 玩家2
    int round = 0;
    while (!q1.empty() && !q2.empty()) {
        round++;
        int card = (turn == 0) ? q1.front() : q2.front();
        if (turn == 0) q1.pop();
        else q2.pop();

        cout << "第" << round << "轮: 玩家" << (turn + 1)
             << " 打出 [" << card << "] — ";

        if (book[card] == 0) {
            // 桌面没有这张牌 → 放到桌面
            table.push_back(card);
            book[card] = 1;
            cout << "无重复，放到桌面" << endl;
        } else {
            // 桌面有这张牌 → 收牌!
            queue<int>& winner_q = (turn == 0) ? q1 : q2;

            // 先把打出的牌收走
            winner_q.push(card);

            // 从桌面顶部依次取牌，直到遇到相同的牌
            int collected = 1;
            while (!table.empty() && table.back() != card) {
                int top = table.back();
                winner_q.push(top);
                book[top] = 0;
                table.pop_back();
                collected++;
            }
            // 最后一张相同的牌也收走
            if (!table.empty()) {
                winner_q.push(table.back());
                book[table.back()] = 0;
                table.pop_back();
                collected++;
            }
            cout << "有重复！收走 " << collected << " 张牌" << endl;
        }

        // 显示当前状态
        cout << "  桌面: [";
        for (size_t i = 0; i < table.size(); ++i) {
            cout << table[i] << (i + 1 < table.size() ? " " : "");
        }
        cout << "]  玩家1: " << q1.size() << "张  玩家2: " << q2.size() << "张" << endl;

        turn = 1 - turn;
    }

    cout << "\n========== 结果 ==========" << endl;
    if (q2.empty()) {
        cout << "玩家1 获胜！剩余手牌: ";
        while (!q1.empty()) { cout << q1.front() << " "; q1.pop(); }
        cout << endl;
    } else {
        cout << "玩家2 获胜！剩余手牌: ";
        while (!q2.empty()) { cout << q2.front() << " "; q2.pop(); }
        cout << endl;
    }
}

int main() {
    cout << "========== a. Kitty Fishing (小猫钓鱼) ==========\n" << endl;
    solveKittyFishing();
    return 0;
}
