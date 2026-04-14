// 题目：104. 货仓选址
// 题目描述
// 在一条数轴上有 N 家商店，它们的坐标分别为 A1∼AN。

// 现在需要在数轴上建立一家货仓，每天清晨，从货仓到每家商店都要运送一车商品。

// 为了提高效率，求把货仓建在何处，可以使得货仓到每家商店的距离之和最小。

// 输入
// 第一行输入整数 N。

// 第二行 N 个整数 A1∼AN。

// 输出
// 输出一个整数，表示距离之和的最小值。

// 数据范围
// 1 ≤ N ≤ 100000,
// 0 ≤ Ai ≤ 40000

// 时空限制
// 1s / 64MB

// 输入样例
// 4
// 6 2 9 1
// 一键获取完整项目代码
// 1
// 2
// 输出样例
// 12
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    sort(a.begin(), a.end());
    
    // 中位数位置（0-based）
    int median = a[n / 2];
    
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += abs(a[i] - median);
    }
    
    cout << sum << endl;
    
    return 0;
}