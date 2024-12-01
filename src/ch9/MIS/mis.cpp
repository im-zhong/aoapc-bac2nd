// 2024/12/1
// zhangzhong

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// 树的最大独立集
// n个节点，n条边
// 任选一些节点，是的任何两个节点均不相邻
// 节点数量最多的成为 最大独立集 Maximun Independent Set MIS

// 任选一个节点作为根节点
// 从这个节点开始做后序遍历
// 遍历的顺序就是计算顺序
// dp[i] 表示 以i为根节点的树的 最大独立集
// 因为任何节点都有两种选择 选择 或者不选 所以dp数组虽然是一维的 但是有两个
// init select_dp[i] = 1. unselect_dp[i] = 0
// solution max{select_dp[r], unselect_dp[r]}

// 对于书上给出的问题，其中一个困难的地方在于如何从输入的n-1条无向边中构建一颗树
// 假设有n个节点 1 ..= n
// 给出n-1 条边 每条边都是用 n1 n2 这样的对给出
// 我们怎么在O(n)的时间内构建出一颗树？
// 或者说 我们怎么不构建这棵树 但是可以进行dfs?

struct Edge {
    int n1;
    int n2;
};

constexpr int max_node = 16;

// 有一个简单的方法 可以使用邻接矩阵 或者 邻接链表
// 只需要遍历一遍边 就可以构建 邻接矩阵 或者 邻接链表
void ConstructGraph(Edge* edges, int n) {
    int graph[max_node][max_node] = {};

    for (int i = 0; i < n; i++) {
        // n1 <-> n2
        int n1 = edges[i].n1;
        int n2 = edges[i].n2;

        graph[n1][n2] = 1;
        graph[n2][n1] = 1;
    }

    // 然后我们在这个图上通过dfs进行遍历即可
    // 别忘了使用一个visited数组来防止重复遍历
}

// 现在我们假设我们已经构建好了一颗二叉树
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
};

void dfs(TreeNode* root, std::unordered_map<TreeNode*, int>& sdp,
         std::unordered_map<TreeNode*, int>& udp) {

    if (root == nullptr) {
        return;
    }

    dfs(root->left, sdp, udp);
    dfs(root->right, sdp, udp);

    // 两种状态都有默认值
    // 无权 相当于权是1
    // sdp[root] = 1;
    // udp[root] = 0;

    // 有权
    sdp[root] = root->val;
    udp[root] = 0;

    // 还有一点需要注意的是 ，sdp和udp是一个整体
    // 整个dp还是一个一维的dp
    // 我们每次想要像其他dp题目那样 获取 dp[i]时， 实际上时去获取 max{sdp[i],
    // udp[i]} 本质上还是一个一维的dp

    // 我们此时可能在处理叶子节点
    // case 1: 不选本节点 udp
    // udp[root] = sum of son's max{sdp, udp}
    // we have son is left and right
    if (root->left) {
        udp[root] += std::max(sdp[root->left], udp[root->left]);
    }
    if (root->right) {
        udp[root] += std::max(sdp[root->right], udp[root->right]);
    }

    // case 2: 选择本节点
    // sdp[root] = 1 + sum of gradson's max{sdp, udp}
    if (root->left) {
        if (root->left->left) {
            sdp[root] += std::max(sdp[root->left->left], udp[root->left->left]);
        }
        if (root->left->right) {
            sdp[root] +=
                std::max(sdp[root->left->right], udp[root->left->right]);
        }
    }
    if (root->right) {
        if (root->right->left) {
            sdp[root] +=
                std::max(sdp[root->right->left], udp[root->right->left]);
        }
        if (root->right->right) {
            sdp[root] +=
                std::max(sdp[root->right->right], udp[root->right->right]);
        }
    }
}

int MIS(TreeNode* root) {

    // 我们使用两个一维dp数组
    // 分别表示以i为根是，选择该节点和不选择该节点

    // 可以使用true和false进行标记
    // int dp[2][max_node] = {};

    // 直接用TreeNode*给出的话 我们没法保存dp呀
    // 这是个数组 没有索引
    // 那么只剩下指针了
    // 我们可以通过hashmap保存节点的直接的方式来保存状态

    std::unordered_map<TreeNode*, int> select_dp;
    std::unordered_map<TreeNode*, int> unselect_dp;

    dfs(root, select_dp, unselect_dp);

    // 我们在计算完成之后，root上面应该保存着最大的答案

    return std::max(select_dp[root], unselect_dp[root]);
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
  public:
    void dfs(TreeNode* root, std::unordered_map<TreeNode*, int>& sdp,
             std::unordered_map<TreeNode*, int>& udp) {

        if (root == nullptr) {
            return;
        }

        dfs(root->left, sdp, udp);
        dfs(root->right, sdp, udp);

        // 两种状态都有默认值
        // 无权 相当于权是1
        // sdp[root] = 1;
        // udp[root] = 0;

        // // 有权
        // sdp[root] = root->val;
        // udp[root] = 0;

        // 还有一点需要注意的是 ，sdp和udp是一个整体
        // 整个dp还是一个一维的dp
        // 我们每次想要像其他dp题目那样 获取 dp[i]时， 实际上时去获取
        // max{sdp[i], udp[i]} 本质上还是一个一维的dp

        // 我们此时可能在处理叶子节点
        // case 1: 不选本节点 udp
        // udp[root] = sum of son's max{sdp, udp}
        // we have son is left and right
        // if (root->left) {
        //     udp[root] += std::max(sdp[root->left], udp[root->left]);
        // }
        // if (root->right) {
        //     udp[root] += std::max(sdp[root->right], udp[root->right]);
        // }

        // case 2: 选择本节点
        // sdp[root] = 1 + sum of gradson's max{sdp, udp}
        // if (root->left) {
        //     if (root->left->left) {
        //         sdp[root] += std::max(sdp[root->left->left],
        //         udp[root->left->left]);
        //     }
        //     if (root->left->right) {
        //         sdp[root] +=
        //             std::max(sdp[root->left->right], udp[root->left->right]);
        //     }
        // }
        // if (root->right) {
        //     if (root->right->left) {
        //         sdp[root] +=
        //             std::max(sdp[root->right->left], udp[root->right->left]);
        //     }
        //     if (root->right->right) {
        //         sdp[root] +=
        //             std::max(sdp[root->right->right],
        //             udp[root->right->right]);
        //     }
        // }

        // 可以对我的这个实现做一个改进
        // 因为我们经常访问 dp[nullptr]
        // 如果我们让 dp[nullptr] = 0 就可以不用做这么多if判断了
        // 同时优化一下逻辑
        // udp[root] = max{udp(l), sdp[l]} + max{udp[r], sdp[r]}
        // sdp[root] = w[root] + udp[l] + udp[r]

        // 同时我们不需要显示的设置 udp[nullptr] 和 sdp[nullptr]
        // 因为他们的默认值就是零
        sdp[root] = root->val + udp[root->left] + udp[root->right];
        udp[root] = max(udp[root->left], sdp[root->left]) +
                    max(udp[root->right], sdp[root->right]);
    }
    int rob(TreeNode* root) {
        // 我们使用两个一维dp数组
        // 分别表示以i为根是，选择该节点和不选择该节点

        // 可以使用true和false进行标记
        // int dp[2][max_node] = {};

        // 直接用TreeNode*给出的话 我们没法保存dp呀
        // 这是个数组 没有索引
        // 那么只剩下指针了
        // 我们可以通过hashmap保存节点的直接的方式来保存状态

        std::unordered_map<TreeNode*, int> select_dp;
        std::unordered_map<TreeNode*, int> unselect_dp;

        dfs(root, select_dp, unselect_dp);

        // 我们在计算完成之后，root上面应该保存着最大的答案

        return std::max(select_dp[root], unselect_dp[root]);
    }
};

int main() {}