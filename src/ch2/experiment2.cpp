// 2024/7/17
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <climits>
#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("experiment 2") {
    double i;
    // deap loop
    // the most closer number is 9.99999999999
    for (i = 0; i != 10; i += 0.1) {
        std::printf("%.1f\n", i);
    }
}