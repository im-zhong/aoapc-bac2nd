// 2024/7/17
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <climits>
#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("exercise 2-1 daffodil") {
    for (int n = 100; n <= 999; n++) {
        // n = abc
        int a = n / 100;
        int b = (n / 10) % 10;
        int c = n % 10;

        if (a * a * a + b * b * b + c * c * c == n) {
            printf("%d\n", n);
        }
    }
}