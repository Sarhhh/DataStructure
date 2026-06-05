#include <iostream>
#include <queue>

using namespace std;

const int N = 5;

// 计算每个顶点的度，返回度最大的顶点下标（若相同则返回编号最小的）
int selectStart(bool graph[N][N])
{
    int degrees[N] = {0};
    int maxDeg = -1;
    int start = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (graph[i][j])
                degrees[i]++;
        }
        if (degrees[i] > maxDeg)
        {
            maxDeg = degrees[i];
            start = i;
        }
    }
    return start;
}

// 广度优先遍历
void BFS(bool graph[N][N], int start)
{
    bool visited[N] = {false};
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "BFS 遍历顺序: ";
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        cout << v << " ";

        // 遍历 v 的所有邻居
        for (int j = 0; j < N; j++)
        {
            if (graph[v][j] && !visited[j])
            {
                visited[j] = true;
                q.push(j);
            }
        }
    }
    cout << endl;
}

int main()
{
    // 测试用例：5×5 无向图邻接矩阵
    //
    //       (0)─────(3)
    //        |       |
    //        |       |
    //       (1)─────(2)─────(4)
    //
    //     0 1 2 3 4
    // 0   0 1 0 1 0    度=2
    // 1   1 0 1 0 0    度=2
    // 2   0 1 0 1 1    度=3 ← 最大，选为起点
    // 3   1 0 1 0 0    度=2
    // 4   0 0 1 0 0    度=1
    bool graph[N][N] = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 1},
        {1, 0, 1, 0, 0},
        {0, 0, 1, 0, 0}};

    int start = selectStart(graph);
    BFS(graph, start);

    return 0;
}