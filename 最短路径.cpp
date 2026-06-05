#include <iostream>
#include <vector>
#include <climits>
#include <cassert>
#include <string>

using namespace std;

// ==================== 图的数据结构 ====================

// 邻接矩阵表示图
class Graph
{
public:
    int V;                         // 顶点数
    vector<vector<int>> adjMatrix; // 邻接矩阵, adjMatrix[u][v] = 权重, INT_MAX 表示无边

    Graph(int vertices) : V(vertices)
    {
        adjMatrix.resize(V, vector<int>(V, INT_MAX));
        for (int i = 0; i < V; i++)
        {
            adjMatrix[i][i] = 0; // 自己到自己的距离为0
        }
    }

    // 添加有向边 u -> v, 权重为 w
    void addEdge(int u, int v, int w)
    {
        adjMatrix[u][v] = w;
    }

    // 添加无向边
    void addUndirectedEdge(int u, int v, int w)
    {
        adjMatrix[u][v] = w;
        adjMatrix[v][u] = w;
    }
};

// ==================== Dijkstra 算法 ====================

/*
 * Dijkstra 最短路径算法
 * 参数:
 *   graph - 带权图
 *   src   - 源点
 *   dist  - 输出: dist[i] 表示源点到顶点 i 的最短距离
 *   prev  - 输出: prev[i] 记录最短路径上 i 的前驱顶点 (-1 表示无前驱)
 *
 * TODO: 实现 Dijkstra 算法
 */
void dijkstra(const Graph &graph, int src, vector<int> &dist, vector<int> &prev)
{
    int V = graph.V;
    dist.assign(V, INT_MAX);
    prev.assign(V, -1);

    vector<bool> visited(V, false);
    dist[src] = 0; // 源点到自己的距离为0
    for (int m = 0; m < V; m++)
    {
        int min = INT_MAX;
        int index = -1;
        int i = 0;
        for (int i = 0; i < V; i++)
        {
            if (!visited[i] && dist[i] < min)
            {
                min = dist[i];
                index = i;
            }
        }

        if (index != -1)
        {
            visited[index] = true;

            for (int v = 0; v < V; v++)
            {
                if (!visited[v])
                {
                    if (graph.adjMatrix[index][v] != INT_MAX && dist[index] + graph.adjMatrix[index][v] < dist[v])
                    {
                        dist[v] = dist[index] + graph.adjMatrix[index][v];
                        prev[v] = index;
                    }
                }
            }
        }
        else
        {
            return;
        }
    }
}

// 根据 prev 数组还原从 src 到 dst 的最短路径
vector<int> reconstructPath(int src, int dst, const vector<int> &prev)
{
    vector<int> path;
    if (prev[dst] == -1 && src != dst)
    {
        return path; // 不可达
    }
    for (int v = dst; v != -1; v = prev[v])
    {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    if (path[0] != src)
    {
        return {};
    }
    return path;
}

// 打印最短路径结果
void printResult(int src, const vector<int> &dist, const vector<int> &prev)
{
    cout << "========== Dijkstra 最短路径结果 ==========" << endl;
    cout << "源点: " << src << endl;
    cout << "--------------------------------------------" << endl;
    for (int i = 0; i < (int)dist.size(); i++)
    {
        cout << "顶点 " << i << ": ";
        if (dist[i] == INT_MAX)
        {
            cout << "不可达" << endl;
        }
        else
        {
            cout << "最短距离 = " << dist[i] << ", 路径: ";
            vector<int> path = reconstructPath(src, i, prev);
            for (size_t j = 0; j < path.size(); j++)
            {
                if (j > 0)
                    cout << " -> ";
                cout << path[j];
            }
            cout << endl;
        }
    }
    cout << "============================================" << endl;
}

// ==================== Floyd 全源最短路径算法 ====================

/*
 * Floyd 算法: 求所有顶点对之间的最短路径
 * 参数:
 *   graph - 带权图
 *   dist  - 输出: dist[i][j] 表示 i 到 j 的最短距离
 *   path  - 输出: path[i][j] 记录 i→j 路径上的中间点 (-1 表示直达)
 */
void floyd(const Graph &graph, vector<vector<int>> &dist, vector<vector<int>> &path)
{
    int V = graph.V;
    dist = graph.adjMatrix;
    path.assign(V, vector<int>(V, -1));

    for (int k = 0; k < V; k++)
    {
        for (int i = 0; i < V; i++)
        {
            if (dist[i][k] == INT_MAX)
                continue; // 防溢出
            for (int j = 0; j < V; j++)
            {
                if (dist[k][j] == INT_MAX)
                    continue;
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = k;
                }
            }
        }
    }
}

// 递归还原 i→j 的路径
void floydGetPath(int i, int j, const vector<vector<int>> &path, vector<int> &result)
{
    if (path[i][j] == -1)
        return;
    int k = path[i][j];
    floydGetPath(i, k, path, result);
    result.push_back(k);
    floydGetPath(k, j, path, result);
}

void floydPrintResult(const vector<vector<int>> &dist,
                      const vector<vector<int>> &path)
{
    int V = (int)dist.size();
    cout << "========== Floyd 全源最短路径结果 ==========" << endl;
    cout << "距离矩阵:" << endl;
    cout << "    ";
    for (int j = 0; j < V; j++)
        cout << j << "\t";
    cout << endl;
    for (int i = 0; i < V; i++)
    {
        cout << i << " | ";
        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] == INT_MAX)
                cout << "∞\t";
            else
                cout << dist[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "\n路径详情:" << endl;
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (i == j)
                continue;
            cout << i << " → " << j << ": ";
            if (dist[i][j] == INT_MAX)
            {
                cout << "不可达" << endl;
            }
            else
            {
                vector<int> route;
                route.push_back(i);
                floydGetPath(i, j, path, route);
                route.push_back(j);
                for (size_t t = 0; t < route.size(); t++)
                {
                    if (t > 0)
                        cout << " → ";
                    cout << route[t];
                }
                cout << "  (距离=" << dist[i][j] << ")" << endl;
            }
        }
    }
    cout << "============================================" << endl;
}

// ==================== Floyd 测试框架 ====================

int floydTestCount = 0;
int floydPassCount = 0;

void floydRunTest(const string &testName, Graph &graph,
                  const vector<vector<int>> &expectedDist)
{
    floydTestCount++;
    cout << "\n[Floyd 测试 " << floydTestCount << "] " << testName << endl;

    vector<vector<int>> dist, path;
    floyd(graph, dist, path);
    floydPrintResult(dist, path);

    int V = (int)expectedDist.size();
    bool passed = true;
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            if (expectedDist[i][j] != INT_MAX && dist[i][j] != expectedDist[i][j])
            {
                cout << "  ? dist[" << i << "][" << j << "] 期望 "
                     << expectedDist[i][j] << ", 实际 " << dist[i][j] << endl;
                passed = false;
            }

    if (passed)
    {
        cout << "  ? 测试通过!" << endl;
        floydPassCount++;
    }
    else
        cout << "  ? 测试失败!" << endl;
}

void floydPrintSummary()
{
    cout << "\n============================================" << endl;
    cout << "Floyd 测试总结: " << floydPassCount << " / " << floydTestCount << " 通过" << endl;
    if (floydPassCount == floydTestCount)
        cout << "全部测试通过! ?" << endl;
    else
        cout << floydTestCount - floydPassCount << " 个测试失败 ?" << endl;
    cout << "============================================" << endl;
}

// ==================== Dijkstra 测试框架 ====================

int testCount = 0;
int passCount = 0;

void runTest(const string &testName, Graph &graph, int src,
             const vector<int> &expectedDist)
{
    testCount++;
    cout << "\n[测试 " << testCount << "] " << testName << endl;

    vector<int> dist, prev;
    dijkstra(graph, src, dist, prev);

    printResult(src, dist, prev);

    bool passed = true;
    for (int i = 0; i < (int)expectedDist.size(); i++)
    {
        if (expectedDist[i] != INT_MAX && dist[i] != expectedDist[i])
        {
            cout << "  ? 顶点 " << i << " 期望距离 " << expectedDist[i]
                 << ", 实际距离 " << dist[i] << endl;
            passed = false;
        }
    }

    if (passed)
    {
        cout << "  ? 测试通过!" << endl;
        passCount++;
    }
    else
    {
        cout << "  ? 测试失败!" << endl;
    }
}

void printSummary()
{
    cout << "\n============================================" << endl;
    cout << "测试总结: " << passCount << " / " << testCount << " 通过" << endl;
    if (passCount == testCount)
    {
        cout << "全部测试通过! ?" << endl;
    }
    else
    {
        cout << testCount - passCount << " 个测试失败 ?" << endl;
    }
    cout << "============================================" << endl;
}

// ==================== 主函数 ====================

int main()
{
    cout << "Dijkstra 最短路径算法测试" << endl;
    cout << "==========================" << endl;

    // ---------- 测试1: 简单有向图 ----------
    {
        Graph g(5);
        g.addEdge(0, 1, 10);
        g.addEdge(0, 2, 3);
        g.addEdge(1, 2, 1);
        g.addEdge(1, 3, 2);
        g.addEdge(2, 1, 4);
        g.addEdge(2, 3, 8);
        g.addEdge(2, 4, 2);
        g.addEdge(3, 4, 7);
        g.addEdge(4, 3, 9);

        // 源点 0 到各点的最短距离
        vector<int> expected = {0, 7, 3, 9, 5};
        runTest("简单有向图 (5个顶点)", g, 0, expected);
    }

    // ---------- 测试2: 无向图 ----------
    {
        Graph g(6);
        g.addUndirectedEdge(0, 1, 4);
        g.addUndirectedEdge(0, 2, 2);
        g.addUndirectedEdge(1, 2, 1);
        g.addUndirectedEdge(1, 3, 5);
        g.addUndirectedEdge(2, 3, 8);
        g.addUndirectedEdge(2, 4, 10);
        g.addUndirectedEdge(3, 4, 2);
        g.addUndirectedEdge(3, 5, 6);
        g.addUndirectedEdge(4, 5, 3);

        vector<int> expected = {0, 3, 2, 8, 10, 13};
        runTest("无向图 (6个顶点)", g, 0, expected);
    }

    // ---------- 测试3: 单顶点 ----------
    {
        Graph g(1);
        vector<int> expected = {0};
        runTest("单顶点图", g, 0, expected);
    }

    // ---------- 测试4: 不连通图 ----------
    {
        Graph g(4);
        g.addEdge(0, 1, 5);
        g.addEdge(1, 0, 5);
        // 顶点 2, 3 与 0,1 不连通

        vector<int> expected = {0, 5, INT_MAX, INT_MAX};
        runTest("不连通图 (4个顶点)", g, 0, expected);
    }

    printSummary();

    // ==================== Floyd 算法测试 ====================

    cout << "\n\n";
    cout << "Floyd 全源最短路径算法测试" << endl;
    cout << "=============================" << endl;

    floydTestCount = 0;
    floydPassCount = 0;

    // ---------- Floyd 测试1: 和 Dijkstra 测试1 同样的图 ----------
    {
        Graph g(5);
        g.addEdge(0, 1, 10);
        g.addEdge(0, 2, 3);
        g.addEdge(1, 2, 1);
        g.addEdge(1, 3, 2);
        g.addEdge(2, 1, 4);
        g.addEdge(2, 3, 8);
        g.addEdge(2, 4, 2);
        g.addEdge(3, 4, 7);
        g.addEdge(4, 3, 9);

        // 期望的 dist 矩阵
        vector<vector<int>> expected = {
            {0, 7, 3, 9, 5},
            {INT_MAX, 0, 1, 2, 3},
            {INT_MAX, 4, 0, 6, 2},
            {INT_MAX, INT_MAX, INT_MAX, 0, 7},
            {INT_MAX, INT_MAX, INT_MAX, 9, 0}};
        floydRunTest("有向图 (5个顶点)", g, expected);
    }

    // ---------- Floyd 测试2: 无向图 ----------
    {
        Graph g(4);
        g.addUndirectedEdge(0, 1, 1);
        g.addUndirectedEdge(0, 2, 4);
        g.addUndirectedEdge(1, 2, 2);
        g.addUndirectedEdge(1, 3, 6);
        g.addUndirectedEdge(2, 3, 3);

        vector<vector<int>> expected = {
            {0, 1, 3, 6},
            {1, 0, 2, 5},
            {3, 2, 0, 3},
            {6, 5, 3, 0}};
        floydRunTest("无向图 (4个顶点)", g, expected);
    }

    // ---------- Floyd 测试3: 单顶点 ----------
    {
        Graph g(1);
        vector<vector<int>> expected = {{0}};
        floydRunTest("单顶点图", g, expected);
    }

    floydPrintSummary();

    return 0;
}
