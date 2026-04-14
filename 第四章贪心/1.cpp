// R7-1 多机调度问题--贪心
// 分数 12
// 作者 glee
// 单位 保定学院
// 有n个互相独立的作业（job1,job2,…jobn）,由m台相同的机器（med1,med2,…medm）进行处理。

// 完成作业jobi需要的时间为ti，每个作业都可在任意一台机器上处理，一旦上了一台机器，就必须处理完，不能转移到其他机器上去。

// 请你设计一种作业调度方案，使这n个作业在尽可能短的时间内由m台机器处理完。

// 贪心策略如下：处理时间最长的作业将按照机器的序号依次优先得到处理。

// 输入格式:
// 输入为3行，全部都是整数。

// 第一行输入2个数，分别是作业数n，机器数m。

// 第二行输入n个数，是作业的编号。

// 第三行输入n个数，是对应上行编号作业的处理时间。

// 输出格式:
// 输出m行，表示在m个机器上的作业运行顺序，以及在该机器上的总运行时间。

// 每一行输出，机器编号：作业序列（作业编号之间用->隔开），在该台机器上的处理总时间。


// 注意，n也许比m大，也许比m小。

// 如果某台机器分不到作业，则作业序列以及处理总时间均为0，也用逗号隔开。

// 输入样例:

// 5 3
// 1 2 3 4 5
// 2 8 4 5 3
// 输出样例:

// 1:2,8
// 2:4->1,7
// 3:3->5,7
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> jobId(n), jobTime(n);
    for (int i = 0; i < n; i++) cin >> jobId[i];
    for (int i = 0; i < n; i++) cin >> jobTime[i];
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) {
        return jobTime[a] > jobTime[b];
    });

    vector<int> load(m, 0);
    vector<vector<int>> assigned(m);

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    for (int i = 0; i < m; i++) pq.push({0, i});

    for (int i = 0; i < n; i++) {
        auto [l, mid] = pq.top();
        pq.pop();
        assigned[mid].push_back(order[i]);
        load[mid] += jobTime[order[i]];
        pq.push({load[mid], mid});
    }


    for (int i = 0; i < m; i++) {
        cout << i + 1 << ":";
        if (assigned[i].empty()) {
            cout << "0,0\n";
        } else {
            for (int j = 0; j < (int)assigned[i].size(); j++) {
                if (j > 0) cout << "->";
                cout << jobId[assigned[i][j]];
            }
            cout << "," << load[i] << "\n";
        }
    }

    return 0;
}