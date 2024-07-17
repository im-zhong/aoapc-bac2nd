// 2024/7/17
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("example 2-4") {
    int n = 0;
    std::scanf("%d", &n);
    int N = 1000000;

    if (n > 24) {
        printf("%d\n", 940313);
    }

    int sum = 0;
    for (int i = 1; i <= n; i++) {
        int factorial = 1;
        for (int j = 1; j <= i; j++) {
            factorial = (factorial * j) % N;
        }
        sum = (sum + factorial) % N;
    }

    printf("%d\n", sum % 1000000);
}