// 2024/12/2
// zhangzhong

#include <iostream>
#include <vector>

constexpr int max_n = 10240;
constexpr int inf = 1 << 20;

// [[BUG]]
// 这是一个无向图，dfs的时候需要考虑visited
void dfs(int root, int* dp1, int* dp2, int* dp3, bool* visited,
         const std::vector<std::vector<int>>& adjs, int n) {

    visited[root] = true;

    std::vector<int> childs;
    for (int child : adjs[root]) {
        if (visited[child]) {
            continue;
        }
        childs.push_back(child);
        dfs(child, dp1, dp2, dp3, visited, adjs, n);
    }

    // is leaf
    if (childs.empty()) {
        dp1[root] = 1;
        dp2[root] = 0;
        dp3[root] = inf;
        return;
    }

    // not leaf

    // 因为处理起来比较复杂，我们使用一个数组保存child吧

    // for (int child : adjs[root]) {
    //     // 只有在当前没有visited过的child才算
    //     dfs(child, dp1, dp2, dp3, adjs, n);
    // }

    // 然后我们开始计算 dp1 dp2 dp3
    // dp1
    // dp1 = 1 + sum of min{dp1[child], dp2[child]}
    dp1[root] = 1;
    for (int child : childs) {
        dp1[root] += std::min(dp1[child], dp2[child]);
    }

    // dp2
    // dp2 = sum of dp3[child]
    dp2[root] = 0;
    for (int child : childs) {
        dp2[root] += dp3[child];
    }

    // dp3
    // dp3 = min {dp2 - dp3[child] + dp1[child]}
    dp3[root] = inf;
    for (int child : childs) {
        dp3[root] = std::min(dp3[root], dp2[root] - dp3[child] + dp1[child]);
    }
}

int CalculatePerfectServiceNumber(const std::vector<std::vector<int>>& adjs,
                                  int n) {
    // 思路和MIS是一样的
    // 只不过状态更多，状态转移更加复杂

    // dp1[i]: 表示i是server，此时孩子可以是server，也可以不是server
    // dp2[i]:
    // 表示i不是server，i的parent是server，此时i的所有孩子必须都不是server
    // dp3[i]:
    // 表示i不是server，i的parent不是server，此时有且只有一个i的孩子是server
    // dp[i]均表示在给定条件下的最小的server数量

    // 先设置 dp2[root] = inf, 然后取三者最小, 或者直接不管dp2[root]
    // solution = min{dp1[root], dp3[root]}
    // 因为root不可能存在一个parent是server，只有1和3两种状态
    // init: 叶子
    // dp1[leaf] = 1
    // dp2[leaf] = 0
    // dp3[leaf] = inf
    // 3这种状态不应该出现在leaf上，使用一个超大的数表示此状态不应该存在

    int dp1[max_n];
    int dp2[max_n];
    int dp3[max_n];
    bool visited[max_n] = {};

    dfs(1, dp1, dp2, dp3, visited, adjs, n);

    return std::min(dp1[1], dp3[1]);
}

int main() {

    int n = 0;
    while (std::cin >> n) {

        // we use index from 1 to n
        std::vector<std::vector<int>> adjs(n + 1);
        for (int i = 0; i < n - 1; i++) {
            int n1 = 0;
            int n2 = 0;
            std::cin >> n1 >> n2;
            adjs[n1].push_back(n2);
            adjs[n2].push_back(n1);
        }

        int psn = CalculatePerfectServiceNumber(adjs, n);
        std::cout << psn << "\n";

        int zero = 0;
        std::cin >> zero;
        if (zero == -1) {
            break;
        }
    }
}