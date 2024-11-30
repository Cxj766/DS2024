#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <climits>
using namespace std;

// 图的类定义
class Graph {
private:
    int V; // 顶点数
    vector<vector<pair<int, int>>> adj; // 邻接表存储，pair中first是目标顶点，second是权重

public:
    // 构造函数
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
    }

    // 添加边
    void addEdge(int u, int v, int weight) {
        adj[u].push_back({ v, weight });
        adj[v].push_back({ u, weight }); // 无向图
    }

    // BFS实现
    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS starting from vertex " << start << ": ";

        while (!q.empty()) {
            int v = q.front();
            cout << v << " ";
            q.pop();

            for (auto& neighbor : adj[v]) {
                int next = neighbor.first;
                if (!visited[next]) {
                    visited[next] = true;
                    q.push(next);
                }
            }
        }
        cout << endl;
    }

    // DFS实现
    void DFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        for (auto& neighbor : adj[v]) {
            int next = neighbor.first;
            if (!visited[next]) {
                DFSUtil(next, visited);
            }
        }
    }

    void DFS(int start) {
        vector<bool> visited(V, false);
        cout << "DFS starting from vertex " << start << ": ";
        DFSUtil(start, visited);
        cout << endl;
    }

    // Dijkstra最短路径算法
    void dijkstra(int start) {
        vector<int> dist(V, INT_MAX);
        vector<bool> visited(V, false);

        dist[start] = 0;

        for (int count = 0; count < V - 1; count++) {
            int u = -1;
            int min_dist = INT_MAX;

            // 找到当前最短距离的顶点
            for (int v = 0; v < V; v++) {
                if (!visited[v] && dist[v] < min_dist) {
                    min_dist = dist[v];
                    u = v;
                }
            }

            if (u == -1) break;

            visited[u] = true;

            // 更新相邻顶点的距离
            for (auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (!visited[v] && dist[u] != INT_MAX &&
                    dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }

        cout << "Shortest distances from vertex " << start << ":\n";
        for (int i = 0; i < V; i++) {
            cout << "To " << i << ": " << dist[i] << endl;
        }
    }

    // Prim最小生成树算法
    void primMST() {
        vector<int> parent(V, -1);
        vector<int> key(V, INT_MAX);
        vector<bool> inMST(V, false);

        key[0] = 0;

        for (int count = 0; count < V - 1; count++) {
            int u = -1;
            int min_key = INT_MAX;

            // 找到权值最小的顶点
            for (int v = 0; v < V; v++) {
                if (!inMST[v] && key[v] < min_key) {
                    min_key = key[v];
                    u = v;
                }
            }

            if (u == -1) break;

            inMST[u] = true;

            // 更新相邻顶点的权值
            for (auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (!inMST[v] && weight < key[v]) {
                    parent[v] = u;
                    key[v] = weight;
                }
            }
        }

        cout << "Minimum Spanning Tree edges:\n";
        int totalWeight = 0;
        for (int i = 1; i < V; i++) {
            if (parent[i] != -1) {
                cout << parent[i] << " - " << i << endl;
                // 找到对应的边权重
                for (auto& edge : adj[i]) {
                    if (edge.first == parent[i]) {
                        totalWeight += edge.second;
                        break;
                    }
                }
            }
        }
        cout << "Total MST weight: " << totalWeight << endl;
    }
};

// 测试主函数
int main() {
    // 创建一个具有6个顶点的图
    Graph g(6);

    // 添加测试边
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 8);
    g.addEdge(2, 4, 10);
    g.addEdge(3, 4, 2);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 3);

    cout << "Testing BFS and DFS:\n";
    g.BFS(0);
    g.DFS(0);

    cout << "\nTesting Dijkstra's shortest path:\n";
    g.dijkstra(0);

    cout << "\nTesting Prim's MST:\n";
    g.primMST();

    return 0;
}
