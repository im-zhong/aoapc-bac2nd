// 2024/1/17
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("exercise 1-7 year") {
    int year = 0;
    std::scanf("%d", &year);

    bool is_leap = false;
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            is_leap = (year % 400 == 0);
        } else {
            is_leap = true;
        }
    }

    printf(is_leap ? "yes\n" : "no\n");
}