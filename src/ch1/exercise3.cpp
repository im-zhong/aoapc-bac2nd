// 2024/1/17
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("exercise 1-3 sum") {
    int n = 0;
    std::scanf("%d", &n);
    std::printf("%d\n", n * (n + 1) / 2);
}