// 2024/12/1
// zhangzhong

#include <vector>
using namespace std;

// 树的最长路径 最远点对 直径
// 说的都是一个东西

// 我们假设这颗树以边集的形式给出

// 这道题目有两种解法
// 1. DP 不用换根 仅需一次DFS
// 2. 不用DP 两次DFS 换根

constexpr int max_node = 128;

// 现在问题来了，我怎么从边集中构建出一颗树来呢？

void CalculateMaxPath(int* dis, int* path, bool* visited, int root, const int n,
                      vector<vector<int>>& edges) {

    // 在dfs中，对每个节点的访问只会发生一次
    // 我们随便假设一个节点作为跟节点 root = 0
    //

    visited[root] = true;
    path[root] = 0;

    // 访问所有孩子节点, 最简单的方式就是遍历所有的边

    int max1 = 0;
    int max2 = 0;

    // 不行 编程实在太复杂

    for (const vector<int>& edge : edges) {
        edge[0], edge[1];
        if (edge[0] == root && !visited[edge[1]]) {
            CalculateMaxPath(dis, path, visited, edge[1], n, edges);
            if (path[edge[1]] > path[root]) {
                path[root] = path[edge[1]];
                // update max1 and max2
                // always hold max1 > max2
                if (path[root] > max1) {
                    max2 = max1;
                    max1 = path[root];
                } else if (path[root] > max2) {
                    max2 = path[root];
                }
            }

            // update date max
            // if ()
        }

        if (edge[1] == root && !visited[edge[0]]) {
            CalculateMaxPath(dis, path, visited, edge[0], n, edges);
            if (path[edge[0]] > path[root]) {
                path[root] = path[edge[0]];
                if (path[root] > max1) {
                    max2 = max1;
                    max1 = path[root];
                } else if (path[root] > max2) {
                    max2 = path[root];
                }
            }
        }
    }

    // add self
    path[root] += 1;

    // 维护前两个最大值
    // case 1: 只有一个节点 叶子节点
    if (max1 == max2 && max1 == 0) {
        dis[root] = 0;
    }

    // case 2: 只有一颗子树
    else if (max2 == 0) {
        dis[root] = path[root];
    } else {
        // max1 > 0, max2 > 0
        dis[root] = max1 + max2 + 2;
    }

    // 然后我们的所有子节点都访问过了
    // path[root] = 1 + max path[child]
    // 这个过程可以在上面的递归结束之后就进行计算
    // 这样我们就不用保存child节点了
}

int GetDiameter1(int n, vector<vector<int>>& edges) {

    // n表示节点数量
    // 节点编号从 0 1 2 。。。 n-1

    int path[max_node] = {};
    bool visited[max_node] = {};

    // 所以这个题目和树的重心做法类似
    // 我们还需要一个数组用来以i为根且过i的最远点对
    int dis[max_node] = {};

    CalculateMaxPath(dis, path, visited, 0, n, edges);

    // 现在我们算出了以0为根节点的最长路径
    // 我们找到所有0的子树
    // 不对！！！！
    // 最长的路径不一定过0啊
    // 所以在递归的过程中，对于每个节点i
    // 每一颗子树都需要考虑
    // 每棵以i为根的树的所有子树中，path最长的前两个（不够两个则认为其中的一个是零）
    // 不行 得根据情况分析
    // 没有子树 0
    // 一个子树 path[i]
    // 两个以上 path[max] + path[max2] + 2

    // 最终算完了之后，返回dis的最大元素即可
    // return std::max_element(dis);
    return 0;
}

// 2. 两次DFS 换根
// 我们可以实现一个以任意节点为根的dfs函数
// 然后这个函数会返回其余的所有节点距离根的距离
// 假设最远的是v
// 再用v作为跟节点重新调用一次函数即可

void CalculateMaxDis(int* dis, int height, bool* visited, int root, const int n,
                     vector<vector<int>>& edges) {

    dis[root] = height;
    visited[root] = true;

    // 遍历所有子节点
    for (const vector<int>& edge : edges) {
        int node = -1;
        if (!visited[edge[1]] && edge[0] == root) {
            node = edge[1];
        }
        if (!visited[edge[0]] && edge[1] == root) {
            node = edge[0];
        }
        if (node == -1) {
            continue;
        }

        // node is the next node that we need to visit
        CalculateMaxDis(dis, height + 1, visited, node, n, edges);
    }
}

int GetDiameter2(int n, vector<vector<int>>& edges) {

    int dis[max_node] = {};
    bool visited[max_node] = {};

    CalculateMaxDis(dis, 0, visited, 0, n, edges);

    // 找到距离0节点最远的点
    int v = 0;
    for (int i = 1; i < n; i++) {
        if (dis[i] > dis[v]) {
            v = i;
        }
    }

    // 重置visited 和 dis
    // 以v为根节点重新计算
    CalculateMaxDis(dis, 0, visited, v, n, edges);
    // 找到距离v最远的就是直径
    // return std::max_element(dis)
    return 0;
}