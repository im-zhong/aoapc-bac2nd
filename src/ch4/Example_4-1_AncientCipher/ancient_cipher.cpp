// 2024/7/21
// zhangzhong

#include <cstdio>
#include <cstdlib>
#include <cstring>

const int maxn = 128;
char str1[maxn] = "\0";
char str2[maxn] = "\0";

int str1_chars[26] = {};
int str2_chars[26] = {};

int main(int argc, char* argv[]) {

    while (std::scanf("%s%s", str1, str2) == 2) {

        std::memset(str1_chars, 0, sizeof(str1_chars));
        std::memset(str2_chars, 0, sizeof(str2_chars));

        for (int i = 0; i < std::strlen(str1); i++) {
            str1_chars[str1[i] - 'A'] += 1;
        }
        for (int i = 0; i < std::strlen(str2); i++) {
            str2_chars[str2[i] - 'A'] += 1;
        }

        // 然后我们把两个数组进行排序
        std::qsort(str1_chars, 26, sizeof(int),
                   [](const void* lhs, const void* rhs) -> int {
                       return *(int*)(lhs) - *(int*)(rhs);
                   });
        std::qsort(str2_chars, 26, sizeof(int),
                   [](const void* lhs, const void* rhs) -> int {
                       return *(int*)(lhs) - *(int*)(rhs);
                   });
        // then we check if these two array is the same
        bool is_same = true;
        for (int i = 0; i < 26; i++) {
            if (str1_chars[i] != str2_chars[i]) {
                is_same = false;
                break;
            }
        }
        std::printf(is_same ? "YES\n" : "NO\n");
    }
}