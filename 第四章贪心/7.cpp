// R7-7 找到最小数
// 分数 20
// 作者 zx
// 单位 青岛大学
// 找到最小数。

// 输入一个高精度的正整数N（不超过5000位） ，
// 去掉其中任意k个数字后剩下的数字按原左右次序
// 将组成一个新的正整数。
// 对给定的N和k，寻找一种方案使得剩下的数字组成的新数最小。

// ###输入格式：
// 第一行给定一个不超过五千位的正整数n。
// 第二行给定一个不超过n的位数的非负整数k。

// ###输出格式：
// 最后剩下的最小数。

// ###输入样例：

// 175438 
// 4
// ###输出样例：

// 13

#include <iostream>
#include <string>
using namespace std;

int main() {
    string N;
    int k;
    cin >> N >> k;

    string result;
    int len = N.length();
    int toDelete = k;

    for (int i = 0; i < len; i++) {
        // 当还能删除，且栈顶数字 > 当前数字时，删除栈顶
        while (toDelete > 0 && !result.empty() && result.back() > N[i]) {
            result.pop_back();
            toDelete--;
        }
        result.push_back(N[i]);
    }

    // 如果还有删除次数，从末尾删除
    if (toDelete > 0) {
        result.erase(result.length() - toDelete);
    }

    // 去掉前导零
    int pos = 0;
    while (pos < result.length() && result[pos] == '0') {
        pos++;
    }

    if (pos == result.length()) {
        cout << "0" << endl;
    } else {
        cout << result.substr(pos) << endl;
    }

    return 0;
}