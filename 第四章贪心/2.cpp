// R7-2 活动安排问题的贪心算法
// 分数 25
// 作者 陈越
// 单位 浙江大学
// 活动安排问题是这样定义的：假设只有一间活动室可用，现有 n 个俱乐部来申请使用，每个俱乐部的活动都有一个计划开始的时间和结束的时间。要求审批通过的所有活动在时间安排上不能有冲突，问最多可以批准多少个俱乐部的申请？记俱乐部的活动集合为 S={a 
// i
// ​
//  } 
// i=1
// n
// ​
//  ，第 i 项活动 a 
// i
// ​
//   的活动时间为半开闭的区间 [s 
// i
// ​
//  ,f 
// i
// ​
//  )。两项活动 a 
// i
// ​
//   和 a 
// j
// ​
//  ，如果满足 s 
// i
// ​
//  ≥f 
// j
// ​
//   或 s 
// j
// ​
//  ≥f 
// i
// ​
//  ，就说明它们在时间安排上没有冲突。

// 本题就请你实现解决这个问题的贪心算法。

// 输入格式：
// 输入首先在第一行中给出正整数 n（≤10 
// 4
//  ）。随后两行各给出 n 个不超过 10 
// 5
//   的非负整数，分别为 n 个俱乐部的活动开始时间和结束时间，即第一行第 i 个数字表示第 i 个俱乐部活动的开始时间，第二行对应位置表示其结束时间。同行数字间以空格分隔。题目保证每个俱乐部的开始时间都严格早于结束时间。

// 输出格式：
// 在一行中输出能够被批准的最大申请数量。

// 输入样例：
// 11
// 3 0 5 3 5 6 8 7 2 12 1
// 5 6 7 9 9 10 11 13 14 16 4
// 输出样例：
// 4
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Activity {
    int start, end;
};

bool compare(const Activity& a, const Activity& b) {
    return a.end < b.end;  // 按结束时间升序
}

int main() {
    int n;
    cin >> n;

    vector<Activity> acts(n);
    for (int i = 0; i < n; i++) {
        cin >> acts[i].start;
    }
    for (int i = 0; i < n; i++) {
        cin >> acts[i].end;
    }

    sort(acts.begin(), acts.end(), compare);

    int count = 0;
    int last_end = -1;  // 上一个选中活动的结束时间，初始为 -1 保证第一个活动能选

    for (int i = 0; i < n; i++) {
        if (acts[i].start >= last_end) {
            count++;
            last_end = acts[i].end;
        }
    }

    cout << count << endl;

    return 0;
}