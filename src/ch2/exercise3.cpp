// 2024/7/17
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <climits>
#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("exercise 2-3 triangle") {
    int max_level = 0;
    std::scanf("%d", &max_level);

    for (int current_level = 1; current_level <= max_level; current_level++) {
        // first, print enough space
        for (int i = 0; i < (current_level - 1); i++) {
            std::printf(" ");
        }

        // then, print enough #
        int count = 2 * (max_level - current_level) + 1;
        for (int i = 0; i < count; i++) {
            std::printf("#");
        }

        // finally, print the newline
        std::printf("\n");
    }
}