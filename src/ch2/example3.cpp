// 2024/7/16
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("example 2-3 近似计算") {
    double quarter_pi = 0;

    double sign = 1.0;
    for (int k = 1;; k += 2) {
        double fraction = 1.0 / k;
        quarter_pi += sign * fraction;
        sign = -sign;

        if (k < 1e-6) {
            break;
        }
    }
    std::printf("%lf\n", quarter_pi);
    std::printf("%lf\n", 4 * quarter_pi);
}