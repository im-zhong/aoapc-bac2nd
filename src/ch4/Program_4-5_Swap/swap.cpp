// 2024/7/21
// zhangzhong

#include <cstdio>
#include <cstring>

void swap(int* a, int* b) {
    auto t = *a;
    *a = *b;
    *b = t;
}

int main(int argc, char* argv[]) {
    auto a = 3, b = 4;
    swap(&a, &b);
    std::printf("%d %d\n", a, b);
}