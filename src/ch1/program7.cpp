// 2024/7/15

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("example 1-7") {
    int n = 0;
    std::scanf("%d", &n);

    int m = (n % 10) * 100 + ((n / 10) % 10) * 10 + (n / 100);
    std::printf("%d\n", m);
}
