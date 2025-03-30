// 2025/3/30
// zhangzhong

// 我懂了，这道题简单，就是一遍遍历求最小生成树的问题
// 求完之后的 W[R] - W[L]就是slim

#include <algorithm>
#include <iostream>
#include <vector>

class DisjointSet {

  public:
    DisjointSet(const size_t size) : _size(size), _sets(size, -1) {}

    void Reset() {
        // 初始化，所有节点都自己一个集合
        // for (int i = 0; i < this->_sets.size(); i++) {
        //     _sets[i] = -1;
        // }
        std::fill(this->_sets.begin(), this->_sets.end(), -1);
    }

    // 主要实现两个方法 find union

    int Find(int node) {

        if (this->_sets[node] < 0) {
            return node;
        }

        return this->_sets[node] = this->Find(this->_sets[node]);
    }

    // 我们在union结束之后，返回合并之后的集合的大小吧
    int Union(int x, int y) {
        // TODO：但是为什么书上的实现，就是简单的合并x和y和？
        // 根据我们的理解，想要合并x和y所属的集合，应该合并他们的根才对呀
        // find 返回的是集合，也就是根所在的索引的位置！
        int root_x = this->Find(x);
        int root_y = this->Find(y);

        // 两个节点可能属于同一个类
        if (root_x == root_y) {
            // 那么就什么都不做
            return -this->_sets[root_x];
        } else {
            // 我们把小的类合并到大的里面
            // 算了，这个在实现起来有点麻烦了
            int x_size = -this->_sets[root_x];
            int y_size = -this->_sets[root_y];

            this->_sets[root_y] = root_x;
            this->_sets[root_x] = -(x_size + y_size);
            return (x_size + y_size);
        }

        // 最简单的实现方法，
        // 就是让x成为y的parent
        // this->_sets[root_x] = root_y;
    }

    size_t GetSize() const noexcept { return this->_size; }

  private:
    size_t _size;
    std::vector<int> _sets;
};

struct UndirectedEdge {
    int a;
    int b;
    int w;
};

class Graph {
  public:
    Graph(int vertices_count, int edges_count)
        : _vertices_count(vertices_count), _edges_count(edges_count) {}

    void AddEdge(const UndirectedEdge& edge) { this->_edges.push_back(edge); }

    void SortEdgesByWeight() {
        std::sort(this->_edges.begin(), this->_edges.end(),
                  [](const UndirectedEdge& lhs, const UndirectedEdge& rhs) {
                      return lhs.w < rhs.w;
                  });
    }

    int FindSlimSpanningTree() {

        // 首先将权重排序
        this->SortEdgesByWeight();

        // 声明一个disjoint set
        // 因为我们的节点是从1开始的 所以disjoint set的数量要vertiecs count + 1
        DisjointSet disjoint_set(this->_vertices_count + 1);

        const int max_slimness = 1000000;
        int min_slimness = max_slimness;

        // 将已经排序的权重
        // 使用两个索引 left right
        // 分别表示我们需要使用的边
        for (int left = 0; left < this->_edges.size(); left++) {

            // 每次都创建一个新的disjoinst set
            // 或者给disjoint set提供一个init方法
            disjoint_set.Reset();

            for (int right = left; right < this->_edges.size(); right++) {

                // 在遍历的过程中就可以开始寻找最小生成树了
                // 此时我需要一个并查集
                // 将right指向的边变成一个集合
                UndirectedEdge& edge = this->_edges[right];
                // 不对啊，这不会成环吗？
                // 成环之后还叫生成树吗？
                // 这妥妥的不对啊，
                // 不对不对，union同个集合的节点什么都不会发生，但是这条边不应该加入到生成树中
                // 同时最小的边一定会加入到生成树中的
                // 其实我们根据这个应该就可以记录生成树的边了
                // 然后在遍历的过程中，只要目前还没有加入到集合中的，就加入进行，然后边加入到MST中
                // MST就是边的集合，是一颗无根树
                // 但是在这个问题中，我们不需要保存MST，因为我们只需要slim，而left和right一定就是slim
                // 最大和最小的边！
                int set_size = disjoint_set.Union(edge.a, edge.b);

                // 什么时候结束呢？就是当所有的节点都在同一个集合中时，这个要怎么判断呢？
                // 就算是原本的算法，kruskal也需要判断是否结束啊
                // 最简单的办法就是遍历查找所有的节点的集合，但是这应该是非常慢的
                // 还有一个办法，union是否可以记录，我记得disjoint
                // set的实现是可以记录节点的数量的 根据这个东西
                // 我们就可以知道所有的节点是不是都属于同一个集合了。
                // find不会改变集合的元素数量
                // 只有union会

                // 集合的根使用负数存储当前类的大小
                // 而其他节点存储的是负数，也就是类的名字，它应当是某个根的索引
                if (set_size == _vertices_count) {
                    // 所有的节点都属于同一个集合了
                    // 那么目前一定有一颗最小生成树
                    // 但是这棵最小生成树一定是由left和right最小最大组成的吗？
                    // 我们应该需要知道最小生成树用了哪些变？
                    // 首先最大的我们知道，应该是这个right，因为就是加入了这个right，我们才组成了生成树
                    // 但是最小的边呢？
                    // 咱们就先用right - left 吧
                    // 这些个图的结论，咱们不知道啊，也别瞎想了，不如直接了解，理解，然后记住就行了
                    int slimness = this->_edges[right].w - this->_edges[left].w;
                    if (slimness < min_slimness) {
                        min_slimness = slimness;
                    }
                    break;
                }
            }
        }

        if (min_slimness == max_slimness) {
            return -1;
        }
        return min_slimness;
    }

  private:
    // 使用数组保存边，因为待会要排序
    std::vector<UndirectedEdge> _edges;
    int _vertices_count;
    int _edges_count;
};

int main(int argc, char* argv[]) {

    // [2, 100]
    int vertices_count = 0;
    // [0, n(n-1)/2] 没有边，到完全图
    int edges_count = 0;

    while (std::cin >> vertices_count >> edges_count) {
        if (vertices_count == 0 && edges_count == 0) {
            break;
        }

        if (edges_count == 0) {
            std::cout << -1 << std::endl;
            continue;
        }
        // BUG: 有一条边需要读，但是我们没读 所以出问题了
        // if (edges_count == 1) {
        //     std::cout << 0 << std::endl;
        //     continue;
        // }
        // input:
        // 接下来应该就是m行，每行代表一条边，然后是一个权重
        // akand bk(k= 1,...,m) are positive integers less than or equal to n
        // 可以看到节点是从1开始索引的
        // wk is a positive integer less than or equal to 10000
        // simple graph: no self-loops, no parallel edges
        // no self-loops (that connect the same vertex) nor parallel edges (that
        // are two or more edges whose both ends are the same two vertices)

        // output:
        // slimness or -1

        Graph graph{vertices_count, edges_count};
        for (int i = 0; i < edges_count; i++) {
            UndirectedEdge edge{};
            std::cin >> edge.a >> edge.b >> edge.w;
            graph.AddEdge(edge);
        }

        // 然后我们对边进行排序
        // graph.SortEdgesByWeight();

        // 然后我们就可以开始遍历了
        // 当然这个遍历的过程最好是写在类里面
        int min_slimess = graph.FindSlimSpanningTree();
        std::cout << min_slimess << std::endl;
    }
}