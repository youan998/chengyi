#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// 设定浮点数精度误差范围
const double EPS = 1e-8;

struct Point {
    double x, y;
};

// 符号判断函数，处理浮点数精度问题
int dcmp(double x) {
    if (abs(x) < EPS) return 0;
    return x < 0 ? -1 : 1;
}

// 计算向量 p0->p1 和 p0->p2 的叉积
double cross(Point p0, Point p1, Point p2) {
    return (p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x);
}

// 判断点 p 是否在线段 ab 上 (已知 p, a, b 共线的前提下)
bool onSegment(Point p, Point a, Point b) {
    return dcmp(min(a.x, b.x) - p.x) <= 0 && dcmp(p.x - max(a.x, b.x)) <= 0 &&
           dcmp(min(a.y, b.y) - p.y) <= 0 && dcmp(p.y - max(a.y, b.y)) <= 0;
}

// 跨立实验：判断线段 a-b 与 c-d 是否相交
bool isIntersect(Point a, Point b, Point c, Point d) {
    // 快速排斥实验 (外接矩形相交判定)
    if (max(a.x, b.x) < min(c.x, d.x) || max(c.x, d.x) < min(a.x, b.x) ||
        max(a.y, b.y) < min(c.y, d.y) || max(c.y, d.y) < min(a.y, b.y)) {
        return false;
    }

    // 跨立实验
    double d1 = cross(c, d, a);
    double d2 = cross(c, d, b);
    double d3 = cross(a, b, c);
    double d4 = cross(a, b, d);

    // 规范相交 (相互跨立)
    if (dcmp(d1) * dcmp(d2) < 0 && dcmp(d3) * dcmp(d4) < 0) return true;

    // 非规范相交 (端点在另一条线段上)
    if (dcmp(d1) == 0 && onSegment(a, c, d)) return true;
    if (dcmp(d2) == 0 && onSegment(b, c, d)) return true;
    if (dcmp(d3) == 0 && onSegment(c, a, b)) return true;
    if (dcmp(d4) == 0 && onSegment(d, a, b)) return true;

    return false;
}

// 判断多边形是否合法 (是否存在非相邻边相交)
bool isValidPolygon(const vector<Point>& pts) {
    int n = pts.size();
    if (n < 3) return false;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 2; j < n; ++j) {
            // 首尾两条边是相邻边，跳过检测
            if (i == 0 && j == n - 1) continue;

            Point a1 = pts[i], b1 = pts[(i + 1) % n];
            Point a2 = pts[j], b2 = pts[(j + 1) % n];

            if (isIntersect(a1, b1, a2, b2)) {
                return false;
            }
        }
    }
    return true;
}

// 鞋带公式计算多边形面积
double calcArea(const vector<Point>& pts) {
    double area = 0.0;
    int n = pts.size();
    for (int i = 0; i < n; ++i) {
        int next = (i + 1) % n;
        area += pts[i].x * pts[next].y - pts[next].x * pts[i].y;
    }
    return abs(area) / 2.0;
}

void solveAreaProblem() {
    cout << "==========  AREA 习题测试 ==========" << endl;
    int n;
    int caseNum = 1;
    bool firstCase = true;

    while (cin >> n && n != 0) {
        vector<Point> pts(n);
        for (int i = 0; i < n; ++i) {
            cin >> pts[i].x >> pts[i].y;
        }

        // 按题目要求，测试用例之间打印空行
        if (!firstCase) cout << endl;
        firstCase = false;

        cout << "Figure " << caseNum++ << ": ";

        if (isValidPolygon(pts)) {
            // 设置输出保留两位小数
            cout << fixed << setprecision(2) << calcArea(pts) << endl;
        } else {
            cout << "Impossible" << endl;
        }
    }
}
int main() {
    solveAreaProblem();
    return 0;
}