// 2024/10/25
// zhangzhong

#include <iostream>
#include <vector>

class DirectedGraph {

  public:
    DirectedGraph(int node_count)
        : node_count_(node_count), graph_(nullptr), color_(nullptr) {
        // 为了简单起见，这里我们使用二维数组来存储图

        this->graph_ = new int[node_count * node_count];
        this->color_ = new int[node_count];

        // 好像还忘了初始化
        for (int i = 0; i < node_count * node_count; i++) {
            this->graph_[i] = -1;
        }
        for (int i = 0; i < node_count; i++) {
            this->color_[i] = white;
        }
    }

    ~DirectedGraph() {
        delete[] this->graph_;
        delete[] this->color_;
    }

    void AddEdge(int from, int to) {
        // 卧槽 这里写错了 忘了graph是一个二维数组了
        // [[BUG]] 这里的问题在于 在使用指针式，类型系统帮不上忙
        // 他无法帮我们检测正确的访问方式
        // 所以动态二维数组最好可以封装一下
        this->graph_[from * this->node_count_ + to] = 1;

        // 如果是无向图还要添加一条
        // this->graph_[to] = from;
    }

    std::vector<int> TopologicalSort() {

        // 本质上就是一个dfs而已
        auto path = std::vector<int>{};
        for (int i = 0; i < this->node_count_; i++) {
            // 这里错了，应该只访问白色de
            if (this->color_[i] == white) {
                this->Visit(i, path);
            }
        }
        return {path.rbegin(), path.rend()};
    }

    bool HasCircle() const { return this->has_circle_; }

  private:
    void Visit(int node, std::vector<int>& path) {

        // 通过这样设置其实非常容易出错
        // 因为dfs是一定会结束的
        // 不如使用一个全局变量来标识
        // bool has_circle = false;
        // set color to gray
        this->color_[node] = gray;

        // 访问所有的邻接节点
        for (int n = 0; n < this->node_count_; n++) {

            if (this->graph_[node * this->node_count_ + n] == -1) {
                continue;
            }

            // if adj is white, then visit it
            if (this->color_[n] == white) {
                Visit(n, path);
            } else if (this->color_[n] == gray) {
                // there is a circle in in this graph
                // there is noway have a topological sort
                this->has_circle_ = true;
            }
        }

        // set color to black
        this->color_[node] = black;
        // push this node in the path
        path.push_back(node);
        // return has_circle;
    }

  private:
    static const int white = 0;
    static const int gray = 1;
    static const int black = 2;

    int node_count_;
    // int edge_count_;
    int* graph_;
    int* color_;
    bool has_circle_ = false;
};

int main() {

    while (true) {
        int node_count = 0;
        int edge_count = 0;
        std::cin >> node_count >> edge_count;
        // [[BUG]] 可以没有边！
        // 确实题目中的描述是 n = m = 0才是停止条件
        // 这里我想当然了
        if (node_count == 0 && edge_count == 0) {
            break;
        }

        auto graph = DirectedGraph{node_count};
        // read all the edges and add it to the graph
        for (int i = 0; i < edge_count; i++) {
            int from = 0;
            int to = 0;

            // 我们给所有的节点ID-1
            // 然后在输出的时候在全部加1
            std::cin >> from >> to;
            graph.AddEdge(from - 1, to - 1);
        }

        auto order = graph.TopologicalSort();
        // 卧槽，好像题目中根本就没有提到环，可能输入的图都是DAG
        for (int i = 0; i < order.size(); i++) {
            if (i != 0) {
                std::cout << " ";
            }
            std::cout << order[i] + 1;
        }
        std::cout << std::endl;
    }
}