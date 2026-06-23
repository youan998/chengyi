#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
int main()
{
    ll a, b, c;
    cin >> a >> b >> c;
    ll sum = a + b + c;
    ll mx = max({ a, b, c });
    ll T = mx;
    while (true)
    {
        ll need = 3 * T - sum;
        if (need >= 0 && need % 2 == 0)
            break;
        T++;
    }
    ll d1 = T - a;
    ll d2 = T - b;
    ll d3 = T - c;
    ll cnt = 0;
    while (d1 > 0 || d2 > 0 || d3 > 0)
    {
        int num = 0;
        if (d1 > 0) num++;
        if (d2 > 0) num++;
        if (d3 > 0) num++;
        if (num >= 2)
        {
            if (d1 > 0) d1--;
            if (d2 > 0) d2--;
            if (d3 > 0) d3--;
            cnt++;
        }
        else
        {
            if (d1 > 0) d1 -= 2;
            else if (d2 > 0) d2 -= 2;
            else d3 -= 2;
            cnt++;
        }
    }
    cout << cnt << endl;
    return 0;
}