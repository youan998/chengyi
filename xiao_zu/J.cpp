#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

typedef long long ll;
const ll INF = LLONG_MAX / 2;

// 存储每条工序信息
struct Edge {
    int u, v;
    int w, c;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, K;
    cin >> n >> m >> K;
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w >> edges[i].c;
    }

    // dp[i][j]：到达节点i，使用j次优化的最短耗时
    vector<vector<ll>> dp(n + 1, vector<ll>(K + 1, INF));
    dp[1][0] = 0;
    for (int u = 1; u <= n; u++) {
        for (Edge e : edges) {
            if (e.u != u) continue;
            int v = e.v;
            int w = e.w, c = e.c;
            // 枚举所有优化次数
            for (int j = 0; j <= K; j++) {
                // 情况1：不优化这条边
                if (dp[u][j] != INF) {
                    dp[v][j] = min(dp[v][j], dp[u][j] + w);
                }
                // 情况2：优化这条边，消耗1次优化名额
                if (j >= 1 && dp[u][j - 1] != INF) {
                    dp[v][j] = min(dp[v][j], dp[u][j - 1] + c);
                }
            }
        }
    }

    // 取0~K次优化里终点的最小耗时
    ll ans = INF;
    for (int j = 0; j <= K; j++) {
        ans = min(ans, dp[n][j]);
    }
    cout << ans << endl;
    return 0;
}