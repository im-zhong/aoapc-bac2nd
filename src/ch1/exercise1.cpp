// 2024/1/17
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("exercise 1-1 average") {
    double a = 0;
    double b = 0;
    double c = 0;

    std::scanf("%lf%lf%lf", &a, &b, &c);
    std::printf("%.3lf\n", (a + b + c) / 3.0);
}