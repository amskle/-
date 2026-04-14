// R7-3 连续背包问题的贪心算法
// 分数 25
// 作者 陈越
// 单位 浙江大学
// 连续背包问题是这样定义的：给定一个总承重量为 W 的背包和 n 件物品的集合 S={s 
// 1
// ​
//  ,⋯,s 
// n
// ​
//  }，其中第 i 件物品有其重量 w 
// i
// ​
//   和价值 v 
// i
// ​
//  。如果将第 i 件物品 s 
// i
// ​
//   的 x 
// i
// ​
//   部分（x 
// i
// ​
//  ∈[0,1]）放入背包，则放入的重量为 x 
// i
// ​
//  ⋅w 
// i
// ​
//  ，放入的价值为 x 
// i
// ​
//  ⋅v 
// i
// ​
//  。要求一种分派方案  
// x
//  =(x 
// 1
// ​
//  ,⋯,x 
// n
// ​
//  )，在满足约束条件 R: Σ 
// i=1
// n
// ​
//  x 
// i
// ​
//  ⋅w 
// i
// ​
//  ≤W（即装入的物品总重量不超过背包承重）的前提下，使优化函数 f( 
// x
//  )=Σ 
// i=1
// n
// ​
//  x 
// i
// ​
//  ⋅v 
// i
// ​
//   取极大值（即装入的物品总价值最大）。

// 本题就请你实现解决这个问题的贪心算法。

// 输入格式：
// 输入首先在第一行中给出正整数 n（≤1000）和正实数 W（≤500）。随后两行各给出 n 个不超过 2000 的正实数，分别为 n 件物品的重量和价值，即第一行第 i 个数字表示第 i 件物品的重量，第二行对应位置表示其价值。同行数字间以空格分隔。

// 输出格式：
// 首先在第一行输出装入物品的最大总价值；随后一行输出最优分派方案的分量 (x 
// 1
// ​
//  ,⋯,x 
// n
// ​
//  )。要求输出小数点后 2 位。简单起见，每个分量后面跟一个空格。

// 输入样例：
// 5 11.0
// 1 2 5 6 7
// 1 6 18 22 28
// 输出样例：
// 42.67
// 0.00 0.00 0.00 0.67 1.00 
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Item {
    double weight, value, ratio;
    int index;  // 原始顺序
};

bool compare(const Item& a, const Item& b) {
    return a.ratio > b.ratio;  // 按单位价值降序
}

int main() {
    int n;
    double W;
    cin >> n >> W;

    vector<Item> items(n);
    for (int i = 0; i < n; i++) {
        cin >> items[i].weight;
    }
    for (int i = 0; i < n; i++) {
        cin >> items[i].value;
        items[i].ratio = items[i].value / items[i].weight;
        items[i].index = i;
    }

    // 按单位价值排序
    sort(items.begin(), items.end(), compare);

    vector<double> x(n, 0.0);  // 存放每个物品的装入比例（按原始顺序）
    double totalValue = 0.0;
    double remaining = W;

    for (const auto& item : items) {
        if (remaining <= 0) break;

        if (item.weight <= remaining) {
            // 全装
            x[item.index] = 1.0;
            totalValue += item.value;
            remaining -= item.weight;
        } else {
            // 装一部分
            double fraction = remaining / item.weight;
            x[item.index] = fraction;
            totalValue += fraction * item.value;
            remaining = 0;
        }
    }

    // 输出结果
    cout << fixed << setprecision(2) << totalValue << endl;
    for (int i = 0; i < n; i++) {
        cout << fixed << setprecision(2) << x[i] << " ";
    }
    cout << endl;

    return 0;
}