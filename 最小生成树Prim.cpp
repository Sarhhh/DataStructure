#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/*
 * 测试用无向有权图 (4个顶点, 5条边):
 *
 *       2
 *     0 --- 1
 *     |   / |
 *   3 | 4/  | 5
 *     | /   |
 *     2 --- 3
 *       7
 *
 * 邻接矩阵:
 *       0   1   2   3
 *   0   0   2   3  INF
 *   1   2   0   4   5
 *   2   3   4   0   7
 *   3  INF  5   7   0
 */

const int V = 4;
const int INF = INT_MAX; // 无边用 INF 表示

// 构建邻接矩阵 (返回 V×V 二维数组)
void buildGraph(int g[V][V])
{
    // 先全部初始化为 INF
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            g[i][j] = INF;

    // 无向边, 双向赋值
    g[0][1] = g[1][0] = 2; // 0-1, w=2
    g[0][2] = g[2][0] = 3; // 0-2, w=3
    g[1][2] = g[2][1] = 4; // 1-2, w=4
    g[1][3] = g[3][1] = 5; // 1-3, w=5
    g[2][3] = g[3][2] = 7; // 2-3, w=7
}

// 打印邻接矩阵
void printGraph(int g[V][V])
{
    cout << "===== 无向有权图 (邻接矩阵) =====" << endl;
    cout << "    ";
    for (int j = 0; j < V; j++)
        cout << j << "\t";
    cout << endl;
    for (int i = 0; i < V; i++)
    {
        cout << " " << i << "  ";
        for (int j = 0; j < V; j++)
        {
            if (g[i][j] == INF)
                cout << "INF\t";
            else
                cout << g[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "==================================" << endl;
}

void Prim(int g[V][V])
{
    vector<bool> visited(V, false); // 记录哪些顶点已加入生成树
    vector<int> lowcost(V, INF);    // lowcost[i] = 从已加入树的顶点到 i 的最小边权
    int totalWeight = 0;            // 生成树的总权重
    vector<int> edge(V, -1);        // edge[i]为  加入树后连接 i 的边的起点
    lowcost[0] = 0;
    for (int i = 1; i < V;i++)
    {
        int k = 0;
        for (int j = 0; j < V;j++)
        {
            if(lowcost[j]<k)
            {
                k = j;
            }

        }
    }
}

int main()
{
    int graph[V][V];
    buildGraph(graph);
    printGraph(graph);
    return 0;
}