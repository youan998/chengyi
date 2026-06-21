#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;  
// 泛型函数，用于遍历输出容器元素
template <typename Container>
void printContainer(const Container& c) {
    for (auto i = c.begin(); i != c.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;
}

void testVector() {
    cout << "========== 1. Vector 实验 ==========" << endl;
    vector<int> v;
    
    // 生成10个随机数插入到 vector 中
    for (int i = 0; i < 10; ++i) {
        v.push_back(rand() % 100);
    }
    cout << "初始 vector 元素: "; 
    printContainer(v);

    // 在 vector 头部插入一个随机数
    int headNum = rand() % 100;
    v.insert(v.begin(), headNum);
    cout << "头部插入 " << headNum << " 后: "; 
    printContainer(v);

    // 使用 find 查找某个随机数
    int targetNum = rand() % 100;
    auto itFind = find(v.begin(), v.end(), targetNum);
    if (itFind != v.end()) {
        cout << "查找 " << targetNum << " 成功，元素存在！" << endl;
    } else {
        v.push_back(targetNum);
        cout << "查找 " << targetNum << " 失败，已插入到尾部: ";
        printContainer(v);
    }

    // 使用泛型算法 sort 排序
    sort(v.begin(), v.end());
    cout << "sort 排序后: "; 
    printContainer(v);

    // 删除尾部元素
    v.pop_back();
    cout << "删除尾部元素后: "; 
    printContainer(v);

    // 清空 vector
    v.clear();
    cout << "清空后 vector 大小: " << v.size() << endl;
}

void testList() {
    cout << "\n========== 2. List 实验 ==========" << endl;
    list<int> l;
    
    // 生成10个随机数插入到 list 中
    for (int i = 0; i < 10; ++i) {
        l.push_back(rand() % 100);
    }
    cout << "初始 list 元素: "; 
    printContainer(l);

    // 在 list 头部插入一个随机数
    int headNum = rand() % 100;
    l.push_front(headNum); // list 特有方法，或者用 l.insert(l.begin(), headNum)
    cout << "头部插入 " << headNum << " 后: "; 
    printContainer(l);

    // 使用 find 查找某个随机数
    int targetNum = rand() % 100;
    auto itFind = find(l.begin(), l.end(), targetNum);
    if (itFind != l.end()) {
        cout << "查找 " << targetNum << " 成功，元素存在！" << endl;
    } else {
        l.push_back(targetNum);
        cout << "查找 " << targetNum << " 失败，已插入到尾部: ";
        printContainer(l);
    }

    // list 的排序（注意：list不支持泛型sort，需使用成员函数）
    l.sort(); 
    cout << "list.sort() 排序后: "; 
    printContainer(l);

    // 删除尾部元素
    l.pop_back();
    cout << "删除尾部元素后: "; 
    printContainer(l);

    // 清空 list
    l.clear();
    cout << "清空后 list 大小: " << l.size() << endl;
}  
void testGenericAlgorithms() {
    cout << "\n========== 3. 泛型算法综合实验 ==========" << endl;
    vector<int> v;
    
    // 插入10个随机数
    for (int i = 0; i < 10; ++i) {
        v.push_back(rand() % 100);
    }
    cout << "初始序列: ";
    printContainer(v);

    // 升序排序
    sort(v.begin(), v.end());
    cout << "按升序排序后: ";
    printContainer(v);

    // 降序排序 (使用 greater<int> 或逆向迭代器)
    sort(v.begin(), v.end(), greater<int>());
    cout << "按降序排序后: ";
    printContainer(v);

    // 练习用 find 查找元素 (查找现有元素确保能找到)
    // 二分查找需要先排序，这里已经排序了，直接使用 find 查找一个存在的元素 
    if (!v.empty()) {
        int existTarget = v[v.size() / 2];
        auto it = find(v.begin(), v.end(), existTarget);
        if (it != v.end()) {
            cout << "find 成功找到元素: " << *it << endl;
        }
    }

    // 用 min_element 和 max_element 找最大最小元素
    auto minIt = min_element(v.begin(), v.end());
    auto maxIt = max_element(v.begin(), v.end());
    
    if (minIt != v.end() && maxIt != v.end()) {
        cout << "容器中的最小元素为: " << *minIt << endl;
        cout << "容器中的最大元素为: " << *maxIt << endl;
    }
}
int main() {
    srand(static_cast<unsigned int>(time(0))); // 设置随机数种子   
    testVector();   
    testList(); 
    testGenericAlgorithms();
    return 0;
}
    