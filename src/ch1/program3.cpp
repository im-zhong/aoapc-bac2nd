// 2024/7/15

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cmath>
#include <doctest/doctest.h>
#include <iostream>

TEST_CASE("program 1-3") {
    std::cout << 1 + 2 * std::sqrt(3) / (5 - 0.1) << std::endl;
}
