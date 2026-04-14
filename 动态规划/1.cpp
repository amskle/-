#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    vector<int> LT(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (arr[j] < arr[i]) {
                LT[i] = max(LT[i], LT[j] + 1);
            }
        }
    }
    vector<int> LS(n + 1, 1);
    for (int i = n; i >= 1; i--) {
        for (int j = i + 1; j <= n; j++) {
            if (arr[j] < arr[i]) {
                LS[i] = max(LS[i], LS[j] + 1);
            }
        }
    }
    int max_len = 0;
    for (int i = 1; i <= n; i++) {
        max_len = max(max_len, LT[i] + LS[i] - 1);
    }

    cout << n - max_len << endl;
}