#include <iostream>
#include <string>
#include <unordered_map>
#include <chrono>
using namespace std;

// 记忆化哈希表，存储从 1 演化到状态 x 的 {最少步数, 操作字符串}
unordered_map<long long, pair<int, string>> memo;
pair<int, string> dfs(long long x) {
    if (memo.count(x)) {
        return memo[x];
    }   
    if (x==1) return {0, " "};
    if (x==2) return {1, "A"};
    if (x%2==0) {
        auto P = dfs(x/2);
        P.first += 1;   
        P.second += "B";    
        return memo[x] = P; 
    }
    else {
        auto P1 = dfs(x-1);
        P1.first += 1;
        P1.second += "A";   
        auto P2 = dfs(x+1);
        P2.first += 1;
        P2.second += "C";       
        if (P1.first < P2.first) {
            return memo[x] = P1;
        }
        else {
            return memo[x] = P2;
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n;
    if (cin >> n) {
        // 在核心算法开始前，打个时间戳
        auto start_time = chrono::high_resolution_clock::now();

        // 核心执行逻辑
        pair<int, string> ans = dfs(n);
        cout << ans.first << "\n";
        if (ans.first > 0) {
            cout << ans.second << "\n";
        }

        // 在核心算法结束后，再打个时间戳
        auto end_time = chrono::high_resolution_clock::now();

        // 计算时间差 (这里转换为微秒，1秒 = 1,000,000微秒)
        auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
        cout << "-----------------------\n";
        cout << "算法执行耗时: " << duration.count() << " 微秒 (us)\n";
    }
    return 0;
}