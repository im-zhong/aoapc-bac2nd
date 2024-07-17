// 2024/7/17
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <climits>
#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("example 2-6") {
    int n = 0;

    for (int level = 0;; level++) {

        if (std::scanf("%d", &n) != 1 || n == 0) {
            return;
        }

        if (level != 0) {
            std::printf("\n");
        }

        int m = 0;
        int min = INT_MAX;
        int max = INT_MIN;
        double sum = 0;
        for (int i = 0; i < n; i++) {
            std::scanf("%d", &m);
            if (min > m) {
                min = m;
            }
            if (max < m) {
                max = m;
            }
            sum += m;
        }
        std::printf("Case %d: %d %d %.3lf\n", level + 1, min, max, sum / n);
    }
}