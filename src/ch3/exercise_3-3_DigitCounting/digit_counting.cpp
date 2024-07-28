// 2024/7/28
// zhangzhong

#include <cstdio>
#include <cstring>
using namespace std;

int digit_count[10] = {};

int main() {
    int test_case_count = 0;
    scanf("%d", &test_case_count);

    for (int _ = 0; _ < test_case_count; _++) {
        int number = 0;
        scanf("%d", &number);

        memset(digit_count, 0, sizeof(digit_count));
        for (int i = 1; i <= number; i++) {
            int temp = i;
            while (temp) {
                digit_count[(temp % 10)]++;
                temp /= 10;
            }
        }

        for (int i = 0; i < 10; i++) {
            printf("%d", digit_count[i]);
            if (i != 9) {
                printf(" ");
            }
        }
        printf("\n");
    }
}