// 2024/7/15
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>
#include <iostream>

TEST_CASE("example 1-1") { std::cout << 1 + 2 << std::endl; }

TEST_CASE("experiment 1") { std::cout << 3 - 4 << std::endl; }

TEST_CASE("experiment 2") { std::cout << 5 * 6 << std::endl; }

TEST_CASE("experiment 3") { std::cout << 8 / 4 << std::endl; }

TEST_CASE("experiment 4") { std::cout << 8 / 5 << std::endl; }