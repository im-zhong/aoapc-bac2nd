// 2024/11/15
// zhangzhong

#include <cmath>
#include <iostream>

int main() {
    int n = 0;

    while (std::cin >> n) {
        if (n == 0) {
            break;
        }

        int64_t labour = 0;
        int64_t a = 0;
        int64_t last = 0;
        for (int i = 0; i < n; i++) {
            std::cin >> a;

            last += a;
            labour += std::abs(last);
            // 最终last是零
        }
        std::cout << labour << "\n";
    }
}