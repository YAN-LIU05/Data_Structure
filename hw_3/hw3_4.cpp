#include <iostream>
using namespace std;

const int MAX_LENGTH = 2000000; // 假设输入字符串总长度小于2,000,000
char s[MAX_LENGTH]; // 用于存储输入字符串
int bdp = -1; // 记录变换后树的最大深度

// 定义一个结构体来表示树的节点
struct Tree {
    int depth; // 节点的深度（目前未使用，但可以扩展）
};

// 深度优先搜索函数
void dfs(int& i, int fatherdepth) {
    bdp = max(bdp, fatherdepth); // 更新最大深度
    int cnt = 0; // 记录当前节点的子节点数量

    while (s[i]) { // 遍历字符串直到结束
        if (s[i] == 'd') { // 如果遇到节点
            dfs(++i, fatherdepth + cnt + 1); // 递归调用，增加深度
            cnt++; // 子节点计数增加
        } else { // 遇到其他字符（叶子节点）
            ++i; // 移动到下一个字符
            return; // 结束当前递归
        }
    }
}

int main() {
    int cnt = 0; // 计数树的数量

    while (true) {
        int depth = 0;         // 当前树的深度
        int currentDepth = 0;  // 当前节点的深度

        cin >> s; // 读取输入字符串
        if (s[0] == '#') break; // 遇到 '#' 结束输入

        // 计算原始树的深度
        for (int i = 0; s[i]; i++) {
            if (s[i] == 'd') { // 遇到节点
                currentDepth++; // 深度增加
                depth = max(depth, currentDepth); // 更新最大深度
            } else { // 遇到其他字符
                currentDepth--; // 深度减少
            }
        }

        // 如果 currentDepth 变为负值，可能是输入不合法
        if (currentDepth < 0) {
            cout << "Invalid tree structure!" << endl; // 输出错误信息
            continue; // 跳过当前输入
        }

        // 计算转换后的树的深度
        int ptr = 0; // 指向字符串的指针
        dfs(ptr, 0); // 调用 DFS 计算深度
        cout << "Tree " << ++cnt << ": " << depth << " => " << bdp << endl; // 输出结果

        bdp = -1; // 重置最大深度
    }

    return 0; // 程序结束
}
