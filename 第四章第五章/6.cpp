// R7-6 找宝藏
// 分数 20
// 作者 燕敏
// 单位 成都锦城学院
// _EKKDJ9TF5)F2M506BTDGAV.png

// 小明得到了一张藏宝图（如上图所示），小明当前的位置在左上角白色的方块，
// 其中黑色的方块中埋有地雷，不能走，灰色的方块是安全地带可以走，宝藏藏
// 在T所在的方块。小明只能一步一步走，不能跳跃，并且只能走上、下、左、右
// 四个方向，不能斜着走。请你帮他判断一下能否找到宝藏，如果能找到宝藏，输出
// My God！如果不能找到宝藏，输出My God？

// 输入格式:
// 首先输入2个整数n，m（0<n,m<100）,代表藏宝图的高和宽。
// 然后输入n行，每行m个字符，各字符的含义如下：
// S代表小明的当前位置；T代表宝藏的位置；1代表地雷，不能走；0代表路，可以走。

// 输出格式:
// 如果能找到宝藏，输出My God！如果不能找到宝藏，输出My God？

// 输入样例:
// 在这里给出一组输入。例如：

// 5 5
// S100T
// 00010
// 11000
// 00010
// 01001
// 输出样例:
// 在这里给出相应的输出。例如：

// My God!

#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<string> grid;
vector<vector<bool>> visited;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
bool found = false;

void dfs(int x, int y) {
    if (grid[x][y] == 'T') {
        found = true;
        return;
    }
    
    visited[x][y] = true;
    
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny]) {
            if (grid[nx][ny] != '1') {
                dfs(nx, ny);
                if (found) return; // 提前结束
            }
        }
    }
}

int main() {
    cin >> n >> m;
    grid.resize(n);
    visited.assign(n, vector<bool>(m, false));
    
    int sx = -1, sy = -1;
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'S') {
                sx = i;
                sy = j;
            }
        }
    }
    
    dfs(sx, sy);
    
    if (found) {
        cout << "My God!" << endl;
    } else {
        cout << "My God?" << endl;
    }
    
    return 0;
}