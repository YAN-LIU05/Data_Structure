#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 105;    // 最大村庄数
const int MAXE = MAXN * MAXN; // 最大边数

// 边的类
class Edge {
public:
    int u, v, weight;
    Edge() {
        u = 0;
        v = 0;
        weight = 0;
    }

    // 带参数构造函数
    Edge(int u, int v, int weight) {
        this->u = u;
        this->v = v;
        this->weight = weight;
    }
};

// 图的类
class Graph {
private:
    Edge edges[MAXE]; // 存储所有边
    int edgeCount;    // 边的总数
    int parent[MAXN]; // 并查集父节点
    int rank[MAXN];   // 并查集秩

public:
    Graph() {
        edgeCount = 0;
    }
    void addEdge(int u, int v, int weight);
    void initUnionFind(int n);
    int find(int x);
    bool unionSets(int x, int y);
    void sortEdges();
    int kruskal(int n);
};


// --- Graph 类外实现 ---

void Graph::addEdge(int u, int v, int weight) {
    edges[edgeCount++] = Edge(u, v, weight);
}

void Graph::initUnionFind(int n) {
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int Graph::find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]); // 路径压缩
    }
    return parent[x];
}

bool Graph::unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        return true;
    }
    return false;
}

void Graph::sortEdges() {
    for (int i = 0; i < edgeCount - 1; ++i) {
        for (int j = 0; j < edgeCount - i - 1; ++j) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

int Graph::kruskal(int n) {
    sortEdges();          // 对边按权重排序
    int totalCost = 0;

    for (int i = 0; i < edgeCount; ++i) {
        if (unionSets(edges[i].u, edges[i].v)) {
            totalCost += edges[i].weight;
        }
    }

    return totalCost;
}

// --- 主函数 ---
int main() {
    int n;
    cin >> n;

    int distances[MAXN][MAXN];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> distances[i][j];
        }
    }

    int m;
    cin >> m;

    Graph graph;
    graph.initUnionFind(n); // 初始化并查集

    // 添加所有边到图
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            graph.addEdge(i, j, distances[i][j]);
        }
    }

    // 处理已有的边
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        graph.unionSets(a - 1, b - 1); // 直接合并已有的路
    }

    // 输出最小生成树的总权值
    cout << graph.kruskal(n) << endl;

    return 0;
}
