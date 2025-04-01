// 2025/4/1
// zhangzhong

// If the value of mantissa
// is mthen it maintains the constraints 1
// 2 ≤m<1. The left most digit of mantissa must always be 1 to
// maintain the constraint 1
// 2 ≤m<1. So this bit is not stored as it is always 1

// 咱们先用不是高精度的方法进行处理
// 如果不行的话就看答案
// 多看看答案 自己想比较慢

#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <unordered_map>

// E = [1, 30]
// 算了，计算这个东西应该是很快的，咱们还是不打表了
// no，这个弄不了，因为指数位可能有32个bit，这个是都double肯定存储不了的
// 咱们写的这个只适用于能存储在double类型里面的计算

// 看了一下答案，可以用log
// 因为指数太大，肯定是没法放在double里面的
// 所以我们把尾数和指数分开村
// 指数的精度应该也是可以存放在double里面的
// 我们首先把 10^B -> 2^X
// 通过对数运算

std::unordered_map<uint32_t, int> e2bit;
int exponents[32];
double m2bit[10];
double log2m[10];

std::pair<int, int> GetMandE(double A, int B) {

    double number = std::log2(10) * B + std::log2(A);

    // e 可以直接被确定
    // 将number做向上取整

    // 我们要确保number本身不是特别靠近某个整数
    // 我们直接特判一下吧
    // 因为在这种情况下 m = 0
    // 循环判断一下
    for (int e = 1; e <= 30; e++) {
        int exp = exponents[e];
        double x = log2m[0] + exp;
        if (std::abs(x - number) < 1e-6) {
            return {0, e};
        }
    }

    // 否则e可以直接被确定，一定是向上取整
    int exp = std::ceil(number);
    // 然后遍历m 找到最近的
    for (int m = 0; m < 10; m++) {
        if (std::abs(log2m[m] + exp - number) < 1e-6) {
            return {m, e2bit[exp]};
        }
    }

    // // 最终 number = [1/2, 1)
    // //

    // // 不对 我们求出来的e是 1111111
    // // 我们需要把他们转换成位数
    // // 这里我选择直接打表
    // // 并不是，我们这里是反过来
    // // 所以我们需要一个hashmap

    // // 一般指数可以估计的比较准确
    // // 但是尾数肯定会伴随着精读损失
    // // 这时候我们就需要估计了
    // assert(number >= 0.5);
    // // 我们把这个位数转成整数来保存吧
    // // 然后和最近的整数进行比较？
    // // 假设m = 9
    // // 则尾数应该等于 0.111111111(2)
    // // x2 - 1
    // // 直到等于1 就结束了
    // int m = 0;
    // while (number > m2bit[m]) {
    //     m++;
    // }

    // return {m, e2bit[e]};
    // return {0, e};
    assert(false);
}

int main(int argc, char* argv[]) {

    // calculate exponents
    for (int e = 1; e <= 30; e++) {
        exponents[e] = (1 << e) - 1;
        e2bit[exponents[e]] = e;
    }

    // 制作一张表，表示
    // 这次咱们用遍历的就行了，以为有精读损失 没有办法精确匹配

    m2bit[0] = 1.0 / 2;
    for (int i = 1; i < 10; i++) {
        // m = 0
        // 零位，我们也表示 0.1 = 2^-1 = 1/2
        m2bit[i] = m2bit[i - 1] / 2;
    }
    for (int i = 1; i < 10; i++) {
        m2bit[i] += m2bit[i - 1];
    }
    for (int i = 0; i < 10; i++) {
        log2m[i] = std::log2(m2bit[i]);
    }

    std::string number;

    while (std::cin >> number) {
        if (number == "0e0") {
            break;
        }

        int pos = number.find('e');
        std::string Astr(number.substr(0, pos));
        std::string Bstr(number.substr(pos + 1));

        // 0 < A < 10
        // 而且一定是小数
        // 1.xxx

        // 咱们可以处理一下这个A 我们主动的把小数点向后移一位
        // 这样可以保证有效位数不会超过double的范围
        double A = std::atof(Astr.c_str());
        int B = std::atoi(Bstr.c_str());

        auto pair = GetMandE(A, B);
        std::cout << pair.first << " " << pair.second << "\n";
    }
}