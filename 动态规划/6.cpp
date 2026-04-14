// R7-6 回文串问题
// 分数 25
// 作者 高见元
// 单位 湖北经济学院
// 一个字符串，如果从左到右读和从右到左读是完全一样的，比如"aba"，我们称其为回文串。现在给你一个字符串，可在任意位置添加字符，求最少添加几个字符，才能使其变成一个回文串。

// 输入格式:
// 任意给定的一个字符串，其长度不超过1000.

// 输出格式:
// 能变成回文串所需添加的最少字符数。

// 输入样例:
// 在这里给出一组输入。例如：

// Ab3bd
// Abb
// 输出样例:
// 在这里给出相应的输出。例如：

// 2
// 1
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 计算两个字符串的最长公共子序列 (LCS)
int getLCS(string s1, string s2) {
    int n = s1.length();
    // dp[i][j] 表示 s1 前 i 个字符与 s2 前 j 个字符的 LCS 长度
    // 考虑到长度 1000，二维数组 int[1001][1001] 约占用 4MB，完全可行
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][n];
}

int main() {
    string s;
    // 注意：题目样例中有空格或多组输入的可能，根据格式使用 cin 或 while(cin >> s)
    while (cin >> s) {
        string rs = s;
        reverse(rs.begin(), rs.end()); // 获取逆序字符串

        int n = s.length();
        int lcs_len = getLCS(s, rs);

        // 最少添加次数 = 总长 - 最长回文子序列长度
        cout << n - lcs_len << endl;
    }

    return 0;
}