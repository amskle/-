// 7-1 h0093-递归实现组合型枚举
// 分数 10
// 作者 黄正鹏
// 单位 贵州工程应用技术学院
// 从 1∼n 这 n 个整数中随机选出 m 个，输出所有可能的选择方案。

// 输入格式:
// 两个整数 n（n>0）,m（0≤m≤n） ,在同一行用空格隔开。

// n+(n−m)≤25

// 输出格式:
// 按照从小到大的顺序输出所有方案，每行 1 个。

// 首先，同一行内的数升序排列，相邻两个数用一个空格隔开。

// 其次，对于两个不同的行，对应下标的数一一比较，字典序较小的排在前面（例如 1 3 5 7 排在 1 3 6 8 前面）。

// 输入样例:
// 在这里给出一组输入。例如：

// 5 3
// 输出样例:
// 在这里给出相应的输出。例如：

// 1 2 3 
// 1 2 4 
// 1 2 5 
// 1 3 4 
// 1 3 5 
// 1 4 5 
// 2 3 4 
// 2 3 5 
// 2 4 5 
// 3 4 5 
#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> path;  // 存放当前选的数

void dfs(int start) {
    // 如果已经选够了 m 个数，就输出
    if (path.size() == m) {
        for (int i = 0; i < m; i++) {
            cout << path[i] << " ";
        }
        cout << endl;
        return;
    }
    
    // 从 start 开始选，保证升序
    for (int i = start; i <= n; i++) {
        path.push_back(i);
        dfs(i + 1);
        path.pop_back();  // 回溯
    }
}

int main() {
    cin >> n >> m;
    dfs(1);
    return 0;
}