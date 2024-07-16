// 2024/1/17
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cmath>
#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("experiment A1-1") { std::printf("%d\n", 11111 * 11111); }
TEST_CASE("experiment A1-2") { std::printf("%d\n", 111111 * 111111); }
TEST_CASE("experiment A1-3") { std::printf("%d\n", 111111111 * 111111111); }

TEST_CASE("experiment A2-1") { std::printf("%f\n", 11111.0 * 11111.0); }
TEST_CASE("experiment A2-2") { std::printf("%f\n", 111111.0 * 111111.0); }
TEST_CASE("experiment A2-3") { std::printf("%f\n", 111111111.0 * 111111111.0); }

// nan
TEST_CASE("experiment A3-1") { std::printf("%f\n", std::sqrt(-10)); }
// 0 !?
TEST_CASE("experiment A3-2") { std::printf("%d\n", std::sqrt(-10)); }

// inf nan
TEST_CASE("experiment A4-1") { std::printf("%f %f\n", 1.0 / 0.0, 0.0 / 0.0); }
// 0 0 !?
TEST_CASE("experiment A4-2") { std::printf("%d %d\n", 1.0 / 0.0, 0.0 / 0.0); }

// 71058640
TEST_CASE("experiment A5-1") { std::printf("%d\n", 1 / 0); }
// 0.0
TEST_CASE("experiment A5-1") { std::printf("%f\n", 1 / 0); }