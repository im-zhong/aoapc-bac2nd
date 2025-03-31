// 2025/3/31
// zhangzhong

// In addition to yourself, your calling circle consists of all people whom you
// call and who call you, either directly or indirectly

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// 我们每读到一个名字，都要给他一个id
// 这次我们的id可以从零开始 好哎
// 写一个类来处理这个事情吧

// 我们这是一个有向图
// 但是我们使用矩阵来存储这个有向图

// 我还是不理解我哪里错了
// pdf上也没有指定输出顺序啊？

const int MAX_PEOPLE_COUNT = 32;

class Graph {
  public:
    Graph(int node_count) : _node_count(node_count), _graph(node_count) {}

    void AddEdge(int i, int j) {
        // 我们这是无向图
        // 所以要一次性添加两条边
        this->_graph[i].push_back(j);
        this->_graph[j].push_back(i);
    }

    std::vector<std::vector<int>> GetAllConnected() {

        // 创建一个visited数组
        std::vector<bool> visited(this->_node_count, false);
        std::vector<std::vector<int>> connects;
        for (int i = 0; i < this->_node_count; i++) {
            if (visited[i]) {
                continue;
            }
            // 开始一段dfs
            std::vector<int> connected;
            visited[i] = true;
            connected.push_back(i);
            dfs(i, visited, connected);
            // 给connected拍个序
            // std::sort(connected.begin(), connected.end());
            connects.push_back(std::move(connected));
        }
        return connects;
    }

    void dfs(int node, std::vector<bool>& visited,
             std::vector<int>& connected) {

        // 否则找到所有的邻接
        for (int adj : this->_graph[node]) {
            if (!visited[adj]) {
                visited[adj] = true;
                connected.push_back(adj);
                dfs(adj, visited, connected);
            }
        }
    }

  private:
    int _node_count;
    std::vector<std::vector<int>> _graph;
};

class CallingCircle {

  public:
    CallingCircle() : _people_count(0) {
        // TODO: 如果一个二维数组也可以像std::array那样，变成一个容器就好了
        // 初始化这张图啊，在最开始的时候 所有的图应该都是零
        for (int i = 0; i < MAX_PEOPLE_COUNT; i++) {
            for (int j = 0; j < MAX_PEOPLE_COUNT; j++) {
                this->_graph[i][j] = 0;
            }
        }
    }

    int GetPeopleCount() const noexcept { return this->_people_count; }

    int AddName(const std::string& name) {
        if (this->_names.find(name) == this->_names.end()) {
            int id = this->_people_count;
            ++this->_people_count;
            this->_names[name] = id;
            this->_name_vec.push_back(name);
            return id;
        } else {
            return this->_names.at(name);
        }
    }

    std::vector<std::vector<int>> GetAllCallingCircles() {

        // 在graph上floyd
        // 得到传递必报
        // 自己和自己计算会发生什么？不变 ok
        // 难道是这里的遍历顺序的问题？
        // !!!
        // 真的是，这里必须让k在最外面，否则最终计算出来的传递闭包就是错误的，为什么？
        for (int k = 0; k < this->_people_count; k++) {
            for (int i = 0; i < this->_people_count; i++) {
                for (int j = 0; j < this->_people_count; j++) {

                    // 这里我们用的是位运算 而不是逻辑运算
                    this->_graph[i][j] =
                        this->_graph[i][j] |
                        (this->_graph[i][k] & this->_graph[k][j]);
                }
            }
        }

        // 我知道了，自己给自己打虽然会在graph上floy上留下1
        // 但是在下面构造新的图的并不会考虑
        // 可以正确处理只是因为在求联通分量的时候，self edge并不会产生影响

        // 求完之后
        // 遍历整张图 构造一个新的图
        // 当且仅当两者互通是，添加一天边，这个新的图是一个无向图
        // 因为边肯定很少，所以应该采取邻接表存储

        // solution里面这是直接在graph上进行了dfs 没有再构造一张新的图
        // 其实也是可以的，就是需要遍历二维数组而已
        // 不过可能整体上会快一些

        Graph graph{this->_people_count};
        for (int i = 0; i < this->_people_count; i++) {
            // 哎，不对的，因为是对称的，所以只需要遍历上半矩阵就行了
            for (int j = i + 1; j < this->_people_count; j++) {
                if ((this->_graph[i][j] & this->_graph[j][i]) == 1) {
                    graph.AddEdge(i, j);
                }
            }
        }

        return graph.GetAllConnected();
    }

    void AddEdge(int head, int tail) { this->_graph[head][tail] = 1; }

    const std::vector<std::string>& GetNameVec() const noexcept {
        return this->_name_vec;
    }

  private:
    // 为了能从id映射回名字
    // 我们还需要在一个vector中保存所有的名字
    std::vector<std::string> _name_vec;
    int _graph[MAX_PEOPLE_COUNT][MAX_PEOPLE_COUNT];
    std::unordered_map<std::string, int> _names;
    int _people_count;
};

int main(int argc, char* argv[]) {
    // [0, 25]
    int people_count = 0;

    int phone_call_count = 0;

    for (int kase = 1; std::cin >> people_count >> phone_call_count; kase++) {
        if (people_count == 0 && phone_call_count == 0) {
            break;
        }

        if (kase != 1) {
            std::cout << std::endl;
        }

        if (phone_call_count == 0) {
        }

        CallingCircle cc{};
        // The remainder of the data set consists of mlines, each representing
        // a phone call
        // for example: Ben Dolly
        std::string name;

        for (int i = 0; i < phone_call_count; i++) {
            std::cin >> name;
            int head = cc.AddName(name);
            std::cin >> name;
            int tail = cc.AddName(name);
            cc.AddEdge(head, tail);
        }

        // assert(cc.GetPeopleCount() == people_count);

        // ok，现在数据读取完毕了
        // output
        // For each input set, print a header line with the data set number,
        // followed by a line for each calling
        // circle in that data set
        std::cout << "Calling circles for data set " << kase << ":\n";
        // 然后对于每个圈子，应该返回一个vector
        // 然后可能有多个圈子，所以返回了多个vector
        std::vector<std::vector<int>> ccs = cc.GetAllCallingCircles();
        const std::vector<std::string>& name_vec = cc.GetNameVec();
        for (const std::vector<int>& circle : ccs) {
            for (int i = 0; i < circle.size(); i++) {
                // std::cout << circle[i];
                std::cout << name_vec[circle[i]];
                if (i != circle.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }

        // 因为输出是没有顺序的 所以需要另外一种测试方法
        // 就是把out.txt的内容也给读进来，然后比较集合，这个就比较麻烦了，
        // 还是看看solution吧
        // 现在想测试 只能重新写一个测试的程序了，还是写一个吧
    }
}