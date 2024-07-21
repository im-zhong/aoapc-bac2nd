// 2024/7/21
// zhangzhong

#include <cstdint>
#include <cstdio>
#include <cstring>

double factorial(int n) {
    double answer = 1;
    for (int i = 1; i <= n; i++) {
        answer *= i;
    }
    return answer;
}

double combinatorial_number(int n, int m) {
    if (m < n - m) {
        m = n - m;
    }

    double answer = 1.0;
    for (int i = m + 1; i <= n; i++) {
        answer *= i;
    }
    for (int i = 1; i <= n - m; i++) {
        answer /= i;
    }
    return answer;
}

int main(int argc, char* argv[]) {
    auto n = 0, m = 0;
    std::scanf("%d%d", &n, &m);
    std::printf("%lld\n", static_cast<uint64_t>(combinatorial_number(n, m)));
}