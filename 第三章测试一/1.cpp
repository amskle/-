// 上图给出了一个数字三角形。从三角形的顶部到底部有很多条不同的路径。对于每条路径，把路径上面的数加起来可以得到一个和，你的任务就是找到最大的和。

// 路径上的每一步只能从一个数走到下一层和它最近的左边的那个数或者右 边的那个数。此外，向左下走的次数与向右下走的次数相差不能超过 1。

// 输入格式:
// 输入的第一行包含一个整数 N (1<N<100)，表示三角形的行数。

// 下面的 N 行给出数字三角形。数字三角形上的数都是 0 至 100 之间的整数。

// 输出格式:
// 输出一个整数，表示答案。

// 输入样例:
// 5
// 7
// 3 8
// 8 1 0
// 2 7 4 4
// 4 5 2 6 5
// 输出样例:
// 27
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 110;
int a[N][N];
int dp[N][N][N];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            cin >> a[i][j];
        }
    }

    memset(dp, -1, sizeof(dp));
    dp[1][1][0] = a[1][1];

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            for (int k = 0; k <= i - 1; k++) {
                if (j > 1 && k >= 1 &&dp[i - 1][j - 1][k - 1] != -1) {
                    dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j - 1][k - 1] + a[i][j]);
                }
                if (j <= i - 1 && dp[i - 1][j][k] != -1) {
                    dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j][k] + a[i][j]);
                }
            }
        }
    }

    int ans = 0;
    int totalSteps = n - 1;

    for (int j = 1; j <= n; j++) {
        for (int k = 0; k <= totalSteps; k++) {
            int right = totalSteps - k;
            if (abs(k - right) <= 1 && dp[n][j][k] != -1) {
                ans = max(ans, dp[n][j][k]);
            }
        }
    }
    cout << ans << endl;

    return 0;
}