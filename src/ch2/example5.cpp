// 2024/7/17
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <climits>
#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("example 2-5") {
    int n = 0;
    int k = 1;
    int min = INT_MAX;
    int max = INT_MIN;
    double avg = 0;
    while (std::scanf("%d", &n) == 1) {
        if (min > n) {
            min = n;
        }
        if (max < n) {
            max = n;
        }
        // case 2: calculate the sum, and calculate the avg at the end
        avg = ((k - 1) * avg + n) / k;
        k++;
    }
    std::printf("%d %d %.3lf\n", min, max, avg);
}

#define LOCAL

TEST_CASE("example 2-5 redirection") {
#ifdef LOCAL
    std::freopen("data.in", "r", stdin);
    std::freopen("data.out", "w", stdout);
#endif

    // the rest is same
}

TEST_CASE("example 2-5 fopen") {
    // Opens the file for reading in binary mode. No translations are performed
    // (e.g., no newline character conversion on Windows), and the file is read
    // exactly as it exists.
    std::FILE* fin = std::fopen("data.in", "rb");
    // Opens the file for writing in binary mode. If the file already exists,
    // its contents are truncated before opening. If the file does not exist, a
    // new file is created. Like with rb, no translations are performed.
    std::FILE* fout = std::fopen("data.out", "wb");

    // use std::fscanf to replace std::scanf
    // use std::fprintf to replace std::printf

    std::fclose(fin);
    std::fclose(fout);
}