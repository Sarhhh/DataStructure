#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <functional>
using namespace std;

// ==================== 图（邻接矩阵）====================
class Graph {
public:
    int V;
    vector<vector<int>> mat;

    Graph(int n) : V(n) {
        mat.assign(n, vector<int>(n, INT_MAX));
        for (int i = 0; i < n; i++) mat[i][i] = 0;
    }
    void addEdge(int u, int v, int w) { mat[u][v] = w; }
    void addUndirectedEdge(int u, int v, int w) { mat[u][v] = mat[v][u] = w; }
};

// ==================== Dijkstra ====================
void dijkstra(const Graph& g, int src, vector<int>& dist, vector<int>& prev) {
    int V = g.V;
    dist.assign(V, INT_MAX);  dist[src] = 0;
    prev.assign(V, -1);
    vector<bool> done(V, false);

    for (int r = 0; r < V; r++) {
        int u = -1, best = INT_MAX;
        for (int i = 0; i < V; i++)
            if (!done[i] && dist[i] < best) { best = dist[i]; u = i; }
        if (u == -1) return;
        done[u] = true;
        for (int v = 0; v < V; v++)
            if (!done[v] && g.mat[u][v] != INT_MAX && dist[u] + g.mat[u][v] < dist[v]) {
                dist[v] = dist[u] + g.mat[u][v];
                prev[v] = u;
            }
    }
}

// ==================== Floyd ====================
void floyd(const Graph& g, vector<vector<int>>& dist, vector<vector<int>>& path) {
    int V = g.V;
    dist = g.mat;
    path.assign(V, vector<int>(V, -1));
    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++) {
            if (dist[i][k] == INT_MAX) continue;
            for (int j = 0; j < V; j++) {
                if (dist[k][j] == INT_MAX) continue;
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = k;
                }
            }
        }
}

// ==================== 打印 ====================
void printDijkstra(int src, const vector<int>& dist, const vector<int>& prev) {
    for (int i = 0; i < (int)dist.size(); i++) {
        cout << "  0→" << i << ": ";
        if (dist[i] == INT_MAX) { cout << "不可达" << endl; continue; }
        vector<int> p;
        for (int v = i; v != -1; v = prev[v]) p.push_back(v);
        reverse(p.begin(), p.end());
        cout << dist[i] << "  [";
        for (size_t j = 0; j < p.size(); j++) {
            if (j) cout << "→";  cout << p[j];
        }
        cout << "]" << endl;
    }
}

void printFloyd(const vector<vector<int>>& dist, const vector<vector<int>>& path) {
    int V = dist.size();
    cout << "  距离矩阵:\n";
    for (int i = 0; i < V; i++) {
        cout << "    ";
        for (int j = 0; j < V; j++)
            if (dist[i][j] == INT_MAX) cout << "∞\t"; else cout << dist[i][j] << "\t";
        cout << endl;
    }
    cout << "  最短路径:\n";
    function<void(int,int,vector<int>&)> getPath = [&](int a, int b, vector<int>& r) {
        if (path[a][b] == -1) return;
        getPath(a, path[a][b], r);
        r.push_back(path[a][b]);
        getPath(path[a][b], b, r);
    };
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++) {
            if (i == j) continue;
            cout << "    " << i << "→" << j << ": ";
            if (dist[i][j] == INT_MAX) { cout << "不可达" << endl; continue; }
            vector<int> r{i};
            getPath(i, j, r); r.push_back(j);
            cout << dist[i][j] << "  [";
            for (size_t t = 0; t < r.size(); t++) { if (t) cout << "→"; cout << r[t]; }
            cout << "]" << endl;
        }
}

// ==================== main ====================
int main() {
    // ---------- Dijkstra ----------
    cout << "========== Dijkstra ==========" << endl;
    {
        Graph g(5);
        g.addEdge(0, 1, 10); g.addEdge(0, 2, 3);
        g.addEdge(1, 2, 1);  g.addEdge(1, 3, 2);
        g.addEdge(2, 1, 4);  g.addEdge(2, 3, 8);
        g.addEdge(2, 4, 2);  g.addEdge(3, 4, 7);
        g.addEdge(4, 3, 9);
        vector<int> dist, prev;
        dijkstra(g, 0, dist, prev);
        printDijkstra(0, dist, prev);
    }

    // ---------- Floyd ----------
    cout << "\n========== Floyd ==========" << endl;
    {
        Graph g(4);
        g.addUndirectedEdge(0, 1, 1);
        g.addUndirectedEdge(0, 2, 4);
        g.addUndirectedEdge(1, 2, 2);
        g.addUndirectedEdge(1, 3, 6);
        g.addUndirectedEdge(2, 3, 3);
        vector<vector<int>> dist, path;
        floyd(g, dist, path);
        printFloyd(dist, path);
    }
    return 0;
}
