// R7-3 选数问题
// 分数 8
// 作者 燕敏
// 单位 成都锦城学院
// 给定若干个正整数a0、a0 、…、an-1 ，从中选出若干数，使它们的和恰好为k，

// 要求找选择元素个数最少的解。如果有多个最优解，输出字典序最小的。

// 输入格式:
// 输入有两行，第一行给出2个正整数n,k，用空格分隔。第二行是用空格分隔的n个整数。

// 输出格式:
// 输出有两行，第一行从小到大输出选择的元素，第二行输出元素的个数。

// 输入样例:
// 在这里给出一组输入。例如：

// 5 9
// 1 1 4 5 7
// 输出样例:
// 在这里给出相应的输出。例如：

// 4 5
// 2
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct State {
    int sum;
    int last_idx;
    vector<int> path;
};

int main() {
    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // 1. 排序：为了满足字典序最小
    sort(a.begin(), a.end());

    // 2. BFS：按选择元素的个数层层递增
    queue<State> q;
    q.push({0, -1, {}});

    vector<int> best_path;
    bool found = false;

    while (!q.empty()) {
        int sz = q.size();
        // 记录当前层所有可能的成功路径，用于比较字典序
        vector<vector<int>> potential_results;

        for (int i = 0; i < sz; i++) {
            State curr = q.front();
            q.pop();

            if (curr.sum == k) {
                found = true;
                potential_results.push_back(curr.path);
                continue;
            }

            // 剪枝：如果已经找到结果，不再往更深层搜索
            if (found) continue;

            for (int j = curr.last_idx + 1; j < n; j++) {
                if (curr.sum + a[j] <= k) {
                    State next = curr;
                    next.sum += a[j];
                    next.last_idx = j;
                    next.path.push_back(a[j]);
                    q.push(next);
                }
            }
        }

        if (found) {
            // 在所有解中找字典序最小的
            sort(potential_results.begin(), potential_results.end());
            best_path = potential_results[0];
            break;
        }
    }

    // 3. 输出
    for (int i = 0; i < best_path.size(); i++) {
        cout << best_path[i] << (i == best_path.size() - 1 ? "" : " ");
    }
    cout << endl << best_path.size() << endl;

    return 0;
}