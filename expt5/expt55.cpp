#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ==========================================
//  Problem B: Do the Untwist (解密扭曲散列)
//  加密公式: C[i] = (P[(k * i) % n] - i) mod 28
//  解密公式: P[(k * i) % n] = (C[i] + i) mod 28
//  字符映射: _ = 0, a = 1, b = 2, ..., z = 26, . = 27
// ==========================================

// 字符 → 数字 (0-27)
int charToCode(char c) {
    if (c == '_') return 0;
    if (c == '.') return 27;
    if (c >= 'a' && c <= 'z') return c - 'a' + 1;
    return 0;
}

// 数字 (0-27) → 字符
char codeToChar(int code) {
    code = (code % 28 + 28) % 28;  // 规范化到 0-27
    if (code == 0) return '_';
    if (code == 27) return '.';
    return 'a' + code - 1;
}

// 加密：plaintext → ciphertext
string twist(int k, const string& plaintext) {
    int n = plaintext.size();
    vector<int> plaincode(n);
    for (int i = 0; i < n; ++i) {
        plaincode[i] = charToCode(plaintext[i]);
    }

    vector<int> ciphercode(n);
    for (int i = 0; i < n; ++i) {
        // C[i] = (P[(k*i) % n] - i) mod 28
        ciphercode[i] = ((plaincode[(k * i) % n] - i) % 28 + 28) % 28;
    }

    string ciphertext;
    for (int c : ciphercode) {
        ciphertext += codeToChar(c);
    }
    return ciphertext;
}

// 解密：ciphertext → plaintext
string untwist(int k, const string& ciphertext) {
    int n = ciphertext.size();
    vector<int> ciphercode(n);
    for (int i = 0; i < n; ++i) {
        ciphercode[i] = charToCode(ciphertext[i]);
    }

    vector<int> plaincode(n);
    for (int i = 0; i < n; ++i) {
        // P[(k*i) % n] = (C[i] + i) mod 28
        int plain_idx = (k * i) % n;
        plaincode[plain_idx] = ((ciphercode[i] + i) % 28 + 28) % 28;
    }

    string plaintext;
    for (int c : plaincode) {
        plaintext += codeToChar(c);
    }
    return plaintext;
}

int main() {
    cout << "========== Problem B: Do the Untwist (解密扭曲散列) ==========\n" << endl;

    // 测试样例
    struct TestCase {
        int k;
        string plaintext;
    };

    // 注意: k 必须与 n 互质 (gcd(k,n)=1)，否则映射不是双射
    vector<TestCase> tests = {
        {5, "hello_world."},   // n=12, gcd(5,12)=1 ✓
        {2, "cat"},            // n=3,  gcd(2,3)=1  ✓
        {7, "code_is_fun"},    // n=10, gcd(7,10)=1 ✓
        {5, "algorithm"},      // n=9,  gcd(5,9)=1  ✓
    };

    for (const auto& test : tests) {
        cout << "k = " << test.k << ", 原文 = \"" << test.plaintext << "\"" << endl;

        // 加密
        string cipher = twist(test.k, test.plaintext);
        cout << "  加密: \"" << cipher << "\"" << endl;

        // 解密
        string recovered = untwist(test.k, cipher);
        cout << "  解密: \"" << recovered << "\"" << endl;

        // 验证
        bool ok = (recovered == test.plaintext);
        cout << "  验证: " << (ok ? "✓ 成功" : "✗ 失败") << endl;
        cout << endl;
    }

    // 独立的加解密演示
    cout << "--- 独立加解密演示 (k=5, n=28) ---" << endl;
    string plain = "hello_world.";
    int k = 5, n = plain.size();

    cout << "原文: " << plain << " (n=" << n << ")" << endl;

    // 显示编码 → 加密 → 解密过程
    cout << "\n字符编码映射:" << endl;
    cout << "  _=0, a=1, b=2, ..., z=26, .=27" << endl;

    // 加密演示
    vector<int> pc(n);
    for (int i = 0; i < n; ++i) pc[i] = charToCode(plain[i]);

    cout << "\n加密过程 (C[i] = (P[k*i mod n] - i) mod 28):" << endl;
    vector<int> cc(n);
    for (int i = 0; i < n; ++i) {
        int idx = (k * i) % n;
        cc[i] = ((pc[idx] - i) % 28 + 28) % 28;
        cout << "  C[" << i << "] = (P[" << idx << "] - " << i
             << ") mod 28 = (" << pc[idx] << " - " << i
             << ") mod 28 = " << cc[i] << " → '" << codeToChar(cc[i]) << "'" << endl;
    }

    // 解密演示
    cout << "\n解密过程 (P[k*i mod n] = (C[i] + i) mod 28):" << endl;
    vector<int> dc(n);
    for (int i = 0; i < n; ++i) {
        int idx = (k * i) % n;
        dc[idx] = ((cc[i] + i) % 28 + 28) % 28;
        cout << "  P[" << idx << "] = (C[" << i << "] + " << i
             << ") mod 28 = (" << cc[i] << " + " << i
             << ") mod 28 = " << dc[idx] << " → '" << codeToChar(dc[idx]) << "'" << endl;
    }

    string recovered = untwist(k, plain);
    if (!recovered.empty()) recovered = untwist(k, twist(k, plain));
    cout << "\n解密结果: \"" << recovered << "\"" << endl;
    cout << "验证: " << (recovered == plain ? "✓" : "✗") << endl;

    return 0;
}
