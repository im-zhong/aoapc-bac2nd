// 2024/1/17
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("exercise 1-5 discount") {
    int n = 0;
    const double price = 95;
    std::scanf("%d", &n);
    double cost = price * n;
    if (cost >= 300.0) {
        cost *= 0.85;
    }
    std::printf("%.2lf", cost);
}