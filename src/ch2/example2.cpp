// 2024/7/16
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("example 2-2 3n+1") {
    long long n = 0;
    std::scanf("%lld", &n);
    int step = 0;
    while (n != 1) {
        if (n % 2 == 0) {
            n /= 2;
        } else {
            n = 3 * n + 1;
        }
        step += 1;
    }
    std::printf("%d\n", step);
}