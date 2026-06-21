#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>
using namespace std;
// 记忆化哈希表
std::unordered_map<int, int> memo;  
int main() {
    int n,k;
    int max_freq = 0;
    cin >> n >> k;
    vector<int> A(n);
    for(int i=0; i<n; ++i) {
        cin >> A[i];
    }   
    auto start_time = chrono::high_resolution_clock::now(); 
    // 这里是核心算法的实现                     
    for(int i=0; i<n; ++i) {
        int x = A[i];
        if(memo.count(x)) {
            memo[x]++;
        }
        else {
            memo[x] = 1;
        }   
        max_freq = max(max_freq, memo[x]);
    }                   
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    cout <<n- max_freq << endl;
    cout << "-----------------------\n";                            
    cout << "算法执行耗时: " << duration.count() << " 微秒 (us)\n";
    return 0;
}