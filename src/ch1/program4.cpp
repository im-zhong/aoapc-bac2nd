// 2024/7/15

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_CASE("example 1-4") {
    int a = 0;
    int b = 0;

    std::scanf("%d%d", &a, &b);
    std::printf("%d\n", a + b);
}
