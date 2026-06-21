#include <iostream>
#include <vector>

using namespace std;

// ==========================================
//  2. 买票问题 (卡特兰数变体 + 高精度)
//  合法排列数 = C(n+m, m) - C(n+m, m-1)
//  考虑人的差异: Result = (n+m)! * (n-m+1) / (n+1)
//  用高精度 BigInt 处理大数阶乘
// ==========================================

struct BigInt {
    vector<int> digits;  // 低位在前

    BigInt(int v = 0) {
        if (v == 0) digits.push_back(0);
        while (v > 0) {
            digits.push_back(v % 10);
            v /= 10;
        }
    }

    // 乘以单精度整数
    void multiply(int v) {
        int carry = 0;
        for (size_t i = 0; i < digits.size(); ++i) {
            long long cur = 1LL * digits[i] * v + carry;
            digits[i] = cur % 10;
            carry = cur / 10;
        }
        while (carry > 0) {
            digits.push_back(carry % 10);
            carry /= 10;
        }
    }

    // 除以单精度整数
    void divide(int v) {
        int rem = 0;
        for (int i = digits.size() - 1; i >= 0; --i) {
            long long cur = digits[i] + 1LL * rem * 10;
            digits[i] = cur / v;
            rem = cur % v;
        }
        // 去除前导零
        while (digits.size() > 1 && digits.back() == 0)
            digits.pop_back();
    }

    void print() const {
        for (int i = digits.size() - 1; i >= 0; --i)
            cout << digits[i];
    }
};

void solveTicket() {
    cout << "--- 买票问题 (卡特兰数变体) ---" << endl;

    // 默认测试 n=100, m=100
    int n = 100, m = 100;
    cout << "输入 n (持5元人数) 和 m (持10元人数): ";
    if (!(cin >> n >> m)) {
        n = 100; m = 100;
        cout << "(使用默认值 n=100, m=100)" << endl;
    }

    if (m > n) {
        cout << "m > n，无法保证找零，方案数为: 0" << endl;
        return;
    }

    cout << "\nn=" << n << ", m=" << m << endl;
    // 公式: Result = (n+m)! * (n-m+1) / (n+1)
    BigInt ans(1);

    // 计算 (n+m)!
    cout << "计算 (" << n+m << ")! ..." << endl;
    for (int i = 1; i <= n + m; ++i) {
        ans.multiply(i);
    }

    // 乘以 (n - m + 1)
    ans.multiply(n - m + 1);

    // 除以 (n + 1)
    ans.divide(n + 1);

    cout << "合法排队方案总数 = ";
    ans.print();
    cout << endl;

    // 验证：小数据 n=3, m=2
    cout << "\n--- 小数据验证 (n=3, m=2) ---" << endl;
    BigInt test(1);
    for (int i = 1; i <= 5; ++i) test.multiply(i);  // 5! = 120
    test.multiply(3 - 2 + 1);  // *2 = 240
    test.divide(3 + 1);        // /4 = 60
    cout << "Result = 5! * 2 / 4 = ";
    test.print();
    cout << " (预期: 60)" << endl;
}

int main() {
    cout << "========== 2. 组合数学: 买票问题 ==========\n" << endl;
    solveTicket();
    return 0;
}
