// 2024/1/17
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("exercise 1-5") {
    int a = 0;
    int b = 0;
    int c = 0;
    int t = 0;

    std::scanf("%d%d%d", &a, &b, &c);
    // a <= b <= c
    if (a > b) {
        t = a;
        a = b;
        b = t;
    }
    // now a <= b

    // case 1: c a b
    // case 2: a c b
    // case 3: a b c
    if (a > c) {
        t = a;
        a = c;
        c = t;
    }

    // only in case 1, we swap the a and c
    // now we only left with two cases
    // a c b
    // a b c
    if (b > c) {
        t = b;
        b = c;
        c = t;
    }

    std::printf("%d %d %d\n", a, b, c);
}