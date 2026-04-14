// 7-9 十进制转任意进制(自然数)
// 分数 10
// 作者 李祥
// 单位 湖北经济学院
// 请编写程序，将十进制数转换成 n 进制数。

// 输入格式
// x  n

// 说明：x(0≤x≤2 
// −63
//  −1) 为十进制数，n(2≤n≤36) 为数制。

// 输出格式
// y

// 说明：y 为 n 进制整数 (超过 9 的数字，用大写字母表示：A 表示 10, B 表示 11, ..., Z 表示 35)。

// 输入样例1
// 37 2

// 输出样例1
// 100101

// 输入样例2
// 4786 20

// 输出样例2
// BJ6
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    unsigned long long x;
    int n;
    cin >> x >> n;

    if (x == 0) {
        cout << 0 << endl;
        return 0;
    }

    string result = "";
    while (x > 0) {
        int remainder = x % n;
        char ch;
        if (remainder < 10) {
            ch = '0' + remainder;
        } else {
            ch = 'A' + (remainder - 10);
        }
        result += ch;
        x /= n;
    }

    // 反转字符串（因为余数是从低位到高位收集的）
    reverse(result.begin(), result.end());

    cout << result << endl;

    return 0;
}
