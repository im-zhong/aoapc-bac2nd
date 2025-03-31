// 2025/3/30
// zhangzhong

// TODO: 我们的算法实现应该是对的，但是实现的却是比较慢
// 应该是枚举的方式有问题，看看答案吧

// 跑了很久，答案出来是对的，就是太慢了，

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

struct City {
    int x;
    int y;
};

struct UndirectedEdge {
    int a;
    int b;
    int cost;

    bool operator==(const UndirectedEdge& rhs) const noexcept {
        return (this->a == rhs.a && this->b == rhs.b) ||
               (this->a == rhs.b && this->b == rhs.a);
    }
};

namespace std {
template <> struct hash<UndirectedEdge> {
    size_t operator()(const UndirectedEdge& self) const noexcept {
        return hash<int>{}(self.a) ^ hash<int>{}(self.b);
    }
};
} // namespace std

const int MAX_CITIES = 1024;

int city_graph[MAX_CITIES][MAX_CITIES] = {};

// 我们还需要一个disjointset

class DisjointSet {
  public:
    DisjointSet(size_t size) : _size(size), _sets(size) {

        // 如果只是简单的实现kruskal 应该不需要支持返回个数的功能吧
        // 那咱们就实现一个简单版本的就行了
        this->Reset();
    }

    int Find(int x) {
        if (this->_sets[x] == x) {
            return x;
        }
        this->_sets[x] = this->Find(this->_sets[x]);
        return this->_sets[x];
    }

    bool InSameSet(int x, int y) { return this->Find(x) == this->Find(y); }

    void Union(int x, int y) {
        int root_x = this->Find(x);
        int root_y = this->Find(y);
        if (root_x != root_y) {
            this->_sets[root_y] = root_x;
        }
    }

    void Reset() {
        for (int i = 0; i < this->_sets.size(); i++) {
            this->_sets[i] = i;
        }
    }

  private:
    size_t _size;
    std::vector<int> _sets;
};

struct SubNetwork {
    int cost;
    std::vector<int> cities;
};

class Solution {

  public:
    Solution(const std::vector<City>& cities) : _cities_count(cities.size()) {
        this->InitCityGraph(cities);
    }

    // 首先我们运行第一次SMT 不加任何套餐
    // 我们的目的是获得边

    std::vector<UndirectedEdge> GetMST() {

        // 是不是这个算法可以提前退出呢？
        // 咱们用profile看一下吧 咱们这次写到makefile里面

        std::vector<UndirectedEdge> edges;
        // 这样就是一个简单图，只有简单图才能用kruskal算法
        for (int i = 1; i <= this->_cities_count; i++) {
            // 只需要遍历上半矩阵就行了，不考虑parallel edge
            for (int j = i + 1; j <= this->_cities_count; j++) {
                // i == j 意味着什么？意味着self edge
                // 这样的边显然不应该考虑

                edges.push_back(UndirectedEdge{i, j, city_graph[i][j]});
            }
        }

        // 然后我们在这个图上面跑MST
        // 首先排序
        std::sort(edges.begin(), edges.end(),
                  [](const UndirectedEdge& lhs, const UndirectedEdge& rhs) {
                      return lhs.cost < rhs.cost;
                  });

        std::vector<UndirectedEdge> mst;
        DisjointSet disjoint_set{static_cast<size_t>(this->_cities_count + 1)};

        // 然后我们遍历所有的边就行了
        for (const UndirectedEdge& edge : edges) {
            // 看看edge的两个端点是不是在一个集合里面，如果不是，就放到一个集合中
            if (!disjoint_set.InSameSet(edge.a, edge.b)) {
                disjoint_set.Union(edge.a, edge.b);
                // 然后把当前的边加入到mst中
                mst.push_back(edge);
            }
        }

        return mst;
    }

    std::vector<std::vector<UndirectedEdge>>
    EnumerateSubNetworks(const std::vector<SubNetwork>& sub_networks) {
        std::vector<std::vector<UndirectedEdge>> enumerate_edges;
        for (const SubNetwork& sub_network : sub_networks) {

            enumerate_edges.push_back(
                this->GetAllEdgesFromSubNetwork(sub_network));
        }
        return enumerate_edges;
    }

    // 卧槽，我们还要再写一组mst，输入是边的数组
    // 因为接下来我们处理的就是稀疏图了，就用不着上面的数组了
    // 而且，我们会重新设置一些边的权重，所以必然要用新的边

    // 我们还需要方案，一种方案，方案的英文是什么
    // 不是，它叫做subnework
    int Enumerate(int q, const std::vector<SubNetwork>& sub_networks,
                  const std::vector<UndirectedEdge>& mst) {

        // calculate mst cost

        int mycost = 0;
        for (const UndirectedEdge& edge : mst) {
            mycost += edge.cost;
        }

        // 对于所有的边 我们只需要在最开始枚举一次
        std::vector<std::vector<UndirectedEdge>> subnetwork_edges =
            this->EnumerateSubNetworks(sub_networks);

        // 不对啊，这个min cost 就可以是mst的cost啊
        int min_cost = mycost;
        // 将mst的边放进去，初始化我们的边

        // 现在这个就不需要了
        // 对于任何一种新的方案，都需要重新设置边
        // 这样写有可能超时
        // std::unordered_map<UndirectedEdge, int> edges;
        // for (const UndirectedEdge& edge : mst) {
        //     edges[edge] = edge.cost;
        // }

        // 不选择任何方案的我们就不进行枚举了，我们从1开始，一直到 2^q
        // BUG: 这里少了个等号 没有遍历最后一个 全选的情况。。。
        for (int i = 1; i <= ((1 << q) - 1); i++) {
            // std::cout << "done case " << i << std::endl;
            // if (i == 10) {
            //     return min_cost;
            // }

            int sub_network_cost = 0;
            // 我们根据枚举出来的i，索引特定的subnetwork
            // 在这里发生截断, 因为q最大是8
            std::vector<int> picked_subnetworks;
            for (int j = 0; j < q; j++) {
                if (((i >> j) & 1) != 1) {
                    continue;
                }
                // 所有在subnetwork里面的city都应该看作是完全互联的
                // 这意味着我们要遍历这些互联的城市，然后把权重为零的边添加到边的集合中
                // 注意到，我们这里产生的边和mst的边可能是重复的
                // 所以我们需要一个hashmap
                // 且hashmap中要先添加mst的边，因为后序我们可能将这些边的权重更新为0

                const SubNetwork& sub_network = sub_networks[j];
                // const std::vector<UndirectedEdge> sub_edges =
                //     subnetwork_edges[j];
                // // 给定一个subnetwork 返回它涉及到的所有边
                // //
                // 我想到一个优化，对于这些边的枚举，我们可以提前完成，不需要每次都重新枚举
                // // 我又想到一个优化，就是我们不在这里加入这些边了
                // // 我们在下面根据j直接访问对应的边就行了
                // // 因为这些边的权重是零，根本不需要排序
                // //
                // 然后我们在访问原来的边的时候，这条边需不需要访问，只需要判断一下是否出现在集合中就行
                // // 而且这些判断也是可以预先计算出来的。
                // for (const UndirectedEdge& edge : sub_edges) {
                //     edges[edge] = edge.cost;
                // }
                picked_subnetworks.push_back(j);
                sub_network_cost += sub_network.cost;
            }

            // 果然，把上面的去掉之后，速度快了非常非常多

            // 这里还有一个优化，就是如果我们光自网络的花费就比现在最小的花费还要大的话，
            // 后面就没有任何必要继续做下去了
            if (sub_network_cost > min_cost) {
                continue;
            }

            // 现在方案对应的边也更新完毕
            // 我们需要根据现在的边，来计算出一个MST

            // std::vector<UndirectedEdge> graph_edges;
            // for (auto it = edges.begin(); it != edges.end(); it++) {
            //     graph_edges.push_back(
            //         UndirectedEdge{it->first.a, it->first.b, it->second});
            // }

            // 我们还得考虑subnetwork的cost
            // 那这样的话，咱们需要写一个特殊的mst，它遍历边的方式是先遍历subnetwokrs里面的边
            // 然后遍历mst里面的边
            int mst_cost =
                SparseMSTV2(picked_subnetworks, mst, subnetwork_edges);
            int cost = sub_network_cost + mst_cost;
            if (cost < min_cost) {
                min_cost = cost;
            }
        }

        return min_cost;
    }

    // 哦哦 这里需要对edges进行排序，所以edges不能是常量引用，只能是引用
    int SparseMST(std::vector<UndirectedEdge>& edges) const {

        std::sort(edges.begin(), edges.end(),
                  [](const UndirectedEdge& lhs, const UndirectedEdge& rhs) {
                      return lhs.cost < rhs.cost;
                  });

        std::vector<UndirectedEdge> mst;
        DisjointSet disjoint_set{static_cast<size_t>(this->_cities_count + 1)};

        // 然后我们遍历所有的边就行了
        for (const UndirectedEdge& edge : edges) {
            // 看看edge的两个端点是不是在一个集合里面，如果不是，就放到一个集合中
            if (!disjoint_set.InSameSet(edge.a, edge.b)) {
                disjoint_set.Union(edge.a, edge.b);
                // 然后把当前的边加入到mst中
                mst.push_back(edge);
            }
        }

        // 最终需要返回mst的权和
        int cost = 0;
        for (const UndirectedEdge& edge : mst) {
            cost += edge.cost;
        }
        return cost;
    }

    int SparseMSTV2(const std::vector<int>& sub_indicies,
                    const std::vector<UndirectedEdge>& original_mst,
                    const std::vector<std::vector<UndirectedEdge>>& sub_edges) {
        // 我们不需要mst 我们只需要cost
        int cost = 0;
        DisjointSet disjoint_set{static_cast<size_t>(this->_cities_count + 1)};
        for (const int i : sub_indicies) {
            const std::vector<UndirectedEdge>& edges = sub_edges[i];
            for (const UndirectedEdge& edge : edges) {
                // 看看edge的两个端点是不是在一个集合里面，如果不是，就放到一个集合中
                if (!disjoint_set.InSameSet(edge.a, edge.b)) {
                    // TODO: 这里也是可以提前退出的
                    disjoint_set.Union(edge.a, edge.b);
                    // 然后把当前的边加入到mst中
                    // mst.push_back(edge);
                    cost += edge.cost;
                }
            }
        }
        // 自网络遍历完了，就遍历mst的边
        // 只要这些边在集合中的，就跳过就行了
        // 但是我们怎么判断我们的mst中的某条边是否在自网络中呢？
        // 或者，我们需要判断吗
        // 假设我们的某条边在subnetwork中，那么这条边有两种状态，要么被选择了，要么没有
        // 如果被选择了：那么这个边的两个端点一定已经加入到同一个集合中了，我们的判断就会为假，是ok的
        // 如果没有被选择，他是零的权重，都没有被选择，这不可能
        // 如果没有，那么就正常的处理
        // 所以经过讨论，根本就不需要判断是否在subnetwork中！
        for (const UndirectedEdge& edge : original_mst) {
            // 看看edge的两个端点是不是在一个集合里面，如果不是，就放到一个集合中
            if (!disjoint_set.InSameSet(edge.a, edge.b)) {
                // TODO: 这里也是可以提前退出的
                disjoint_set.Union(edge.a, edge.b);
                // 然后把当前的边加入到mst中
                // mst.push_back(edge);
                cost += edge.cost;
            }
        }
        return cost;
    }

    std::vector<UndirectedEdge>
    GetAllEdgesFromSubNetwork(const SubNetwork& sub_network) {

        std::vector<UndirectedEdge> edges;
        // 防止出现重复的边和self边
        for (int i = 0; i < sub_network.cities.size(); i++) {
            for (int j = i + 1; j < sub_network.cities.size(); j++) {
                edges.push_back(UndirectedEdge{sub_network.cities[i],
                                               sub_network.cities[j], 0});
            }
        }
        return edges;
    }

  private:
    void InitCityGraph(const std::vector<City>& cities) {
        for (int i = 0; i < cities.size(); i++) {
            const City& city1 = cities[i];
            for (int j = 0; j < cities.size(); j++) {
                const City& city2 = cities[j];

                int cost = (city1.x - city2.x) * (city1.x - city2.x) +
                           (city1.y - city2.y) * (city1.y - city2.y);
                city_graph[i + 1][j + 1] = cost;
                city_graph[j + 1][i + 1] = cost;
            }
        }
    }

  private:
    int _cities_count;
};

int main(int argc, char* argv[]) {
    int case_count = 0;
    std::cin >> case_count;

    // [1, 1000]
    // Cities are identified by a unique integer value ranging from 1 to n.
    // 也就是序号是从1开始的
    int cities_count = 0;
    // [0, 8]
    int sub_networks_count = 0;

    for (int kase = 1; kase <= case_count; kase++) {
        if (kase != 1) {
            std::cout << std::endl;
        }
        std::cin >> cities_count >> sub_networks_count;

        std::vector<SubNetwork> sub_networks;
        // 首先是subnetwork的描述
        // The first line is followed by q lines(one per subnetwork)
        for (int i = 0; i < sub_networks_count; i++) {
            // The first integer is the number of cities in the subnetwork
            int cities_in_subnetwork_count = 0;
            std::cin >> cities_in_subnetwork_count;
            // The second integer is the the cost of the subnetwork (not greater
            // than 2 ×10^6).
            int subnetwork_cost = 0;
            std::cin >> subnetwork_cost;

            // The remaining integers on the line (as many as the number of
            // cities in the subnetwork) are the identifiers of the cities in
            // the subnetwork
            // 剩下的就是城市了
            std::vector<int> cities;
            for (int c = 0; c < cities_in_subnetwork_count; c++) {
                int city = 0;
                std::cin >> city;
                cities.push_back(city);
            }

            sub_networks.push_back(SubNetwork{subnetwork_cost, cities});
        }

        std::vector<City> cities;
        //  The last part of the file contains nlines that provide the
        //  coordinates of the citie, based on its ordering
        // Each line is made of 2 integer values(ranging from 0 to 3000)
        for (int i = 0; i < cities_count; i++) {
            City city{};
            std::cin >> city.x >> city.y;
            cities.push_back(city);
        }

        Solution solution{cities};

        std::vector<UndirectedEdge> mst = solution.GetMST();

        // 这个事不需要的 因为Enumrate考虑到了这种可能性
        // if (sub_networks_count == 0) {
        //     // 这里就直接返回mst的cost就行了
        //     int mycost = 0;
        //     for (const UndirectedEdge& edge : mst) {
        //         mycost += edge.cost;
        //     }
        //     std::cout << mycost << std::endl;
        //     continue;
        // }

        // 然后我们开始枚举所有方案

        // output: optimal total cost, just a number
        // 因为这个东西一定是个整数, 而且int也放得下
        // 9 * 10^3 + 8 * 2 * 10^6, 完全放得下

        // 首先在整张图上跑一个MST，这是个完全图
        // 对于每个节点，都需要计算她的权重
        // 因为这是完全图，所以才去邻接表的方式存储边就变得不合适了
        // 比较好的方式是使用邻接矩阵
        // 我们预先定义一张二维数组吧

        // 根据我们拿到的cities 我们要初始化这张权重图
        // 我们在遍历所有的边的时候，可以只便利一半的
        // 对称矩阵的存储不知道solution里有没有更好的解法 TODO 写完了去查看一下

        // 咱们的程序从逻辑上讲是非常简单的，就是枚举所有的套餐选择
        // 然后结合套餐和现有
        int cost = solution.Enumerate(sub_networks_count, sub_networks, mst);
        std::cout << cost << std::endl;
    }
}
