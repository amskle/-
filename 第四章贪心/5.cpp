// R7-5 最小生成树-kruskal
// 分数 10
// 作者 任唯
// 单位 河北农业大学
// 题目给出一个无向连通图，要求求出其最小生成树的权值。

// 温馨提示：本题请使用kruskal最小生成树算法。

// 输入格式:
// 第一行包含两个整数 N(1<=N<=1x10 
// 6
//  ),M(1<=M<=1x10 
// 6
//  ) 表示该图共有 N 个结点和 M 条无向边。

// 接下来 M 行每行包含三个整数 X 
// i
// ​
//  ,Y 
// i
// ​
//  ,Z 
// i
// ​
//   ，表示有一条长度为 Z 
// i
// ​
//   的无向边连接结点 X 
// i
// ​
//  ,Y 
// i
// ​
//   。

// 输出格式:
// 输出一个整数表示最小生成树的各边的长度之和。

// 输入样例:
// 4 5
// 1 2 2
// 1 3 2
// 1 4 3
// 2 3 4
// 3 4 3
// 输出样例:
// 7
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, w;
};

vector<int> parent, rank_;

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);  // 路径压缩
    }
    return parent[x];
}

bool unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX == rootY) return false;

    // 按秩合并
    if (rank_[rootX] < rank_[rootY]) {
        parent[rootX] = rootY;
    } else if (rank_[rootX] > rank_[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootY] = rootX;
        rank_[rootX]++;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<Edge> edges(M);
    for (int i = 0; i < M; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    // 按权值排序
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });

    // 初始化并查集
    parent.resize(N + 1);
    rank_.resize(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        parent[i] = i;
    }

    long long totalWeight = 0;
    int edgesUsed = 0;

    for (const auto& e : edges) {
        if (unionSets(e.u, e.v)) {
            totalWeight += e.w;
            edgesUsed++;
            if (edgesUsed == N - 1) break;
        }
    }

    cout << totalWeight << endl;

    return 0;
}