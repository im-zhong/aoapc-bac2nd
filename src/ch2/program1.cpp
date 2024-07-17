// 2024/1/17
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("program 2-1") {
    int n = 0;
    std::scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("%d\n", i + 1);
    }
}