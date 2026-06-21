#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <iomanip>
#include <algorithm>

using namespace std;

// ==========================================
//  凸包问题 (Graham/Andrew 算法相关定义)
// ==========================================
struct Point {
    double x, y;
    // 排序规则：先按 x 坐标排，x 相同按 y 排
    bool operator<(const Point& p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};

// 计算叉积 OA x OB
double cross(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// 求凸包
vector<Point> convex_hull(vector<Point>& P) {
    int n = P.size(), k = 0;
    if (n <= 3) return P;
    vector<Point> H(2 * n);
    sort(P.begin(), P.end());

    // 构建下半凸包
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    // 构建上半凸包
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t && cross(H[k - 2], H[k - 1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    H.resize(k - 1);
    return H;
}

void testConvexHull() {
    cout << "========== 凸包求解 ==========" << endl;
    vector<Point> pts = {{0, 0}, {2, 2}, {1, 1}, {2, 0}, {0, 2}, {0.5, 0.5}};
    vector<Point> hull = convex_hull(pts);
    cout << "凸包顶点为：" << endl;
    for (auto p : hull) {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
    }
}


// ==========================================
//  房间最短路问题相关定义
// ==========================================
struct Node {
    double x, y;
};

// 墙体结构：记录x坐标，以及两个门(缺口)的y区间 [y1, y2] 和 [y3, y4]
struct Wall {
    double x, y1, y2, y3, y4; 
};

// 计算两点距离
double dist(Node a, Node b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// 判断点A和点B之间是否可以直接“看见”（连线不穿过实心墙）
bool isVisible(Node a, Node b, const vector<Wall>& walls) {
    if (a.x > b.x) swap(a, b); 
    if (a.x == b.x) return true; 

    for (const auto& w : walls) {
        if (w.x > a.x && w.x < b.x) {
            double inter_y = a.y + (b.y - a.y) * (w.x - a.x) / (b.x - a.x);
            bool inDoor1 = (inter_y >= w.y1 && inter_y <= w.y2);
            bool inDoor2 = (inter_y >= w.y3 && inter_y <= w.y4);
            
            if (!inDoor1 && !inDoor2) {
                return false; 
            }
        }
    }
    return true;
}

void solveRoomPath() {
    cout << "\n==========  房间最短路问题 ==========" << endl;
    
    // 这里直接写死输入作为示例，方便你直接运行看结果
    int n = 1; 
    cout << "墙的数量: " << n << endl;

    vector<Wall> walls(n);
    vector<Node> nodes;
    
    // 起点
    nodes.push_back({0, 5.0}); 
    
    if(n > 0){
        walls[0] = {5.0, 0.0, 2.0, 4.5, 6.0}; // 示例墙
        for(int i=0; i<n; ++i) {
            nodes.push_back({walls[i].x, walls[i].y1});
            nodes.push_back({walls[i].x, walls[i].y2});
            nodes.push_back({walls[i].x, walls[i].y3});
            nodes.push_back({walls[i].x, walls[i].y4});
        }
    }
    
    // 终点
    nodes.push_back({10.0, 5.0});
    
    int V = nodes.size();
    vector<double> min_dist(V, 1e9);
    min_dist[0] = 0;

    // Dijkstra 算法
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    pq.push({0, 0});

    while (!pq.empty()) {
        double d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > min_dist[u]) continue;
        if (u == V - 1) break; 

        for (int v = 0; v < V; ++v) {
            if (u != v && isVisible(nodes[u], nodes[v], walls)) {
                double weight = dist(nodes[u], nodes[v]);
                if (min_dist[u] + weight < min_dist[v]) {
                    min_dist[v] = min_dist[u] + weight;
                    pq.push({min_dist[v], v});
                }
            }
        }
    }

    cout << fixed << setprecision(2);
    cout << "从起点到终点的最短路径长度为: " << min_dist[V - 1] << endl;
}

// ==========================================
// 主函数
// ==========================================
int main() {
    testConvexHull();
    solveRoomPath();
    return 0;
}