// R7-4 单源最短路径（标准版）
// 分数 100
// 作者 EBeason
// 单位 兰州大学
// 题目描述
// 如题，给出一个有向图，请输出从某一点出发到所有点的最短路径长度。

// 输入格式
// 第一行包含三个整数 n,m,s，分别表示点的个数、有向边的个数、出发点的编号。
// 接下来 m 行每行包含三个整数 u,v,w，表示一条 u→v 的，长度为 w 的边。

// 输出格式
// 输出一行 n 个整数，第 i 个表示 s 到第 i 个点的最短路径，若不能到达则输出 2 
// 31
//  −1。

// 样例 #1
// 样例输入
// 4 6 1
// 1 2 2
// 2 3 2
// 2 4 1
// 1 3 5
// 3 4 3
// 1 4 4
// 样例输出
// 0 2 4 3 
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const long long INF = (1LL << 31) - 1;  // 2^31 - 1

int main() {
    int n, m, s;
    cin >> n >> m >> s;

    vector<vector<pair<int, int>>> graph(n + 1);  // to, weight

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }

    vector<long long> dist(n + 1, INF);
    dist[s] = 0;

    // 小根堆：{距离, 顶点}
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d != dist[u]) continue;  // 过时条目

        for (auto [v, w] : graph[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << dist[i] << " ";
        // if (i < n) cout ;
    }
    cout << endl;

    return 0;
}