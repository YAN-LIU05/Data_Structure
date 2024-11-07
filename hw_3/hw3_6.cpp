#include <iostream>
#include <string>

using namespace std;

// 定义二叉树类
class BinaryTree {
public:
    // 构造函数，接受前序和中序遍历字符串
    BinaryTree(const string& preorder, const string& inorder) {
    this->preorder = preorder; // 将输入的前序字符串赋值给成员变量
    this->inorder = inorder;   // 将输入的中序字符串赋值给成员变量
}
    // 获取后序遍历结果
    string getPostorder();

private:
    string preorder;  // 存储前序遍历字符串
    string inorder;   // 存储中序遍历字符串

    // 递归计算后序遍历
    string postorder(const string& preorder, const string& inorder);
};


// 获取后序遍历的公共接口
string BinaryTree::getPostorder() {
    return postorder(preorder, inorder);
}

// 实现后序遍历的递归函数
string BinaryTree::postorder(const string& preorder, const string& inorder) {
    // 基本情况：如果前序或中序字符串为空，返回空字符串
    if (preorder.empty() || inorder.empty()) {
        return "";
    }

    // 检查前序和中序的长度是否相等
    if (preorder.length() != inorder.length()) {
        return "Error"; // 长度不相等，返回错误信息
    }

    // 前序的第一个字符是根节点
    char root = preorder[0];
    // 在中序遍历中找到根节点的位置
    size_t root_index = inorder.find(root);

    // 如果根节点不在中序字符串中，返回错误
    if (root_index == string::npos) {
        return "Error";
    }

    // 递归分割中序和前序字符串，构造左右子树
    string left_inorder = inorder.substr(0, root_index); // 左子树的中序
    string right_inorder = inorder.substr(root_index + 1); // 右子树的中序

    // 计算前序遍历的左右子树
    string left_preorder = preorder.substr(1, left_inorder.length()); // 左子树的前序
    string right_preorder = preorder.substr(1 + left_inorder.length()); // 右子树的前序

    // 递归调用以获取左右子树的后序遍历
    string left_postorder = postorder(left_preorder, left_inorder);
    string right_postorder = postorder(right_preorder, right_inorder);

    // 检查左右子树的后序遍历是否出错
    if (left_postorder == "Error" || right_postorder == "Error") {
        return "Error"; // 返回错误信息
    }

    // 返回左右子树的后序遍历加上根节点，形成完整的后序遍历
    return left_postorder + right_postorder + root;
}

int main() {
    string line;
    // 持续读取输入，直到输入结束
    while (getline(cin, line)) {
        // 查找空格位置，将前序和中序遍历分开
        size_t space_pos = line.find(' ');
        string preorder = line.substr(0, space_pos); // 获取前序遍历
        string inorder = line.substr(space_pos + 1); // 获取中序遍历

        // 创建 BinaryTree 对象
        BinaryTree tree(preorder, inorder);
        // 获取后序遍历结果
        string result = tree.getPostorder();

        // 输出后序遍历结果
        cout << result << endl;
    }
    return 0; // 返回 0 表示程序正常结束
}
