// 2024/7/18
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("program 3-1") {
    const int max_count = 1000000000;
    int arr[max_count] = {};

    int i = 0;
    int n = 0;
    while (std::scanf("%d", &n) == 1) {
        arr[i] = n;
        i += 1;
    }

    for (int j = n - 1; j >= 0; j--) {
        std::printf("%d ", arr[j]);
    }
    std::printf("\n");
}
