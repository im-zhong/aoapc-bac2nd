// 2024/11/30
// zhangzhong

#include <iostream>

constexpr int max_cut_point = 64;
constexpr int inf = 1 << 30;

int GetMinimumCost(int cut_point[max_cut_point], int n) {

    int dp[max_cut_point][max_cut_point] = {};

    for (int dis = 2; dis <= n + 1; dis++) {
        for (int i = 0; i + dis <= n + 1; i++) {
            int j = i + dis;
            dp[i][j] = inf;
            for (int k = i + 1; k < j; k++) {
                dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k][j]);
            }
            if (dp[i][j] == inf) {
                dp[i][j] = 0;
            }
            dp[i][j] += cut_point[j] - cut_point[i];
        }
    }

    return dp[0][n + 1];
}

int main() {
    int length = 0;
    int n = 0;
    while (std::cin >> length) {
        if (length == 0) {
            break;
        }

        std::cin >> n;

        int cut_point[max_cut_point];
        cut_point[0] = 0;
        for (int i = 1; i <= n; i++) {
            std::cin >> cut_point[i];
        }
        cut_point[n + 1] = length;

        int minimum_cost = GetMinimumCost(cut_point, n);
        std::cout << "The minimum cutting is " << minimum_cost << ".\n";
    }
}