// 2024/7/26
// zhangzhong

#include <cstdio>
#include <cstring>

char test[128] = "\0";

int main() {
    int lines = 0;
    scanf("%d", &lines);

    for (int _ = 0; _ < lines; _++) {
        int total_score = 0;
        int accumulated_score = 0;

        scanf("%s", test);
        for (char* p = test; *p; p++) {
            if (*p == 'O') {
                ++accumulated_score;
            } else {
                accumulated_score = 0;
            }
            total_score += accumulated_score;
        }
        printf("%d\n", total_score);
    }
}