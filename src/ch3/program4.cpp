// 2024/7/18
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cmath>
#include <cstdio>
#include <cstring>
#include <doctest/doctest.h>

bool digits[10] = {};
int digit_set[10] = {};

TEST_CASE("program 3-4") {
    int n = 0;
    // n = 2357;
    std::scanf("%d", &n);
    if (n == 0) {
        std::printf("The number of solutions: 0\n");
        return;
    }

    // first, get the number set
    while (n > 0) {
        digits[n % 10] = true;
        n /= 10;
    }

    // then enumeration all the possible of abc*de
    int digit_num = 0;
    for (int i = 0; i < 10; i++) {
        if (digits[i]) {
            digit_set[digit_num] = i;
            digit_num += 1;
        }
    }

    int solution_count = 1;

    for (int a = 0; a < digit_num; a++) {
        for (int b = 0; b < digit_num; b++) {
            for (int c = 0; c < digit_num; c++) {
                int abc = digit_set[a] * 100 + digit_set[b] * 10 + digit_set[c];

                for (int d = 0; d < digit_num; d++) {

                    for (int e = 0; e < digit_num; e++) {
                        bool is_all_in_digits = true;
                        int de = digit_set[d] * 10 + digit_set[e];

                        // abc = 775;
                        // de = 33;

                        int abce = abc * (digit_set[e]);
                        int abcd = abc * (digit_set[d]);
                        int abcde = abc * de;

                        // abce = 775 * 3;
                        // abcd = 775 * 3;

                        // now we got abc* de = abcd + abce = abcde
                        // then check all the digits in abcd, abce, abcde is in
                        // the digit set
                        int m = abcd;
                        while (m) {
                            int digit = m % 10;
                            if (!digits[digit]) {
                                is_all_in_digits = false;
                                break;
                            }
                            m /= 10;
                        }
                        if (!is_all_in_digits) {
                            continue;
                        }

                        m = abce;
                        while (m) {
                            int digit = m % 10;
                            if (!digits[digit]) {
                                is_all_in_digits = false;
                                break;
                            }
                            m /= 10;
                        }
                        if (!is_all_in_digits) {
                            continue;
                        }

                        m = abcde;
                        while (m) {
                            int digit = m % 10;
                            if (!digits[digit]) {
                                is_all_in_digits = false;
                                break;
                            }
                            m /= 10;
                        }
                        if (!is_all_in_digits) {
                            continue;
                        }

                        // now, we could render the shushi
                        std::printf("<%d>\n", solution_count);
                        solution_count += 1;

                        std::printf("%5d\n", abc);
                        std::printf("X%4d\n", de);
                        std::printf("-----\n");
                        std::printf("%5d\n", abce);
                        std::printf("%4d \n", abcd);
                        std::printf("-----\n");
                        std::printf("%5d\n", abcde);
                        std::printf("\n");
                    }
                }
            }
        }
    }

    std::printf("The number of solutions: %d\n", solution_count - 1);
}