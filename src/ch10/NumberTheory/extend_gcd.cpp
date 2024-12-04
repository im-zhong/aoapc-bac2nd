// 2024/12/3
// zhangzhong
// https://zh.wikipedia.org/zh-cn/%E6%89%A9%E5%B1%95%E6%AC%A7%E5%87%A0%E9%87%8C%E5%BE%97%E7%AE%97%E6%B3%95
// 其中的python实现可以理解

#include <cmath>
#include <iostream>

struct GCD {
    int a;
    int x;
    int y;
};

// 这个是解决的 ax + by = gcd(a, b)
GCD extend_gcd_impl(int a, int b, int x, int x1, int y, int y1) {
    if (b == 0) {
        return GCD{a, x, y};
    } else {
        int q = a / b;
        return extend_gcd_impl(b, a % b, x1, x - q * x1, y1, y - q * y1);
    }
}

// 我们还需要一个函数来开始调用本函数
// 可以解决 ax + by = a mod b
GCD extend_gcd(int a, int b) { return extend_gcd_impl(a, b, 1, 0, 0, 1); }

// 数论比我想象的要难，只学一些最重要最常见的东西吧，不要在这上面花费太多时间

// 我们要用extend gcd 来解决 ax + by + c = 0
// 的问题，因为只要找出了一组解，剩下的解都可以根据公式得到
// 所以咱们实现一个函数，就是为了找到上述方程的某一个整数解 即可

struct Point {
    int x;
    int y;
};

Point LineEquation(int a, int b, int c) {

    GCD gcd = extend_gcd(a, b);
    if (std::abs(c) % gcd.a != 0) {
        return {};
    }

    // 我们拿到了方程 ax + by = gcd(a, b) = r的一组解 (x0, y0)
    int k = -c / gcd.a;
    // 方程两边同时乘以k
    // a(kx) + b(ky) = kr = -c
    // 所以 (kx0, ky0) 就是方程的一个解

    return {k * gcd.x, k * gcd.y};
}

// 闭区间
struct Interval {
    int left;
    int right;
};

Interval Intersect(Interval i1, Interval i2) {
    // 两者按照left 从小到大排序
    if (i1.left > i2.left) {
        std::swap(i1, i2);
    }
    return Interval{std::max(i1.left, i2.left), std::min(i1.right, i2.right)};
}
