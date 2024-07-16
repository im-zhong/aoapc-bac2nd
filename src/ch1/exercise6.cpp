// 2024/1/17
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("exercise 1-6 triangle") {
    int a = 0;
    int b = 0;
    int c = 0;
    std::scanf("%d%d%d", &a, &b, &c);

    // sum of any two edges larger than the third edge
    if (!(a + b > c && a + c > b && b + c > a)) {
        std::printf("not a triangle\n");
        return;
    }

    // find the largest edge
    // and the last two edges's square sum should equal to its square
    // we let c to be the max
    int t = 0;
    if (c < a) {
        t = c;
        c = a;
        a = b;
    }
    if (c < b) {
        t = c;
        c = b;
        b = t;
    }
    if (a * a + b * b == c * c) {
        printf("yes\n");
    } else {
        printf("no\n");
    }
}