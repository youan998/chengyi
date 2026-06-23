#include <iostream>

#include <cstring>

#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 105;

const ll INF = 1e18;

struct Matrix {

    ll a[MAXN][MAXN];

    Matrix() {

        for (int i = 0; i < MAXN; i++)

            for (int j = 0; j < MAXN; j++)

                a[i][j] = INF;

    }

};

Matrix mul(const Matrix& A, const Matrix& B, int n) {

    Matrix res;

    for (int i = 1; i <= n; ++i) {

        for (int t = 1; t <= n; ++t) {

            if (A.a[i][t] == INF) continue; // 剪枝：不可达中转直接跳过

            for (int j = 1; j <= n; ++j) {

                if (B.a[t][j] == INF) continue;

                ll now = max(A.a[i][t], B.a[t][j]);

                res.a[i][j] = min(res.a[i][j], now);

            }

        }

    }

    return res;

}



// 矩阵快速幂

Matrix matrix_pow(Matrix G, int k, int n) {

    Matrix ans;

    // 单位矩阵：0步转移，只能留在自身

    for (int i = 1; i <= n; ++i)

        ans.a[i][i] = 0;

    while (k > 0) {

        if (k & 1)

            ans = mul(ans, G, n);

        G = mul(G, G, n);

        k >>= 1;

    }

    return ans;

}



int main() {

    cin.tie(nullptr);

    int N, M;

    cin >> N >> M;

    Matrix G;

    // 建图，自动处理重边，保留最小权值

    for (int i = 0; i < M; ++i) {

        int u, v;

        ll w;

        cin >> u >> v >> w;

        if (w < G.a[u][v]) {

            G.a[u][v] = w;

        }

    }

    int Q;

    cin >> Q;

    while (Q--) {

        int s, K;

        cin >> s >> K;

        Matrix mat = matrix_pow(G, K, N);

        for (int j = 1; j <= N; ++j) {

            if (mat.a[s][j] >= INF)

                cout << -1 << " ";

            else

                cout << mat.a[s][j] << " ";

        }

        cout << "\n";

    }

    return 0;

}