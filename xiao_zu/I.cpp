#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

const int IN_STOCK = 0;
const int OUT_USE = 1;
const int SCRAP = 2;

struct Battery {
    int loop;
    int timeId;
    int status;
    Battery() : loop(0), timeId(0), status(IN_STOCK) {}
    Battery(int t) : loop(0), timeId(t), status(IN_STOCK) {}
};

struct Node {
    string name;
    int loop;
    int timeId;
    Node(string n, int l, int t) : name(n), loop(l), timeId(t) {}
};

struct Cmp {
    bool operator()(const Node& a, const Node& b) {
        if (a.loop != b.loop)
            return a.loop > b.loop;
        return a.timeId > b.timeId;
    }
};

int main()
{
    int Q, K;
    cin >> Q >> K;

    priority_queue<Node, vector<Node>, Cmp> heap;
    unordered_map<string, Battery> batInfo;
    vector<string> res;  

    int stockCnt = 0;
    int timeStamp = 0;

    while (Q--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            string name;
            cin >> name;
            timeStamp++;
            batInfo[name] = Battery(timeStamp);
            heap.emplace(name, 0, timeStamp);
            stockCnt++;
        }
        else if (op == 2)
        {
            while (!heap.empty())
            {
                Node cur = heap.top();
                heap.pop();
                string n = cur.name;
                if (batInfo[n].status == IN_STOCK)
                {
                    batInfo[n].status = OUT_USE;
                    stockCnt--;
                    res.push_back(n); 
                    break;
                }
            }
        }
        else if (op == 3)
        {
            string name;
            cin >> name;
            Battery& b = batInfo[name];
            b.loop += 1;
            if (b.loop >= K)
            {
                b.status = SCRAP;
                res.push_back(name); 
            }
            else
            {
                b.status = IN_STOCK;
                heap.emplace(name, b.loop, b.timeId);
                stockCnt++;
            }
        }
        else if (op == 4)
        {
            res.push_back(to_string(stockCnt)); 
        }
    }
    for (auto& s : res)
    {
        cout << s << endl;
    }

    return 0;
}