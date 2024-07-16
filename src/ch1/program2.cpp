// 2024/7/15

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <iomanip>
#include <iostream>

TEST_CASE("program 1-2") { std::cout << 8.0 / 5.0 << std::endl; }

TEST_CASE("experiment 5") {
    // 1. Use std::fixed to ensure that floating-point numbers are written in
    // fixed-point notation.
    // 2. Use std::setprecision(n) to set the precision to n decimal places.
    // n = 1: 1.6
    // n = 2: 1.60
    // so n is the digit after dot
    std::cout << std::fixed << std::setprecision(2) << 8.0 / 5.0 << std::endl;
}

TEST_CASE("experiment 6") {
    // actually I'm not sure if this is the same behaviour in C
    // the output is 1.0
    std::cout << std::fixed << std::setprecision(2)
              << static_cast<double>(8 / 5) << std::endl;
    // the output is 0.0
    // 看起来应该是直接把整数的编码当作浮点数来输出了
    std::printf("%.1f\n", 8 / 5);
}

TEST_CASE("experiment 7") {
    // 1
    std::cout << static_cast<int>(8.0 / 5.0) << std::endl;
    // -1717986918
    std::printf("%d\n", 8.0 / 5.0);
}
