// 2024/12/1
// zhangzhong
// https://oi-wiki.org/graph/tree-centroid/
// https://www.cnblogs.com/zinthos/p/3899075.html

#include <iostream>

// 一个没有固定根结点的树称为 无根树（unrooted tree）

// 无根树有几种等价的形式化定义：

// 有 n 个结点，n-1 条边的连通无向图

// 无向无环的连通图

// 任意两个结点之间有且仅有一条简单路径的无向图

// 任何边均为桥的连通图

// 没有圈，且在任意不同两点间添加一条边之后所得图含唯一的一个圈的图

// 在无根树的基础上，指定一个结点称为 根，则形成一棵 有根树（rooted tree

// 无根树的重心（质心）
// 如果在树中选择某个节点并删除，这棵树将分为若干棵子树，统计子树节点数并记录最大值。取遍树上所有节点，使此最大值取到最小的节点被称为整个树的重心。

// 我们仍然假设算法的输入以图的形式给出
// 我们假设是一个使用邻接矩阵的无向图

constexpr int max_sons = 8;

struct TreeNode {

    // 保存每个节点的索引 仅仅是为了方便编程
    int index;
    int val;

    // 对于每一个节点，记录他的所有孩子
    // 这里为了代码演示方便，采用一个数组来保存
    TreeNode* sons[max_sons];
};

constexpr int max_node = 128;

void CalculateSizeOfTree(TreeNode* root, int* size, int n) {
    if (root == nullptr) {
        return;
    }

    // 左右根
    for (int i = 0; i < max_sons; i++) {
        CalculateSizeOfTree(root->sons[i], size, n);
    }

    // size[i]= sum of sons size[s] + 1(self)
    size[root->index] = 1;
    for (int i = 0; i < max_sons; i++) {
        size[root->index] += size[root->sons[i]->index];
    }
}

void CalculateWeight(TreeNode* root, int* size, int* weight, int n) {
    if (root == nullptr) {
        return;
    }

    // 后序遍历
    for (int i = 0; i < max_sons; i++) {
        CalculateWeight(root->sons[i], size, weight, n);
    }

    // 删掉节点i之后
    // 剩下的联通分量按照两部分进行考虑
    // i的下方子树 最大的联通分量节点个数 max{d[j]} j is son of i
    // i的上方子树 节点数量 n - d[i]
    // weight[i] = max{i的下方子树, i的上方子树}
    weight[root->index] = n - size[root->index];
    for (int i = 0; i < max_sons; i++) {
        weight[root->index] =
            std::max(weight[root->index], size[root->sons[i]->index]);
    }
}

// 图节点 0 1 ... n-1
int Centroid(TreeNode* root, int n) {

    int dp[max_node] = {};

    // 原来是状态定义的不对
    // 定义dp[i]表示以i为根的子树的节点个数
    // 我们第一次dfs-dp先把这个东西给求出来

    // 第二次dfs遍历全部的节点
    // 对于每个节点i
    // 下方子树的最大节点数量是 max{d(j)...} j is son of i
    // 上方子树 n - d(i)
    // 所以根据重心的定义，此时去掉节点i 剩下的联通分量中 最大的子图的节点树
    // max{max{d(j)...} j is son of i,  n - d(i)}
    // 然后我们要求他的最小值 min{max{max{d(j)...} j is son of i,  n - d(i)}}

    // 这两个dfs可以合并成一个 一块求出来

    // stage 1
    int size[max_node] = {};
    CalculateSizeOfTree(root, size, n);

    // stage 2
    // 使用一个数组来保存 weight[i]
    // 表示删去i之后，剩下的最大的联通分量的节点数量
    int weight[max_node] = {};
    CalculateWeight(root, size, weight, n);

    // 计算完成之后，我们只需要遍历一遍weight
    // 找到最小值即可
    // https://stackoverflow.com/questions/2953491/finding-the-position-of-the-maximum-element
    // distance(min_element(container)-begin)

    int index = 0;
    for (int i = 1; i < n; i++) {
        if (weight[i] < weight[index]) {
            index = i;
        }
    }
    return index;
}

int main() {}
