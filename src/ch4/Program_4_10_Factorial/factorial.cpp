// 2024/7/21
// zhangzhong

#include <cstdio>
#include <cstdlib>
#include <cstring>

int factorial(int n) {
    if (n == 0) {
        return 1;
    } else {
        return factorial(n - 1) * n;
    }
}

int main() { std::printf("%d\n", factorial(3)); }