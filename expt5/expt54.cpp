#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

// ==========================================
//  Problem A: Morse Mismatches (莫斯码匹配)
//  1. 将字典中每个单词翻译为莫斯码
//  2. 对输入密文进行精确匹配 → 输出 word!
//  3. 无精确匹配时 → 前缀匹配，选长度差异最小的 → 输出 word?
// ==========================================

// 标准 Morse 码表 (A-Z, 0-9)
const string morseTable[36] = {
    ".-",    // A
    "-...",  // B
    "-.-.",  // C
    "-..",   // D
    ".",     // E
    "..-.",  // F
    "--.",   // G
    "....",  // H
    "..",    // I
    ".---",  // J
    "-.-",   // K
    ".-..",  // L
    "--",    // M
    "-.",    // N
    "---",   // O
    ".--.",  // P
    "--.-",  // Q
    ".-.",   // R
    "...",   // S
    "-",     // T
    "..-",   // U
    "...-",  // V
    ".--",   // W
    "-..-",  // X
    "-.--",  // Y
    "--..",  // Z
    "-----", // 0
    ".----", // 1
    "..---", // 2
    "...--", // 3
    "....-", // 4
    ".....", // 5
    "-....", // 6
    "--...", // 7
    "---..", // 8
    "----."  // 9
};

// 将单个字符转为 Morse 码
string charToMorse(char c) {
    if (c >= 'A' && c <= 'Z') return morseTable[c - 'A'];
    if (c >= 'a' && c <= 'z') return morseTable[c - 'a'];
    if (c >= '0' && c <= '9') return morseTable[26 + c - '0'];
    return "";
}

// 将单词转为 Morse 码字符串（字母间无分隔符）
string wordToMorse(const string& word) {
    string morse;
    for (char c : word) {
        morse += charToMorse(c);
    }
    return morse;
}

// 判断 a 是否是 b 的前缀
bool isPrefix(const string& shorter, const string& longer) {
    if (shorter.size() > longer.size()) return false;
    return longer.compare(0, shorter.size(), shorter) == 0;
}

int main() {
    cout << "========== Problem A: Morse Mismatches (莫斯码匹配) ==========\n" << endl;

    // 字典：单词列表
    vector<string> dictionary = {
        "AN", "EARTHQUAKE", "EAT", "GOD",
        "HATH", "IM", "READY", "TO", "WHAT", "WROTH"
    };

    // 预计算每个字典单词的 Morse 码
    vector<string> dictMorse;
    cout << "字典单词 → Morse 码:" << endl;
    for (const auto& word : dictionary) {
        string m = wordToMorse(word);
        dictMorse.push_back(m);
        cout << "  " << word << " → " << m << endl;
    }
    cout << endl;

    // 待匹配的 Morse 码序列
    vector<string> targets = {
        ".--.....--",   // 示例密文1
        ".....--....",  // 示例密文2
        ".--...--",     // 示例密文3
        "...--..."      // 示例密文4
    };

    for (const auto& target : targets) {
        cout << "密文: \"" << target << "\" → ";

        string bestMatch = "";
        string bestWord = "";
        bool exactFound = false;
        int minDiff = 99999;

        for (size_t i = 0; i < dictionary.size(); ++i) {
            const string& dm = dictMorse[i];

            // 精确匹配
            if (dm == target) {
                cout << dictionary[i] << "!" << endl;
                exactFound = true;
                break;
            }

            // 前缀匹配 (互为前缀)
            int minLen = min(dm.size(), target.size());
            if (dm.substr(0, minLen) == target.substr(0, minLen)) {
                int diff = abs((int)dm.size() - (int)target.size());
                if (diff < minDiff) {
                    minDiff = diff;
                    bestWord = dictionary[i];
                    bestMatch = dm;
                }
            }
        }

        if (!exactFound) {
            if (!bestWord.empty()) {
                cout << bestWord << "?  (前缀匹配, 长度差=" << minDiff << ")" << endl;
            } else {
                cout << "无匹配!" << endl;
            }
        }
    }

    // 交互式测试
    cout << "\n--- 交互式匹配 ---" << endl;
    cout << "字典单词: ";
    for (const auto& w : dictionary) cout << w << " ";
    cout << "\n输入 Morse 码 (或按回车跳过): ";

    string input;
    getline(cin, input);
    if (!input.empty()) {
        // 同上匹配逻辑
        bool exactFound = false;
        int minDiff = 99999;
        string bestWord = "";

        for (size_t i = 0; i < dictionary.size(); ++i) {
            const string& dm = dictMorse[i];
            if (dm == input) {
                cout << "精确匹配: " << dictionary[i] << "!" << endl;
                exactFound = true;
                break;
            }
            int minLen = min(dm.size(), input.size());
            if (dm.substr(0, minLen) == input.substr(0, minLen)) {
                int diff = abs((int)dm.size() - (int)input.size());
                if (diff < minDiff) { minDiff = diff; bestWord = dictionary[i]; }
            }
        }
        if (!exactFound) {
            if (!bestWord.empty())
                cout << "近似匹配: " << bestWord << "? (长度差=" << minDiff << ")" << endl;
            else
                cout << "无匹配!" << endl;
        }
    }

    return 0;
}
