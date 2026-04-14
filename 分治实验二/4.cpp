// -4 十进制转二进制
// 分数 5
// 作者 贾峻威
// 单位 郑州工业应用技术学院
// 输入一个十进制数，输出它的二进制形式。

// 提示：

// input()函数可以用于获取输入，其返回值类型是str字符串。

// int()可以把str类型的值转换为int类型的值。

// bin()函数的返回值类型是字符串。

// 字符串支持切片操作。

// 输入格式:
// 输入在一行中给出1个十进制形式的正整数。

// 输出格式:
// 输出对应的二进制，不包含前缀。

// 输入样例:
// 10
// 输出样例:
// 1010
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    // 特判 0
    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }
    
    string binary = "";
    while (n > 0) {
        binary += (n % 2) + '0';  // 取余数，转为字符
        n /= 2;
    }
    
    // 因为是从低位到高位，需要反转
    reverse(binary.begin(), binary.end());
    
    cout << binary << endl;
    
    return 0;
}