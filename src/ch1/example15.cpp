// 2024/1/17
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("example 1-15") {
    int a = 0;
    int b = 0;

    // input: s 1
    // scanf will exit when encouter error, so b is 0, not 1
    std::scanf("%d%d", &a, &b);
    printf("%d %d\n", a, b);
}
