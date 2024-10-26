// 2024/10/25
// zhangzhong

#include <iostream>
#include <string>

static const int char_count = 26;

class Graph {
  public:
    Graph() { this->Init(); }

    void AddEdge(int from, int to) {
        // 因为是无向图
        // 所以需要添加两条边
        this->graph_[from][to] = 1;
        this->graph_[to][from] = 1;

        // 同时添加节点
        this->nodes_[from] = true;
        this->nodes_[to] = true;
    }

    void Print() {
        std::cout << "Nodes:\n";
        for (int i = 0; i < char_count; i++) {
            if (this->nodes_[i]) {
                std::cout << (char)('A' + i) << ", ";
            }
        }
        std::cout << std::endl;

        for (int r = 0; r < char_count; r++) {
            for (int c = 0; c < char_count; c++) {
                if (this->graph_[r][c] == 1) {
                    std::cout << (char)(r + 'A') << " -> " << (char)(c + 'A')
                              << "\n";
                }
            }
        }
    }

    void CalculateNodeCount() {
        this->node_count_ = 0;
        for (int i = 0; i < char_count; i++) {
            if (this->nodes_[i]) {
                this->node_count_ += 1;
            }
        }
    }

    // int CalculateBandWidth(int* A, int len) {
    //     int bandwidth = 0;
    //     for (int i = 0; i < len; i++) {
    //         int node = A[i];

    //         // find the largets path
    //         for (int c = 0; c < char_count; c++) {
    //             if (this->graph_[node][c] == 1) {
    //                 // there is an edge of node -> c

    //                 // 我们要找到c在A中的位置，
    //             }
    //         }
    //     }
    // }

    void Solve() {
        this->CalculateNodeCount();

        this->Permutation(this->A, 0, 0);
    }

    // 我们有一个重要的观察
    // 注意到一个排列的带宽由其最大的距离决定
    // 所以我们不需要重复计算某一个排列的带宽，只需要在加入一个新的节点的时候
    // 判断这个节点会不会让当前排列的带宽变大即可
    void Permutation(int* A, const int cur, const int cur_bandwidth) {

        // 枚举所有节点组成的全排列，
        // 我们的元素都是不重复的
        // 使用一个visited数组来来保存已经访问过的节点
        if (cur == this->node_count_) {
            // 计算当前序列的带宽
            if (cur_bandwidth < min_bandwidth_) {
                // 更新min bandwidth
                this->min_bandwidth_ = cur_bandwidth;
                // 记录当前的答案
                for (int i = 0; i < cur; i++) {
                    this->answer[i] = A[i];
                }
            }
        } else {

            // 遍历所有的节点
            for (int i = 0; i < char_count; i++) {
                if (!this->nodes_[i]) {
                    continue;
                }

                if (this->visited_[i]) {
                    continue;
                }

                // 如果我们接下来要放置i节点
                // 那么计算一下新的bandwidth
                // 当cur = 0 时，下面的循环不会执行
                // 且初始bandwidth时零 所以是对的
                // 当cur != 0
                // 下面的循环就是执行
                // new bandwidth不会减小
                int node = i;
                int new_bandwidth = cur_bandwidth;
                for (int j = 0; j < cur; j++) {
                    // 遍历当前序列
                    // 查看边 A[j] -> node 是否存在
                    if (this->graph_[A[j]][node] == 1) {
                        // 如果边存在，则bandwidth是
                        int bandwidth = cur - j;
                        if (bandwidth > new_bandwidth) {
                            new_bandwidth = bandwidth;
                        }
                    }
                }

                // 如果new_bandwidth 比我们的 min_bandwidth要小 才会允许继续递归
                if (new_bandwidth < this->min_bandwidth_) {
                    this->visited_[i] = true;
                    A[cur] = i;
                    Permutation(A, cur + 1, new_bandwidth);
                    this->visited_[i] = false;
                }
            }
        }
    }

    void PrintAnswer() {
        for (int i = 0; i < this->node_count_; i++) {
            std::cout << (char)(this->answer[i] + 'A') << " ";
        }
        std::cout << "-> " << this->min_bandwidth_ << "\n";
    }

  private:
    void Init() {
        // 初始化节点
        for (int i = 0; i < char_count; i++) {
            nodes_[i] = false;
            visited_[i] = false;
        }

        // 初始化边
        for (int r = 0; r < char_count; r++) {
            for (int c = 0; c < char_count; c++) {
                this->graph_[r][c] = 0;
            }
        }
    }

    int A[16] = {};
    int answer[16] = {};
    int node_count_ = 0;
    int min_bandwidth_ = 999999;
    bool nodes_[char_count] = {};
    bool visited_[char_count] = {};
    bool graph_[char_count][char_count] = {};
};

int main() {
    std::string line;

    while (std::cin >> line) {
        if (line == "#") {
            break;
        }

        auto graph = Graph{};
        char from = '\0';
        char to = '\0';
        bool is_from = true;
        for (const char ch : line) {
            if (ch == ':') {
                is_from = false;
            } else if (ch == ';') {
                is_from = true;
            } else {
                if (is_from) {
                    from = ch;
                } else {
                    to = ch;
                    graph.AddEdge(from - 'A', to - 'A');
                }
            }
        }

        // graph.Print();

        graph.Solve();
        graph.PrintAnswer();
    }
}