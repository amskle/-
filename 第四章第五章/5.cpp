// R7-5 全排列
// 分数 100
// 作者 陈宇璟
// 单位 浙江大学
// 按照字典序输出自然数 1 到 n 所有不重复的排列，即 n 的全排列，要求所产生的任一数字序列中不允许出现重复的数字。

// 输入格式:
// 一个整数 n(n<=5)。

// 输出格式:
// 由 1~n 组成的所有不重复的数字序列，每行一个序列。

// 输入样例:
// 3
// 输出样例:
// 1 2 3 
// 1 3 2 
// 2 1 3 
// 2 3 1 
// 3 1 2 
// 3 2 1 
#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> path;
vector<bool> used;

void dfs() {
    if (path.size() == n) {
        for (int i = 0; i < n; i++) {
            cout << path[i] << " ";
        }
        cout << endl;
        return;
    }
    
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            used[i] = true;
            path.push_back(i);
            dfs();
            path.pop_back();
            used[i] = false;
        }
    }
}

int main() {
    cin >> n;
    used.resize(n + 1, false);
    dfs();
    return 0;
}