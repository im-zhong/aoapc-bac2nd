// 2024/7/15

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cmath>
#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("example 1-1") {
    const double pi = std::acos(-1);
    double r = 0;
    double h = 0;

    // float use %f, double use %lf
    std::scanf("%lf%lf", &r, &h);
    std::printf("Area = %.3f\n", 2.0 * pi * r * (r + h));
}
