#include <iostream>
#include <cstring>
using namespace std;

class Graph {
private:
    struct ArcNode {
        int adj_vex;            // 该弧的终点
        ArcNode* next_arc;      // 后继弧
    };

    struct VNode {
        int in_degree = 0;     // 顶点的入度
        ArcNode* first_arc = nullptr;  // 顶点的弧链表
    };

    VNode* vertices;         // 存储图的顶点
    int vex_num, arc_num;      // 顶点数和边数

public:
    // 构造函数
    Graph(int vex_num, int arc_num) {
        this->vex_num = vex_num;
        this->arc_num = arc_num;
        vertices = new VNode[vex_num + 1];  // 顶点从1开始
    }

    // 析构函数
    ~Graph() {
        delete[] vertices;
    }

    // 添加弧到图中
    void add_arc(int src, int dst) {
        ArcNode* q = new ArcNode;
        q->adj_vex = dst;
        q->next_arc = vertices[src].first_arc;
        vertices[src].first_arc = q;
        vertices[dst].in_degree++;  // 目标顶点入度加1
    }

    // 拓扑排序
    bool topo_sort(int* arr) {
        int count = 0;
        while (true) {
            int cur = -1;
            for (cur = 1; cur <= vex_num; cur++) {
                if (vertices[cur].in_degree == 0)
                    break;  // 找到入度为0的点
            }
            if (cur > vex_num)
                break;  // 没有入度为0的点了

            count++;
            arr[cur] = count;  // 记录拓扑排序顺序
            vertices[cur].in_degree = -1;  // 置为已访问
            for (ArcNode* p = vertices[cur].first_arc; p; p = p->next_arc)
                vertices[p->adj_vex].in_degree--;  // 更新相邻节点的入度
        }

        return count == vex_num;  // 如果排序数量等于顶点数，说明拓扑排序成功
    }

    // 获取顶点数
    int get_vex_num() {
        return vex_num;
    }
};

void build(int k, int* row, int* col) {
    int map[405][405] = {0};  // 初始化矩阵

    for (int i = 1; i <= k; i++) {
        map[row[i]][col[i]] = i;  // 根据拓扑排序填充矩阵
    }

    // 输出结果矩阵
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= k; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int k, n, m;
    cin >> k >> n >> m;

    Graph rowGraph(k, n);
    Graph colGraph(k, m);

    int* row = new int[k + 1];
    int* col = new int[k + 1];

    int src, dst;

    // 读取行条件并构建行图
    for (int i = 0; i < n; i++) {
        cin >> src >> dst;
        rowGraph.add_arc(src, dst);
    }

    // 对行图进行拓扑排序
    if (!rowGraph.topo_sort(row)) {
        cout << "-1" << endl;
        delete[] row;
        delete[] col;
        return 0;
    }

    // 读取列条件并构建列图
    for (int i = 0; i < m; i++) {
        cin >> src >> dst;
        colGraph.add_arc(src, dst);
    }

    // 对列图进行拓扑排序
    if (!colGraph.topo_sort(col)) {
        cout << "-1" << endl;
        delete[] row;
        delete[] col;
        return 0;
    }

    // 构建并输出结果矩阵
    build(k, row, col);

    // 清理动态分配的内存
    delete[] row;
    delete[] col;

    return 0;
}
