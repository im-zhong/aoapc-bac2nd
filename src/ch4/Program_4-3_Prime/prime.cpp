// 2024/7/21
// zhangzhong

#include <cmath>
#include <cstdio>
#include <cstring>

bool is_prime(int n) {
    if (n <= 1) {
        return false;
    }

    int m = std::floor(std::sqrt(n) + 0.5);
    // for (int i = 2; i < std::sqrt(n); i++) {
    // for (int i = 2; i * i <= n; i++) {
    for (int i = 2; i <= m; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    int n = 0;
    std::scanf("%d", &n);
    std::printf(is_prime(n) ? "yes\n" : "no\n");
}