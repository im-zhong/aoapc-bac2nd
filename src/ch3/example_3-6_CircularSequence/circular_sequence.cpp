// 2024/7/21
// zhangzhong

#include <cstdio>
#include <cstring>
using namespace std;

char input[128] = "\0";

int main(int argc, char* argv[]) {
    int lines = 0;
    scanf("%d", &lines);

    for (int i = 0; i < lines; i++) {
        scanf("%s", input);
        int len = strlen(input);

        // duplicate this string
        memcpy(input + len, input, len);

        char* p_min = input;
        for (int i = 1; i < len; i++) {
            if (strncmp(p_min, input + i, len) > 0) {
                p_min = input + i;
            }
        }

        *(p_min + len) = '\0';
        printf("%s\n", p_min);
    }
}
