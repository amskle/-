// 7-8 sdut-C语言实验-全排列问题
// 分数 20
// 作者 马新娟
// 单位 山东理工大学
// 从n个不同元素任取m（m<=n）个元素，按照一定的顺序排列起来，叫做从n个不同元素中取出m个元素的一个排列，当m=n时所有的排列情况叫全排列。现输入n个递增的数，请你输出这n个数的全排列。全排列输出顺序如样例所示。

// ###输入格式:
// 第一行先输入一个整数n（1<=n<=10）。

// 接下来是一行输入n个由空格分开的互不相同的整数num （1 <= num <= 90000）。

// ###输出格式:
// 对于每组数据，每一种排列占一行，各元素间用逗号隔开。

// ###输入样例:

// 3
// 1 2 3
// ###输出样例:

// 1,2,3
// 1,3,2
// 2,1,3
// 2,3,1
// 3,1,2
// 3,2,1
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);  // 关闭C和C++的输入输出同步
    cin.tie(nullptr);             // 解除cin和cout的绑定

    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    sort(nums.begin(), nums.end());

    string output;          // 用字符串缓存结果
    do {
        for (int i = 0; i < n; i++) {
            if (i > 0) output += ',';
            output += to_string(nums[i]);
        }
        output += '\n';
    } while (next_permutation(nums.begin(), nums.end()));

    cout << output;         // 一次性输出所有结果

    return 0;
}