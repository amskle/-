// R7-4 DNA序列比对
// 分数 15
// 作者 胡锦美
// 单位 闽江学院
// 【问题背景】：在生物学研究中，DNA序列比对是一个基础且关键的问题。它通过比较不同DNA序列的相似性，来揭示生物之间的进化关系、鉴定基因功能，甚至在医疗诊断中用于识别病原体变异。随着测序技术的发展，如何高效、准确地处理海量基因组数据，成为了现代生物信息学的重要挑战。你是一家生物科技公司的算法工程师，公司希望开发一款快速DNA序列比对工具，用于精准医疗中的病原体快速识别。你需要设计一个核心算法，能够计算两条DNA序列的相似度。
// 【题目描述】：DNA（脱氧核糖核酸）由四种碱基组成，分别用字母 A、G、C、T 表示。在DNA复制或测序过程中，可能会产生错误，主要包括：
// 缺失：漏掉某个碱基。
// 插入：多出某个碱基。
// 替换：某个碱基被错误地替换为另一种碱基。
// 两条DNA序列的编辑距离是指，用最小操作次数将一条序列通过最少的插入、删除或替换操作，转换为另一条序列所需的次数。这个距离可以衡量序列的相似程度，距离越小，相似度越高。
// 你的任务是，给定两条DNA序列，计算它们之间的编辑距离（最小操作次数）

// 输入格式:
// 第一行包含一个整数 n (1 ≤ n ≤ 100)，表示有 n 组 测试数据。对于每组测试数据：
// 第一行是字符串 s1 (长度 ≤ 10000)
// 第二行是字符串 s2 (长度 ≤ 10000)

// 字符串 s1 和 s2 仅由字符 A, G, C, T 组成。

// 输出格式:
// 输出共 n 行，每行一个整数，表示对应组测试数据中两条DNA序列的编辑距离。

// 输入样例:
// 3 
// AGCTAAGGCCTT
// AGCTAAGGCCT 
// AGCTAAGGCCTT 
// AGGCTAAGGCCTT 
// AGCTAAGGCCTT 
// AGCTTAAGGCTT
// 输出样例:
// 1 
// 1 
// 2
// 样例说明
// 第一组：AGCTAAGGCCTT 与 AGCTAAGGCCT 的距离为1，因为前者比后者多一个字符T（一次删除操作）。
// 第二组：AGCTAAGGCCTT 与 AGGCTAAGGCCTT 的距离为1，因为后者比前者多一个字符G（一次插入操作，从序列1到序列2的视角看）。
// 第三组：AGCTAAGGCCTT 与 AGCTTAAGGCTT 的距离为2，涉及两次替换操作（例如，第5位的A替换为T，第6位的A替换为T）或其他组合操作。
// 参考知识点：动态规划

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
int solve() {
    string s1, s2;
    cin >> s1 >> s2;
    int n = s1.length();
    int m = s2.length();

    // 使用两行数组进行滚动优化
    vector<int> prev(m + 1);
    vector<int> curr(m + 1);

    // 初始化：当 s1 为空时，转换为 s2 需要 m 次插入
    for (int j = 0; j <= m; j++) prev[j] = j;

    for (int i = 1; i <= n; i++) {
        curr[0] = i; // 当 s2 为空时，s1 需要 i 次删除
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                curr[j] = prev[j - 1]; // 字符相同，不消耗操作
            } else {
                // 取 删除、插入、替换 三者中的最小值 + 1
                curr[j] = min({prev[j] + 1, curr[j - 1] + 1, prev[j - 1] + 1});
            }
        }
        prev = curr; // 更新上一行数据
    }

    return prev[m];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        cout << solve() << "\n";
    }
    return 0;
}