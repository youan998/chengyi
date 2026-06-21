#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
#include <sstream>
#include <chrono>

using namespace std;

// 缓存节点定义
struct CacheNode {
    int key;
    int value;
    bool is_dirty;
};

int C; // 缓存容量
list<CacheNode> cache_list; // 双向链表：头部为 MRU，尾部为 LRU
unordered_map<int, list<CacheNode>::iterator> cache_map; // 哈希表：极速定位链表中的节点
unordered_map<int, int> main_memory; // 模拟主存：只存被修改过的脏数据

// 从主存获取数据
int get_memory(int key) {
    if (main_memory.count(key)) {
        return main_memory[key];
    }
    return key; // 默认 value 等于 key 本身
}

// 写回主存
void set_memory(int key, int value) {
    main_memory[key] = value;
}

// 淘汰策略 (LRU)
void ensure_capacity() {
    if (C == 0) return;
    if (cache_list.size() < C) return; // 容量充足，无需淘汰
    
    // 获取尾部最久未使用节点 (LRU)
    auto lru_node = cache_list.back();
    if (lru_node.is_dirty) {
        set_memory(lru_node.key, lru_node.value); // 脏数据写回主存
    }
    
    // 从缓存中彻底移除
    cache_map.erase(lru_node.key);
    cache_list.pop_back();
}

// 处理 READ 操作
void process_read(int key) {
    if (C == 0) {
        cout << "READ " << key << ":Miss, loaded, value=" << get_memory(key) << "\n";
        return;
    }
    
    if (cache_map.count(key)) {
        // Hit
        auto it = cache_map[key];
        int v = it->value;
        bool dirty = it->is_dirty;
        
        // 移到 MRU 端
        cache_list.erase(it);
        cache_list.push_front({key, v, dirty});
        cache_map[key] = cache_list.begin();
        
        cout << "READ " << key << ":Hit, value=" << v << "\n";
    } else {
        // Miss
        int v = get_memory(key);
        ensure_capacity(); // 满则淘汰
        
        cache_list.push_front({key, v, false}); // 以干净状态加载到 MRU
        cache_map[key] = cache_list.begin();
        
        cout << "READ " << key << ":Miss, loaded, value=" << v << "\n";
    }
}

// 处理 WRITE 操作
void process_write(int key, int value) {
    if (C == 0) {
        cout << "WRITE " << key << " " << value << ":Miss, loaded and updated\n";
        set_memory(key, value); // 容量为0时，相当于穿透直接写回主存
        return;
    }
    
    if (cache_map.count(key)) {
        // Hit
        auto it = cache_map[key];
        cache_list.erase(it);
        
        // 更新 value 并置脏，移至 MRU
        cache_list.push_front({key, value, true});
        cache_map[key] = cache_list.begin();
        
        cout << "WRITE " << key << " " << value << ":Hit, updated\n";
    } else {
        // Miss
        int v = get_memory(key); // 先走一遍加载流
        ensure_capacity();
        
        // 更新 value 并直接置脏，存入 MRU
        cache_list.push_front({key, value, true});
        cache_map[key] = cache_list.begin();
        
        cout << "WRITE " << key << " " << value << ":Miss, loaded and updated\n";
    }
}

int main() {
    // 优化 I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> C)) return 0;
    
    // 读取 C 后面的所有操作串，利用 getline 进行分号切割
    string segment;
    while (getline(cin, segment, ';')) {
        stringstream ss(segment);
        string cmd;
        if (ss >> cmd) {
            if (cmd == "READ") {
                int k; 
                ss >> k;
                process_read(k);
            } else if (cmd == "WRITE") {
                int k, v; 
                ss >> k >> v;
                process_write(k, v);
            }
        }
    }
    
    // 输出最终状态
    cout << "\n";
    if (cache_list.empty()) {
        cout << "Cache is empty.\n";
    } else {
        cout << "Cachestate(MRU->LRU):\n";
        for (const auto& node : cache_list) {
            cout << node.key << ":" << node.value << "\n";
        }
    }

    return 0;
}