#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int totalSolutions = 0;
vector<int> queens(8, 0); // queens[i] = col 表示第 i 行的皇后放在了第 col 列

// 检查在 (row, col) 放置皇后是否安全
bool isValid(int row, int col) {
    for (int i = 0; i < row; ++i) {
        // queens[i] == col 检查同一列是否已经有皇后
        // abs(i - row) == abs(queens[i] - col) 检查对角线是否冲突
        if (queens[i] == col || abs(i - row) == abs(queens[i] - col)) {
            return false;
        }
    }
    return true;
}

// 打印棋盘解法（为了展示直观）
void printBoard() {
    cout << "解法 " << totalSolutions << ":" << endl;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (queens[i] == j) {
                cout << "Q ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << "----------------" << endl;
}

// 回溯主逻辑：在第 row 行尝试放置皇后
void solve(int row) {
    // 终止条件：如果已经到达第8行（索引为8），说明 0-7 行已经放满，找到了一个解
    if (row == 8) {
        totalSolutions++;
        // 打印前3个解作为展示，避免输出全部92个解导致刷屏
        if (totalSolutions <= 3) { 
            printBoard();
        }
        return;
    }

    // 遍历当前行的每一列，尝试放置
    for (int col = 0; col < 8; ++col) {
        if (isValid(row, col)) {
            queens[row] = col; // 放置皇后，记录列号
            solve(row + 1);    // 递归去放置下一行
            // 回溯点：上一行代码执行完毕后（无论是找到解还是走入死胡同退回），
            // 当前循环会继续到下一列 (col++)，直接覆盖 queens[row] 的值。
            // 因此在一维数组表示法下，不需要显式执行诸如 queens[row] = 0 的撤销操作。
        }
    }
}

int main() {
    cout << "开始计算八皇后问题..." << endl;
    solve(0);
    cout << "计算完毕！八皇后问题总共找到了 " << totalSolutions << " 种解法。" << endl;
    return 0;
}


