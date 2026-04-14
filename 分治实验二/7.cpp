// 7-7 15.4 八皇后问题
// 分数 20
// 作者 clmg
// 单位 呼和浩特民族学院
// 会下国际象棋的人都很清楚：皇后可以在横、竖、斜线上不限步数地吃掉其他棋子。如何将8个皇后放在棋盘上（有8 * 8个方格），使它们谁也不能被吃掉。这就是著名的八皇后问题。 对于某个满足要求的8皇后的摆放方法，定义一个皇后串a与之对应，即a=b1b2…b8，其中bi为相应摆法中第i行皇后所处的列数。已经知道8皇后问题一共有92组解（即92个不同的皇后串）。
// 给出一个数b，要求输出第b个串。串的比较是这样的：皇后串x置于皇后串y之前，当且仅当将x视为整数时比y小.

// 输入格式:
// 第一行是测试数据的组数n，后面跟着n行输入。每组测试数据占一行，包括一个正整数b(1 <= b <= 92)。

// 输出格式:
// 输出有n行，每行输出对应一个输入。输出应是一个正整数，是对应于b的皇后串。

// 输入样例:
// 2
// 1
// 92
// 输出样例:
// 15863724
// 84136275
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<string> solutions; // 存储所有皇后串

bool isValid(int row, int col, const vector<int>& queens) {
    for (int i = 0; i < row; i++) {
        // 检查列冲突
        if (queens[i] == col) return false;
        // 检查对角线冲突
        if (abs(queens[i] - col) == abs(i - row)) return false;
    }
    return true;
}

void backtrack(int row, vector<int>& queens) {
    if (row == 8) {
        // 得到一个解，转换为字符串
        string s = "";
        for (int i = 0; i < 8; i++) {
            s += to_string(queens[i] + 1); // 转为 1-based 列号
        }
        solutions.push_back(s);
        return;
    }

    for (int col = 0; col < 8; col++) {
        if (isValid(row, col, queens)) {
            queens[row] = col;
            backtrack(row + 1, queens);
            // 回溯：无需显式清除，下一轮会覆盖
        }
    }
}

int main() {
    // 生成所有解
    vector<int> queens(8);
    backtrack(0, queens);

    // 按整数顺序排序（其实回溯时已经按列顺序，但为了严谨）
    sort(solutions.begin(), solutions.end());

    int n, b;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> b;
        cout << solutions[b - 1] << endl; // b 从 1 开始
    }

    return 0;
}