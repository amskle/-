// 7-6 最小公倍数（递归）
// 分数 100
// 作者 龚如宾
// 单位 金陵科技学院
// 本题目要求读入2个整数a和b，然后输出它们的最小公倍数。

// 输入格式:
// 输入在一行中给出2个正整数，以空格分隔。

// 输出格式:
// 输出最小公倍数。

// 输入样例:
// 在这里给出一组输入。例如：

// 6 14
// 输出样例:
// 在这里给出相应的输出。例如：

// 42
#include <iostream>
using namespace std;

// 递归求最大公约数
long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// 求最小公倍数
long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b;  // 先除后乘，防止溢出
}

int main() {
    long long a, b;
    cin >> a >> b;
    cout << lcm(a, b) << endl;
    return 0;
}