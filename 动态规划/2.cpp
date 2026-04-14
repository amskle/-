#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

// 辅助函数：计算前缀和
vector<ll> get_prefix_sum(vector<int>& v) {
    vector<ll> s(v.size() + 1, 0);
    for (int i = 0; i < v.size(); i++) {
        s[i + 1] = s[i] + v[i];
    }
    return s;
}

int main() {
    // 1. 高速 I/O 优化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<int> ws(n), vs(n);
    vector<int> v1, v2, v3;

    // 读入数据并分类
    for (int i = 0; i < n; i++) cin >> ws[i];
    for (int i = 0; i < n; i++) cin >> vs[i];
    for (int i = 0; i < n; i++) {
        if (ws[i] == 1) v1.push_back(vs[i]);
        else if (ws[i] == 2) v2.push_back(vs[i]);
        else v3.push_back(vs[i]);
    }

    // 2. 降序排序：保证贪心选择最优
    sort(v1.rbegin(), v1.rend());
    sort(v2.rbegin(), v2.rend());
    sort(v3.rbegin(), v3.rend());

    // 3. 预处理重量为 1 和 2 的组合 (dp12)
    // dp12[j] 表示容量为 j 时，只用 w=1 和 w=2 的物品能达到的最大价值
    vector<ll> dp12(m + 1, 0);
    
    // 采用双指针/贪心策略填充 dp12
    // 我们需要分别处理偶数和奇数容量，因为 w=2 的加入会改变奇偶性
    for (int start_cap : {0, 1}) {
        int p1 = 0, p2 = 0;
        ll current_v = 0;
        
        // 如果从容量 1 开始，先放一个最贵的 w=1
        if (start_cap == 1) {
            if (!v1.empty()) {
                current_v = v1[0];
                p1 = 1;
            } else {
                continue; // 没有 w=1 的话，奇数容量初始就无法从 1 开始有效递推
            }
        }
        if (start_cap <= m) dp12[start_cap] = max(dp12[start_cap], current_v);

        // 每次增加 2 个单位容量
        for (int j = start_cap + 2; j <= m; j += 2) {
            ll opt1 = -1, opt2 = -1;
            // 方案 A: 再加两个 w=1
            if (p1 + 1 < v1.size()) opt1 = (ll)v1[p1] + v1[p1 + 1];
            // 方案 B: 再加一个 w=2
            if (p2 < v2.size()) opt2 = v2[p2];

            if (opt1 > opt2 && opt1 != -1) {
                current_v += opt1;
                p1 += 2;
            } else if (opt2 != -1) {
                current_v += opt2;
                p2++;
            } else if (p1 < v1.size()) {
                // 如果只剩下一个 w=1，也加上
                current_v += v1[p1];
                p1++;
            }
            dp12[j] = max(dp12[j], current_v);
        }
    }

    // 修正 dp12 的单调性：容量越大价值一定不减
    for (int j = 1; j <= m; j++) {
        dp12[j] = max(dp12[j], dp12[j - 1]);
    }

    // 4. 枚举重量为 3 的物品数量
    vector<ll> s3 = get_prefix_sum(v3);
    ll max_ans = 0;

    for (int i = 0; i <= v3.size(); i++) {
        ll weight3 = (ll)i * 3;
        if (weight3 > m) break;
        
        ll current_total_v = s3[i] + dp12[m - weight3];
        if (current_total_v > max_ans) {
            max_ans = current_total_v;
        }
    }

    cout << max_ans << endl;

    return 0;
}