// 2024/7/17
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <climits>
#include <cstdio>
#include <doctest/doctest.h>

// TODO：现在的实现肯定是不对的，将来学了BigInteger在回来看看
TEST_CASE("exercise 2-5 decimal") {
    int a = 0;
    int b = 0;
    int c = 0;
    while (std::scanf("%d%d%d", &a, &b, &c) == 3 && a != 0 && b != 0 &&
           c != 0) {
        // first calculate the integer part
        std::printf("%d.", a / b);
        // if (a % b == 0) {
        //     // then the fractional part is all zero
        //     for (int i = 0; i < c; i++) {
        //         std::printf("0");
        //     }
        // }

        a = a % b;
        for (int i = 0; i < c - 1; i++) {
            a = a * 10;
            std::printf("%d", a / b);
            a = a % b;
            // it handle the situation when remainder is 0
            // the output is 0, correct
        }

        // I need to implement 四舍五入
        a = a * 10;
        int last_number = a / b;
        a = a % b;

        a = a * 10;
        int number_after_last_number = a / b;
        if (number_after_last_number >= 5) {
            last_number += 1;
        }
        std::printf("%d", last_number);

        std::printf("\n");
    }
}