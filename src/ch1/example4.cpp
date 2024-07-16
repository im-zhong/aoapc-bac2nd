// 2024/1/17
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("exercise 1-4") {
    int n = 0;
    int m = 0;

    std::scanf("%d%d", &n, &m);

    int a = (4 * n - m) / 2;
    int b = n - a;

    // a and b is integer and is negative
    // if ((4 * n - m >= 0) && (4 * n - m) % 2 == 0 && n - a >= 0) {
    if (m % 2 == 0 && a >= 0 && b >= 0) {
        printf("%d %d\n", a, b);
    } else {
        printf("No answer");
    }
}