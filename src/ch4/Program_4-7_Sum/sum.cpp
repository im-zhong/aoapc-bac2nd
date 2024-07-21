// 2024/7/21
// zhangzhong

#include <cstdio>
#include <cstring>

int sum(int* a, int n) {
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += a[i];
    }
    return ans;
}

int sum(int* begin, int* end) {
    int ans = 0;
    for (; begin != end; ++begin) {
        ans += *begin;
    }
    return ans;
}

int main(int argc, char* argv[]) {
    int a[] = {1, 2, 3, 4};
    std::printf("%d\n", sum(a + 1, 3));
}