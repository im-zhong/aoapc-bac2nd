// 2024/7/15

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("example 1-3") {
    int a = 0;
    int b = 0;
    std::scanf("%d%d", &a, &b);

    int t = a;
    a = b;
    b = t;

    std::printf("%d %d\n", a, b);
}

TEST_CASE("example 1-8") {
    int a = 0;
    int b = 0;
    std::scanf("%d%d", &a, &b);

    a = a + b;
    b = a - b;
    a = a - b;

    std::printf("%d %d\n", a, b);
}

TEST_CASE("example 1-8#2") {
    int a = 0;
    int b = 0;
    std::scanf("%d%d", &a, &b);

    a = a - b;
    b = a + b;
    a = b - a;

    std::printf("%d %d\n", a, b);
}

TEST_CASE("example 1-10") {
    int a = 0;
    int b = 0;
    std::scanf("%d%d", &a, &b);
    std::printf("%d %d\n", b, a);
}
