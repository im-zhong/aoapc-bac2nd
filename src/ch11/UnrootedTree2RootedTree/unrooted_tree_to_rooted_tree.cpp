// 2025/3/28
// zhangzhong
// 无根树转有根树
// 输入：1. 一个有n个结点的无根树的各条边，每个边就是两个节点
//      2. 一个根结点
// 输出：一颗有根树。就是一个parent数组，其中的每个节点都对应一个父节点。

#include <iostream>
#include <queue>
#include <vector>

using node_t = int;

// 图的边分两种，一种是有向的，一种是无向的
// 这样定义的边显然是有向的
// https://oi-wiki.org/graph/concept/
// 注意术语
struct DirectedEdge {
    node_t head;
    node_t tail;
};

struct UndirectedEdge {
    node_t node1 = -1;
    node_t node2 = -1;
};

class UnrootedTree {

  public:
    UnrootedTree(const size_t node_count)
        : _node_count(node_count), _edges(node_count) {}

    void AddEdge(UndirectedEdge edge) {
        this->_edges.push_back(std::move(edge));
    }

    std::vector<node_t> ToRootedTree(node_t root) const {

        // 根据我的理解，应该bfs和dfs都是可以的
        // 先实现dfs的吧
        std::vector<node_t> rooted_tree(this->_node_count);
        rooted_tree[root] = -1;
        this->dfs(root, -1, rooted_tree);
        return rooted_tree;
    }

    std::vector<node_t> ToRootedTreeBFS(node_t root) const {
        return this->bfs(root);
    }

    void ToGraph() { this->_graph = this->_EdgesToGraph(this->_edges); }

    size_t GetNodeCount() const noexcept { return this->_node_count; }

  private:
    void dfs(const int current_node, const int parent,
             std::vector<node_t>& rooted_tree) const {

        // 我们需要根据_edges将边转换成一个无向图
        // 使用邻接表存储
        for (const node_t adjacent_node : this->_graph[current_node]) {
            if (adjacent_node == parent) {
                continue;
            }
            rooted_tree[adjacent_node] = current_node;
            dfs(adjacent_node, current_node, rooted_tree);
        }
    }

    // 用bfs实现一下
    // bfs不需要递归 但是需要用到队列
    std::vector<node_t> bfs(node_t root) const {
        std::vector<node_t> rooted_tree(this->_node_count, -2);
        std::vector<bool> visited(this->_node_count, false);
        rooted_tree[root] = -1;
        visited[root] = true;

        std::queue<node_t> queue{};
        queue.push(root);

        while (!queue.empty()) {
            node_t current_node = queue.front();
            queue.pop();

            // 找到当前结点的邻接结点
            for (const node_t adjacent_node : this->_graph[current_node]) {
                // 如果某个节点已经被设置了parent 那么就跳过
                if (rooted_tree[adjacent_node] == -2) {
                    rooted_tree[adjacent_node] = current_node;
                }

                if (!visited[adjacent_node]) {
                    queue.push(adjacent_node);
                }
            }
            visited[current_node] = true;
        }

        return rooted_tree;
    }

    std::vector<std::vector<node_t>>
    _EdgesToGraph(std::vector<UndirectedEdge> edges) const {
        std::vector<std::vector<node_t>> graph{this->_node_count};
        for (const UndirectedEdge edge : this->_edges) {
            graph[edge.node1].push_back(edge.node2);
            graph[edge.node2].push_back(edge.node1);
        }
        return graph;
    }

  private:
    size_t _node_count;
    std::vector<UndirectedEdge> _edges;
    std::vector<std::vector<node_t>> _graph;
};

int main(int argc, char* argv[]) {

    // 我们自己设置一种测试案例吧
    // 输入就是
    // n
    // root表示这个图有几个节点，因为是无根树，所以一定有n-1条边，root表示一个父节点
    // 1 2 每行表示一条边
    // 0 0 表示测试结束
    // 输出
    // 从头开始，输出一行，每行按顺序写出它的父节点是谁。

    size_t node_count = 0;
    int root = 0;

    while (std::cin >> node_count >> root) {
        if (node_count == 0 && root == 0) {
            break;
        }

        UnrootedTree unrooted_tree{node_count};

        for (size_t i = 0; i < node_count - 1; i++) {
            UndirectedEdge edge{};
            std::cin >> edge.node1 >> edge.node2;

            unrooted_tree.AddEdge(edge);
        }

        unrooted_tree.ToGraph();

        // std::vector<node_t> rooted_tree = unrooted_tree.ToRootedTree(root);
        std::vector<node_t> rooted_tree = unrooted_tree.ToRootedTreeBFS(root);
        for (const node_t node : rooted_tree) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
    }
}