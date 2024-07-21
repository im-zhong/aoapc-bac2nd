// 2024/7/21
// zhangzhong

#include <cstdio>
#include <cstring>

int main(int argc, char* argv[]) {
    int n = 0;
    while (std::scanf("%d", &n) == 1 && n != 0) {
        bool found = false;
        for (int i = 1; i < n; i++) {
            int sum = i;
            int m = i;
            while (m) {
                sum += (m % 10);
                m /= 10;
            }

            if (sum == n) {
                std::printf("%d\n", i);
                found = true;
                break;
            }
        }
        if (!found) {
            std::printf("0\n");
        }
    }
}
