#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;
int dp[31][31][31][31];
struct Line
{
    int l,c,n,m, cost;
} line[105];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int Lmin, Cmin, Nmin, Mmin;
    cin >> Lmin >> Cmin >> Nmin >> Mmin;
    int num;
    cin >> num;

    for (int i = 1; i <= num; i++)
    {
        cin >> line[i].l >> line[i].c >> line[i].n >> line[i].m >> line[i].cost;
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][0][0] = 0;
    for (int i = 1; i <= num; i++)
    {
        int dl = line[i].l;
        int dc = line[i].c;
        int dn = line[i].n;
        int dm = line[i].m;
        int co = line[i].cost;
        for (int l = 30; l >= 0; l--)
            for (int c = 30; c >= 0; c--)
                for (int n = 30; n >= 0; n--)
                    for (int mm = 30; mm >= 0; mm--)
                    {
                        if (dp[l][c][n][mm] == INF)
                            continue;
                        int nl = min(l + dl, 30);
                        int nc = min(c + dc, 30);
                        int nn = min(n + dn, 30);
                        int nm = min(mm + dm, 30);
                        if (dp[nl][nc][nn][nm] > dp[l][c][n][mm] + co)
                        {
                            dp[nl][nc][nn][nm] = dp[l][c][n][mm] + co;
                        }
                    }
    }
    int ans = INF;
    for (int l = Lmin; l <= 30; l++)
        for (int c = Cmin; c <= 30; c++)
            for (int n = Nmin; n <= 30; n++)
                for (int mm = Mmin; mm <= 30; mm++)
                {
                    ans = min(ans, dp[l][c][n][mm]);
                }
    if (ans == INF)
        cout << "Impossible" << endl;
    else
        cout << ans << endl;
    return 0;
}