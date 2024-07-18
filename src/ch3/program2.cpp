// 2024/7/18
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cmath>
#include <cstdio>
#include <cstring>
#include <doctest/doctest.h>

const int max_count = 1000;
int lights[max_count] = {};

TEST_CASE("program 3-2") {
    int n = 0;
    int k = 0;

    std::memset(lights, 0, sizeof(lights));

    std::scanf("%d%d", &n, &k);
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= n; j++) {
            // i stand for the i-th person
            // j stand for the j-th lignt
            if (j % i == 0) {
                lights[j] = !lights[j];
            }
        }
    }

    // the first element is not used
    for (int i = 1; i <= n; i++) {
        if (lights[i] == 1) {
            std::printf("%d ", i);
        }
    }
    std::printf("\n");
}