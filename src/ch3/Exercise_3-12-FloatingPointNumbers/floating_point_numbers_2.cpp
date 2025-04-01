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
#include <cstdint>
#include <iostream>
#include <unordered_map>

// E = [1, 30]
// 算了，计算这个东西应该是很快的，咱们还是不打表了
// no，这个弄不了，因为指数位可能有32个bit，这个是都double肯定存储不了的
// 咱们写的这个只适用于能存储在double类型里面的计算

std::unordered_map<uint32_t, int> e2bit;
double m2bit[12];

std::pair<int, int> GetMandE(double number) {

    int e = 0;
    while (number > 1) {
        number /= 2;
        e += 1;
    }

    // 最终 number = [1/2, 1)
    //

    // 不对 我们求出来的e是 1111111
    // 我们需要把他们转换成位数
    // 这里我选择直接打表
    // 并不是，我们这里是反过来
    // 所以我们需要一个hashmap

    // 一般指数可以估计的比较准确
    // 但是尾数肯定会伴随着精读损失
    // 这时候我们就需要估计了
    assert(number >= 0.5);
    // 我们把这个位数转成整数来保存吧
    // 然后和最近的整数进行比较？
    // 假设m = 9
    // 则尾数应该等于 0.111111111(2)
    // x2 - 1
    // 直到等于1 就结束了
    int m = 0;
    while (number > m2bit[m]) {
        m++;
    }

    return {m, e2bit[e]};
}

int main(int argc, char* argv[]) {

    // 初始化 e2bit
    for (int i = 0; i < 32; i++) {
        e2bit[(1 << i) - 1] = i;
    }

    // 制作一张表，表示
    // 这次咱们用遍历的就行了，以为有精读损失 没有办法精确匹配

    m2bit[0] = 1.0 / 2;
    for (int i = 1; i < 12; i++) {
        // m = 0
        // 零位，我们也表示 0.1 = 2^-1 = 1/2
        m2bit[i] = m2bit[i - 1] / 2;
    }
    for (int i = 1; i < 12; i++) {
        m2bit[i] += m2bit[i - 1];
    }

    double number = 0;
    while (std::cin >> number) {
        if (number == 0) {
            break;
        }

        auto pair = GetMandE(number);
        std::cout << pair.first << " " << pair.second << "\n";
    }
}