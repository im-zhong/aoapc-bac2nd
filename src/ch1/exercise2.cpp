// 2024/1/17
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("exercise 1-2 temperature") {
    double f = 0;
    std::scanf("%lf", &f);
    std::printf("%.3lf\n", 5 * (f - 32) / 9);
}