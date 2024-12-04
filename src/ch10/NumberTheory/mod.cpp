// 2024/12/4
// zhangzhong
// 同余与模算术
// 模算术
// (a + b) mod n = ((a mod n) + (b mod n)) mod n
// (a * b) mod n = ((a mod n) * (b mod n)) mod n
// (a - b) mod n = ((a mod n) - (b mod n) + n) mod n, 因为 (a mod n) - (b mod n)
// 可能小于零，+n对 mod n的结果不会产生影响
// 其实任何的线性运算 a*b + c 都可以应用上述公式 这就是模算术
// 模算术在计算一些可能溢出的数值时 非常有用
// 比如计算大数乘法

#include <cstdint>
#include <iostream>

int mul_mod(int a, int b, int n) { return ((a % n) * (b % n)) % n; }

// 大整数取模
// abcd = ((a*10 + b)*10 + c)*10 + d
uint64_t big_int_mod(uint64_t* bits, int n, int m) {
    uint64_t ans = 0;
    for (int i = 0; i < n; i++) {
        ans = (ans * 10 + bits[i]) % m;
    }
    return ans % m;
}

// 大幂取模
// a^b % m
uint64_t pow_mod(int a, int b, int m) {
    // 最简单的O(n)算法
    uint64_t ans = 1;
    for (int i = 0; i < b; i++) {
        ans = (ans * a) % m;
    }
    return ans % m;
}

// 使用二分递归 O(logn)
uint64_t pow_mod2(int a, int b, int m) {
    // 递归结束条件
    if (b == 0) {
        // a^0 = 1
        return 1;
    }

    int ans = pow_mod2(a, b / 2, m);

    // b可能是奇数，/2会导致少算一次幂
    if (b % 2 == 0) {
        return (ans * ans) % m;
    } else {
        ans = (ans * ans) % m;
        ans = (ans * a) % m;
        return ans;
    }
}