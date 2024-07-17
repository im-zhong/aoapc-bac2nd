// 2024/7/17
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <climits>
#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("exercise 2-4 subsequence") {
    int n = 0;
    int m = 0;
    int level = 1;
    while (std::scanf("%d%d", &n, &m) == 2 && n != 0 && m != 0) {
        double sum = 0;
        for (int i = n; i <= m; i++) {
            sum += 1 / (static_cast<double>(i) * static_cast<double>(i));
        }
        std::printf("Case %d: %.5lf\n", level, sum);
    }
}