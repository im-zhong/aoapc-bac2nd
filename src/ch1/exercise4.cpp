// 2024/1/17
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cmath>
#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("exercise 1-4 sin and cos") {
    const double pi = std::acos(-1);
    int n = 0;
    std::scanf("%d", &n);
    std::printf("%lf %lf\n", std::sin(pi * n / 180.0),
                std::cos(pi * n / 180.0));
}