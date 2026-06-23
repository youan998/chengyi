#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>
using namespace std;
typedef long long ll;
const int MAXN = 3e5 + 10;
vector<pair<int, int>> adj[MAXN];
ll d[MAXN];  
int dis[MAXN]; 
int belong[MAXN]; 
struct Node
{
    int id, dist;
    Node(int i, int d) : id(i), dist(d) {}
    bool operator>(const Node& other) const
    {
        return dist > other.dist;
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> d[i];
    for (int i = 1; i < n; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    int q;
    cin >> q;
    while (q--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int u, val;
            cin >> u >> val;
            d[u] = val;
        }
        else if (op == 2)
        {
            int u, v, w;
            cin >> u >> v >> w;
            for (auto& p : adj[u])
                if (p.first == v) p.second = w;
            for (auto& p : adj[v])
                if (p.first == u) p.second = w;
        }
        else if (op == 3)
        {
            int k;
            cin >> k;
            vector<int> cen(k);
            priority_queue<Node, vector<Node>, greater<Node>> heap;
            fill(dis, dis + n + 1, INT_MAX);
            fill(belong, belong + n + 1, -1);
            for (int i = 0; i < k; i++)
            {
                cin >> cen[i];
                int s = cen[i];
                dis[s] = 0;
                belong[s] = s;
                heap.emplace(s, 0);
            }
            while (!heap.empty())
            {
                Node cur = heap.top();
                heap.pop();
                int u = cur.id;
                int nowd = cur.dist;
                if (nowd > dis[u]) continue;
                for (auto& p : adj[u])
                {
                    int v = p.first;
                    int w = p.second;
                    if (dis[v] > dis[u] + w)
                    {
                        dis[v] = dis[u] + w;
                        belong[v] = belong[u];
                        heap.emplace(v, dis[v]);
                    }
                    else if (dis[v] == dis[u] + w)
                    {
                        if (belong[u] < belong[v])
                            belong[v] = belong[u];
                    }
                }
            }
            vector<ll> res(k, 0);
            for (int i = 1; i <= n; i++)
            {
                int bid = belong[i];
                for (int j = 0; j < k; j++)
                {
                    if (cen[j] == bid)
                    {
                        res[j] += d[i];
                        break;
                    }
                }
            }
            for (int i = 0; i < k; i++)
                cout << res[i] << " ";
            cout << "\n";
        }
  }
    return 0;
}