// 2024/7/16
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cmath>
#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("example 2-1 aabb") {
    for (int a = 1; a <= 9; a++) {
        for (int b = 0; b <= 9; b++) {
            // aabb
            // int aabb = b * 10 + b + a * 100 + a * 1000;
            int aabb = a * 1100 + b * 11;

            // not perfect
            // double sqrt = std::sqrt(aabb);
            // if (sqrt - static_cast<int>(sqrt) == 0) {
            //     printf("%d\n", aabb);
            // }

            // also not perfect
            int sqrt = std::floor(std::sqrt(aabb) + 0.5);
            if (sqrt * sqrt == aabb) {
                printf("%d\n", aabb);
            }
        }
    }
}

TEST_CASE("example 2-1 aabb #2") {
    // enumerate all the complete square number between 1000 - 9999
    // and then check if its in the format of aabb
    for (int n = 1;; n++) {
        int square = n * n;
        if (square < 1000) {
            continue;
        }
        if (square > 9999) {
            break;
        }

        // not good
        // if (((square % 10) == ((square / 10)) % 10) &&
        //     ((square / 100) % 10 == (square / 1000))) {
        //     printf("%d\n", square);
        // }

        // good
        int high = square / 100;
        int low = square % 100;
        if (high / 10 == high % 10 && low / 10 == low % 10) {
            printf("%d\n", square);
        }
    }
}