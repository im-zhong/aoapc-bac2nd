// 2024/7/21
// zhangzhong

#include <cstdio>
#include <cstring>

char input[256] = "\0";

int main(int argc, char* argv[]) {
    while (std::scanf("%s", input) == 1) {
        int len = std::strlen(input);

        // duplicate this string
        std::memcpy(input + len, input, len);

        char* p_min = input;
        for (int i = 1; i < len; i++) {
            if (std::strncmp(p_min, input + i, len) > 0) {
                p_min = input + i;
            }
        }

        *(p_min + len) = '\0';
        std::printf("%s\n", p_min);
    }
}
