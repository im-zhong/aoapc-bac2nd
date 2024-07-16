// 2024/7/15

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("exercise 1-2") {
    int n = 0;
    std::scanf("%d", &n);
    std::printf("%d%d%d\n", n % 10, (n / 10) % 10, (n / 100));
}
