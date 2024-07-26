// 2024/7/21
// zhangzhong

#include <cstdio>
#include <cstring>
using namespace std;

char input[128] = {};
char mirrored_characters[26 + 1] = "A...3..HIL.JM.O...2TUVWXY5";
char mirrored_digits[9 + 1] = "1SE.Z..8.";
// 感觉数字和字母可以分开 毕竟他们在ascii里面也不是连着的

int main() {
    bool is_start = true;
    while (scanf("%s", input) == 1) {
        if (!is_start) {
            printf("\n\n");
        }
        is_start = false;

        char* head = input;
        char* tail = head + strlen(input) - 1;

        bool is_palindrome = true;

        while (head < tail) {
            if (*head != *tail) {
                is_palindrome = false;
                break;
            }
            head++;
            tail--;
        }

        bool is_mirrored = true;
        head = input;
        tail = head + strlen(input) - 1;
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
            head++;
            tail--;
        }

        // four situation
        if (!is_palindrome && !is_mirrored) {
            printf("%s -- is not a palindrome.", input);
        } else if (is_palindrome && is_mirrored) {
            printf("%s -- is a mirrored palindrome.", input);
        } else if (is_palindrome) {
            printf("%s -- is a regular palindrome.", input);
        } else {
            printf("%s -- is a mirrored string.", input);
        }
    }
}