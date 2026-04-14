// R7-3 石子合并
// 分数 30
// 作者 杜祥军
// 单位 青岛大学
// 在一个圆形操场的四周摆放 N 堆石子，现要将石子有次序地合并成一堆，规定每次只能选相邻的2堆合并成新的一堆，并将新的一堆的石子数，记为该次合并的得分。

// 试设计出一个算法,计算出将 N 堆石子合并成 1 堆的最小得分和最大得分。

// 输入格式:
// 数据的第 1行是正整数 N，表示有 N 堆石子。

// 第 2 行有 N 个整数，第 i 个整数ai表示第 i 堆石子的个数。

// 输出格式:
// 输出共 2 行，第 1 行为最小得分，第 2 行为最大得分。

// 输入样例:
// 4
// 4 5 9 4
// 输出样例:
// 43
// 54
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

int main() {
    int n;
    cin >> n;
    vector<int> a(2 * n + 1);
    vector<int> s(2 * n + 1, 0);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i + n] = a[i]; // 环形拆解为线性
    }

    // 计算前缀和
    for (int i = 1; i <= 2 * n; i++) {
        s[i] = s[i - 1] + a[i];
    }

    // f[i][j] 存最小，g[i][j] 存最大
    vector<vector<int>> f(2 * n + 1, vector<int>(2 * n + 1, INF));
    vector<vector<int>> g(2 * n + 1, vector<int>(2 * n + 1, 0));

    // 初始化：单堆石子合并得分为 0
    for (int i = 1; i <= 2 * n; i++) {
        f[i][i] = 0;
    }

    // 区间 DP
    for (int len = 2; len <= n; len++) { // 枚举区间长度
        for (int i = 1; i + len - 1 <= 2 * n; i++) { // 枚举起点
            int j = i + len - 1; // 终点
            for (int k = i; k < j; k++) { // 枚举分割点
                f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j] + s[j] - s[i - 1]);
                g[i][j] = max(g[i][j], g[i][k] + g[k + 1][j] + s[j] - s[i - 1]);
            }
        }
    }

    int min_score = INF, max_score = 0;
    for (int i = 1; i <= n; i++) {
        min_score = min(min_score, f[i][i + n - 1]);
        max_score = max(max_score, g[i][i + n - 1]);
    }

    cout << min_score << endl << max_score << endl;

    return 0;
}