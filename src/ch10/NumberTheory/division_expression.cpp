// 2024/12/3
// zhangzhong

#include <cstdint>
#include <iostream>
#include <sys/types.h>

// C++17 标准库添加了gcd

// 除法表达式
// Xi > 0 正整数
// X1 / X2 / ... / Xk
// 判断是否可以通过添加括号，使表达式的值为整数

uint64_t gcd(uint64_t a, uint64_t b) { return b == 0 ? a : gcd(b, a % b); }

// 这里有一个问题，万一gcd返回的是0呢？
// gcd返回零只有一种可能，a == b == 0
uint64_t lcm(uint64_t a, uint64_t b) { return a / gcd(a, b) * b; }

bool Judge(uint64_t* nums, int n) {
    // 假设下标从1开始 一直到N
    nums[2] /= gcd(nums[2], nums[1]);

    for (int i = 3; i <= n; i++) {
        nums[2] /= gcd(nums[2], nums[i]);
    }
    return nums[2] == 1;
}