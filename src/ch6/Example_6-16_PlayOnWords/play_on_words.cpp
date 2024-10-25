// 2024/10/25
// zhangzhong

#include <iostream>

static const int char_count = 26;

// [[BUG]]
// 有一些特殊的情况要处理
// 我发现自己构造一些边界情况作为自测的是非常重要的
// 以后尽可能的自己多构造一些测试用例，专门测试极端的边界情况
class Graph {

  public:
    Graph() {
        for (int r = 0; r < char_count; r++) {
            for (int c = 0; c < char_count; c++) {
                this->graph_[r][c] = 0;
            }
        }
        for (int i = 0; i < char_count; i++) {
            this->nodes_[i] = false;
            this->visited_[i] = false;
            this->in_degree_[i] = 0;
            this->out_degree_[i] = 0;
        }

        this->edge_count_ = 0;
    }

    // 我们的图非常简单，0 - 25 代表 a - z
    // 当然是输入的时候进行处理
    // [[TIPS]]
    // 遇到一些不知道如何处理的情况时，考虑极端（最简单，最特殊）的情况可能是有益的
    // 不过我有一个问题，就是重复的边对图的性质是否会产生影响？
    // 考虑一个最极端的情况
    // 只有两个单词 ab -> bc
    // 这种情况下，我们是有解的
    // 但是，如果再加上一条边 ab, ab, bc
    // 那么此时我们找不到一个合适的解
    // 所以重复的边也必须被考虑进去！
    //
    // 但是这里的情况实际上是简单的，因为我们不需要求出具体的path
    // 我们只需要分析其degree即可
    // 所以我们用0表示节点ab之间没有边，用1表示有一条边，2表示有两条边。。。
    void AddEdge(int from, int to) {
        this->graph_[from][to] += 1;

        // add ndoes
        this->nodes_[from] = true;
        this->nodes_[to] = true;

        this->edge_count_ += 1;
    }

    bool HasEulerPath() {

        // 无论如何，如果我们只有一条边，那么一定是可以构造的
        // 没有这个条件也是可以通过测试的，只不过测试时间变长了一些
        // if (this->edge_count_ == 1) {
        //     return true;
        // }

        // first make sure that the graph is connected
        // make a copy of our graph and make it into a undirected graph
        // and make a dfs on a single node, to check if it can traverse all the
        // node if it can, then this graph is connected; otherwise, is not
        // int undirected_graph[char_count][char_count];
        // TODO: maybe good ways to initializaion?
        for (int r = 0; r < char_count; r++) {
            for (int c = 0; c < char_count; c++) {
                undirected_graph[r][c] = 0;
            }
        }

        for (int r = 0; r < char_count; r++) {
            for (int c = 0; c < char_count; c++) {
                // check if there a edge: r -> c
                if (this->graph_[r][c] > 0) {
                    undirected_graph[r][c] = undirected_graph[c][r] = 1;
                }
            }
        }

        // then make a dfs on this graph
        // but how?
        // we need to know which node this graph have
        // first find a exist node
        int node = 0;
        for (; !this->nodes_[node]; node++)
            ;

        // then visit this node
        Visit(node);

        // then check if all the node are visited
        bool connected = true;
        for (int i = 0; i < char_count; i++) {
            if (this->nodes_[i]) {
                connected = connected && this->visited_[i];
            }
        }

        if (!connected) {
            return false;
        }

        // then, if we are connected
        // we will statistics all the degree of the all the nodes
        // there must exactly be one start point, one end point, and all other
        // be the balance point

        for (int r = 0; r < char_count; r++) {
            for (int c = 0; c < char_count; c++) {
                // r -> c:
                // then in_degree[c]
                // out_degree[r]
                this->out_degree_[r] += this->graph_[r][c];
                this->in_degree_[c] += this->graph_[r][c];
            }
        }

        // 统计完度之后，检查是否符合上述条件
        // check start point
        bool has_start_point = false;
        int start_point = -1;
        bool has_end_point = false;
        int end_point = -1;
        // [[BUG]]
        // 这里的过滤条件不对
        // for + filter 这样写诗不对的，之前就写出来过这样的代码
        // 只能把for循环和filter分开写
        for (int n = 0; n < char_count; n++) {
            if (!this->nodes_[n]) {
                continue;
            }

            if (this->in_degree_[n] == this->out_degree_[n]) {
                // normal point, which is ok
            } else if (this->in_degree_[n] - this->out_degree_[n] == 1) {
                // end point
                if (has_end_point) {
                    // if we already has end point, then false
                    return false;
                }
                has_end_point = true;
                end_point = n;
            } else if (this->out_degree_[n] - this->in_degree_[n] == 1) {
                // start point
                if (has_start_point) {
                    return false;
                }
                has_start_point = true;
                start_point = n;
            } else {
                // other nodes , just reutrn false
                return false;
            }
        }

        // normal, then check if we have start point and end point
        // and there is another situation
        // when we both do not have start point and end point, which means all
        // of our node is balanced

        return (has_start_point && has_end_point) ||
               (!has_end_point && !has_end_point);
    }

  private:
    void Visit(int node) {

        // first make this node visited
        this->visited_[node] = true;

        // then check all the adj nodes
        for (int adj = 0; adj < char_count; adj++) {
            if (this->undirected_graph[node][adj] == 1 &&
                !this->visited_[adj]) {

                Visit(adj);
            }
        }
    }

  private:
    int undirected_graph[char_count][char_count];
    int graph_[char_count][char_count];
    bool nodes_[char_count];
    bool visited_[char_count];
    int in_degree_[char_count];
    int out_degree_[char_count];
    int edge_count_;
};

int main() {
    int test_case_count = 0;
    std::cin >> test_case_count;

    for (int t = 0; t < test_case_count; t++) {

        int word_count = 0;
        std::cin >> word_count;

        auto word = std::string{};
        auto graph = Graph{};
        for (int i = 0; i < word_count; i++) {
            std::cin >> word;

            // when read a new word
            // add an edge into the graph
            graph.AddEdge(word.front() - 'a', word.back() - 'a');
        }

        bool has_euler_path = graph.HasEulerPath();
        if (has_euler_path) {
            std::cout << "Ordering is possible.\n";
        } else {
            std::cout << "The door cannot be opened.\n";
        }
    }
}