// 2024/7/17
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <climits>
#include <cstdio>
#include <doctest/doctest.h>

TEST_CASE("exercise 2-6 permutation") {
    for (int a = 1; a <= 9; a++) {
        for (int b = 1; b <= 9; b++) {
            if (b == a) {
                continue;
            }
            for (int c = 1; c <= 9; c++) {
                if (c == a || c == b) {
                    continue;
                }

                int abc = a * 100 + b * 10 + c;
                int def = abc + abc;
                int ghi = def + abc;
                // we could stop early
                // if ghi is not under 999, then we are stop
                if (ghi > 999) {
                    return;
                }

                // then split def and ghi
                // I want to define an array to check if some digit is already
                // there
                int d = def / 100;
                int e = (def / 10) % 10;
                int f = def % 10;
                int g = ghi / 100;
                int h = (ghi / 10) % 10;
                int i = ghi % 10;

                // now calculate the count for each digits
                // the first slot of the array is not uses
                int digits[10] = {
                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                };
                digits[a] += 1;
                digits[b] += 1;
                digits[c] += 1;
                digits[d] += 1;
                digits[e] += 1;
                digits[f] += 1;
                digits[g] += 1;
                digits[h] += 1;
                digits[i] += 1;

                // if there exist one digit is not 1, then current permutation
                // is wrong
                bool is_result = true;
                for (int i = 1; i < 10; i++) {
                    if (digits[i] != 1) {
                        is_result = false;
                        break;
                    }
                }
                if (is_result) {
                    std::printf("%d %d %d\n", abc, def, ghi);
                }
            }
        }
    }
}