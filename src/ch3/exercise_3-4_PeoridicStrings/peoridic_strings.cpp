// 2024/7/28
// zhangzhong

#include <cstdio>
#include <cstring>

using namespace std;

char line[128] = "";

int main() {
    int test_case_count = 0;
    scanf("%d", &test_case_count);

    for (int _ = 0; _ < test_case_count; _++) {
        scanf("%s", line);

        int len = strlen(line);
        for (int period = 1; period <= len; period++) {
            // check if the whole line is of period
            // TODO: 或者KMP算法的思想可以应用在这里？
            char* p = line;
            bool is_periodic = true;

            for (int i = 0; i < len; i += period) {
                // 判断最开始的字符串和period的字符串是否相等
                // 只要有一处不想等，就不是

                if (strncmp(p, p + i, period) != 0) {
                    is_periodic = false;
                    break;
                }
            }
            if (is_periodic) {
                printf("%d\n", period);
                break;
            }
        }
        if (_ != test_case_count - 1) {
            printf("\n");
        }
    }
}
