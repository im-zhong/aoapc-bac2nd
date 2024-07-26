// 2024/7/21
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cstdio>
#include <cstring>
#include <doctest/doctest.h>

char input[128] = {};
char mirrored_characters[26 + 1] = "A...3..HIL.JM.O...2TUVWXY5";
char mirrored_digits[9 + 1] = "1SE.Z..8.";
// 感觉数字和字母可以分开 毕竟他们在ascii里面也不是连着的

int main() {
    while (std::scanf("%s", input) == 1) {

        char* head = input;
        char* tail = head + std::strlen(input) - 1;

        bool is_palindrome = true;

        while (head < tail) {
            if (*head != *tail) {
                is_palindrome = false;
                break;
            }
            head += 1;
            tail -= 1;
        }

        bool is_mirrored = true;
        head = input;
        tail = head + std::strlen(input) - 1;
        while (head < tail) {
            if (*head >= 'A' && *head <= 'Z') {
                if (mirrored_characters[*head - 'A'] != *tail) {
                    is_mirrored = false;
                    break;
                }
            } else if (*head >= '1' && *head <= '9') {
                if (mirrored_digits[*head - '1'] != *tail) {
                    is_mirrored = false;
                    break;
                }
            } else {
                break;
            }
            head += 1;
            tail -= 1;
        }

        // four situation
        if (!is_palindrome && !is_mirrored) {
            std::printf("%s -- is not a palindrome.\n\n", input);
        } else if (is_palindrome && is_mirrored) {
            std::printf("%s -- is a mirrored palindrome.\n\n", input);
        } else if (is_palindrome) {
            std::printf("%s -- is a regular palindrome.\n\n", input);
        } else {
            std::printf("%s -- is a mirrored string.\n\n", input);
        }
    }
}