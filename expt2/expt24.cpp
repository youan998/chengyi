#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// 定义状态结构体
struct State {
    int a, b;
    string op_desc;// 描述当前操作      
    int parent_id; // 记录父节点下标以便回溯路径
};

void solveWaterJug(int capA, int capB, int L) {
    if (L > max(capA, capB)) {
        cout << "No Solution (目标水量超过了容器最大容量)" << endl;
        return;
    }

    vector<State> history; // 相当于队列的增强版，保留所有节点用于回溯
    int head = 0;// 队列头指针，模拟 BFS    
    // 记录状态是否访问过
    vector<vector<bool>> visited(capA + 1, vector<bool>(capB + 1, false));

    history.push_back({0, 0, "初始状态", -1});
    visited[0][0] = true;

    int target_id = -1;

    while (head < history.size()) {
        State curr = history[head];

        if (curr.a == L || curr.b == L) {
            target_id = head;
            break;
        }

        // 定义6种可能的操作
        int next_states[6][2] = {
            {capA, curr.b}, // 1. 填满A
            {curr.a, capB}, // 2. 填满B
            {0, curr.b},    // 3. 倒空A
            {curr.a, 0},    // 4. 倒空B
            // 5. A倒B：实际倒入量为 min(A当前水, B剩余容量)
            {curr.a - min(curr.a, capB - curr.b), curr.b + min(curr.a, capB - curr.b)},
            // 6. B倒A：实际倒入量为 min(B当前水, A剩余容量)
            {curr.a + min(curr.b, capA - curr.a), curr.b - min(curr.b, capA - curr.a)}
        };

        string ops[6] = {
            "装满容器 1", "装满容器 2", "倒空容器 1", "倒空容器 2",
            "将容器 1 的水倒入容器 2", "将容器 2 的水倒入容器 1"
        };

        for (int i = 0; i < 6; i++) {
            int na = next_states[i][0];
            int nb = next_states[i][1];

            if (!visited[na][nb]) {
                visited[na][nb] = true;
                history.push_back({na, nb, ops[i], head});
            }
        }
        head++;
    }

    if (target_id == -1) {
        cout << "No Solution" << endl;
    } else {
        // 回溯打印路径
        vector<int> path;
        int curr = target_id;
        while (curr != -1) {
            path.push_back(curr);
            curr = history[curr].parent_id;
        }
        
        cout << "找到解决方案，步骤如下：" << endl;
        for (int i = path.size() - 1; i >= 0; i--) {
            int id = path[i];
            cout << "步骤 " << path.size() - 1 - i << ": " 
                 << history[id].op_desc << " => (容器1: " << history[id].a 
                 << " 升, 容器2: " << history[id].b << " 升)" << endl;
        }
    }
}

int main() {
    cout << "==========倒水问题 ==========" << endl;
    int capA = 3, capB = 5, target = 4; // 这里以 3升、5升杯子装4升水为例
    cout << "设定: 容器1容量=" << capA << ", 容器2容量=" << capB << ", 目标水量=" << target << endl;
    solveWaterJug(capA, capB, target);
    
    return 0;
}