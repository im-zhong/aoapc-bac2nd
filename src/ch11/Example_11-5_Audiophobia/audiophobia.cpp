// 2025/3/31
// zhangzhong

#include <algorithm>
#include <iostream>
#include <vector>

struct UndirectedEdge {
    int c1;
    int c2;
    int d;
};

struct Query {
    int c1;
    int c2;
};

const int MAX_CROSSINGS_COUNT = 128;
int graph[MAX_CROSSINGS_COUNT][MAX_CROSSINGS_COUNT];

const int MAX_NOISE = 1000000;

void ResetGraph() {
    for (int i = 0; i < MAX_CROSSINGS_COUNT; i++) {
        for (int j = 0; j < MAX_CROSSINGS_COUNT; j++) {
            // 因为这道题目不需要加起来，我们不用考虑溢出的问题
            graph[i][j] = MAX_NOISE;
        }
    }
}

int main(int argc, char* argv[]) {

    // crossings are numbered using distinct integers ranging from 1 to C
    // [0, 100] 也就是结点的数量
    int corssings_count = 0;

    // [0, 1000]
    int streets_count = 0;

    // Q,
    // 所谓的query就是问你两个点，在这两个点的路径上，最小的必须路过的噪音是多少
    int queries_count = 0;

    for (int kase = 1;
         std::cin >> corssings_count >> streets_count >> queries_count;
         kase++) {
        if (corssings_count == 0 && streets_count == 0 && queries_count == 0) {
            break;
        }

        if (kase != 1) {
            std::cout << "\n";
        }

        ResetGraph();

        // 咱们都不需要保存这些边的
        // std::vector<UndirectedEdge> edges{};
        // Each of the next S(streets_count) lines contains three integer
        // c1 c2 d 就是一条带权的无向边, c1 != c2
        for (int s = 0; s < streets_count; s++) {
            UndirectedEdge edge{};
            std::cin >> edge.c1 >> edge.c2 >> edge.d;
            // edges.push_back(edge);
            // 我们读取的是无向边
            // 但是folyd 邻接矩阵保存的是有向边
            // 所以需要对称的保存
            graph[edge.c1][edge.c2] = edge.d;
            graph[edge.c2][edge.c1] = edge.d;
        }

        // 然后在这里运行floyd算法
        // 不对，节点是从1开始的
        for (int k = 1; k <= corssings_count; k++) {
            for (int i = 1; i <= corssings_count; i++) {
                for (int j = 1; j <= corssings_count; j++) {
                    graph[i][j] = std::min(graph[i][j],
                                           std::max(graph[i][k], graph[k][j]));
                }
            }
        }

        // Each of the next Q(queries_count) lines contains two integers
        // c1 c2
        // sking for the minimum sound
        // intensity level you must be able to tolerate in order to get from
        // crossing c1 to crossing c2
        std::cout << "Case #" << kase << "\n";
        for (int q = 0; q < queries_count; q++) {
            Query query{};
            std::cin >> query.c1 >> query.c2;

            int noise = graph[query.c1][query.c2];
            if (noise == MAX_NOISE) {
                std::cout << "no path";
            } else {
                std::cout << graph[query.c1][query.c2];
            }
            std::cout << std::endl;

            // 这里其实可以直接输出的呀 因为这道题目其实相当的简单了
            // 简单到我们设置不需要写一个类啊
        }
    }
}
