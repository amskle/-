// 7-3 Sumdiv
// 分数 10
// 作者 黄正鹏
// 单位 贵州工程应用技术学院
// 考虑两个自然数A和B。让我们是所有自然因子的和。确定S模9901（S除以9901的其余部分）。

// 输入格式:
// 唯一一行包含两个自然数A和B(0<=A，B<=50000000)，用空格隔开。

// 输出格式:
// 输出的唯一一行将包含S模9901。

// 输入样例:
// 在这里给出一组输入。例如：

// 2 3
// 输出样例:
// 在这里给出相应的输出。例如：

// 15

#include <iostream>
#include <cmath>
using namespace std;

const int MOD = 9901;

// 快速幂
int powmod(int a, int b) {
    int res = 1;
    a %= MOD;
    while (b) {
        if (b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

// 计算几何级数 1 + p + p^2 + ... + p^k 对 MOD 取模
int geometric_sum(int p, int k) {
    if (p % MOD == 1) {
        // 每一项都是 1
        return (k + 1) % MOD;
    }
    // 公式 (p^(k+1) - 1) / (p - 1)
    int numerator = (powmod(p, k + 1) - 1 + MOD) % MOD;
    int denominator = (p - 1 + MOD) % MOD;
    // 分母逆元
    int inv_den = powmod(denominator, MOD - 2);  // MOD 是质数，费马小定理
    return (numerator * inv_den) % MOD;
}

int main() {
    int A, B;
    cin >> A >> B;
    
    if (A == 0) {
        // 0^B = 0，因子只有 0，和是 0
        cout << 0 << endl;
        return 0;
    }
    
    int ans = 1;
    // 质因数分解 A
    int temp = A;
    for (int p = 2; p * p <= temp; p++) {
        if (temp % p == 0) {
            int cnt = 0;
            while (temp % p == 0) {
                temp /= p;
                cnt++;
            }
            // 对 p^(cnt * B) 的因子和累乘
            ans = (ans * geometric_sum(p, cnt * B)) % MOD;
        }
    }
    if (temp > 1) {
        // 剩余质因子
        ans = (ans * geometric_sum(temp, B)) % MOD;
    }
    
    cout << ans << endl;
    
    return 0;
}