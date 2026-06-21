#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<long long> a;

// 核心验证函数：判断给定的风险阈值 limit 是否可行
bool check(long long limit) {
    int count = 1; // 至少需要 1 个周期
    long long cur_min = a[0];
    long long cur_max = a[0];
    long long len = 1;

    for (int i = 1; i < n; ++i) {
        // 模拟将当前元素 a[i] 加入当前周期的状态
        long long next_min = min(cur_min, a[i]);
        long long next_max = max(cur_max, a[i]);
        long long next_len = len + 1;

        // 如果加入后的风险值超过了限制，必须另起一个新周期
        if (next_len * (next_max - next_min) > limit) {
            count++;
            // 新周期以当前元素 a[i] 为起点重新计算
            cur_min = a[i];
            cur_max = a[i];
            len = 1;
        } else {
            // 否则，贪心地将 a[i] 纳入当前周期
            cur_min = next_min;
            cur_max = next_max;
            len = next_len;
        }
    }
    // 如果切分的周期数 <= m，说明该限制可行
    return count <= m;
}

int main() {
    // 优化终端 I/O 速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (cin >> n >> m) {
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        // 设定二分的上下界
        long long low = 0;
        // 最坏情况：n = 10^5, 数据差值为 10^9，风险极值为 10^14
        long long high = 1e14; 
        long long ans = high;

        // 二分答案模板
        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (check(mid)) {
                ans = mid;       // 当前 mid 可行，记录答案
                high = mid - 1;  // 尝试挑战更小的极限风险值
            } else {
                low = mid + 1;   // 当前 mid 不可行，说明条件太苛刻，需放宽风险值
            }
        }

        cout << ans << "\n";
    }

    return 0;
}