// 2024/7/17
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <climits>
#include <cstdio>
#include <doctest/doctest.h>

// TODO: use 高斯余数定理 来解决这个问题
TEST_CASE("exercise 2-2 hanxin") {
    int a = 0;
    int b = 0;
    int c = 0;
    int level = 1;
    while (std::scanf("%d%d%d", &a, &b, &c) == 3) {
        bool is_found = false;
        for (int n = 10; n <= 100; n++) {
            if (n % 3 == a && n % 5 == b && n % 7 == c) {
                printf("Case %d: %d\n", level, n);
                is_found = true;
                break;
            }
        }
        if (!is_found) {
            std::printf("Case %d: No answer\n", level);
        }

        level += 1;
    }
}