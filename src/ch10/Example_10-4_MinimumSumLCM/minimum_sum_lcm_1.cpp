// 2024/12/7
// zhangzhong

#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

// 卧槽，
// https://github.com/aoapc-book/aoapc-bac2nd/blob/master/ch10/UVa10791.cpp
// 简直太妙了
// 这道题目的困境在于，输入的数很大 n = 2^31-1，求这么大范围的素数会超时
// 但是这道题目实际上不需要求出所有素数
// 注意到solve代码中，代码只有一个for循环，来遍历 2 .. sqrt(n)
// 为什么这样可以找到所有的素数因子呢
// 因为我们会把所有的 2^k 3^k 都给除掉
// 假设我们i=2结束了，之后所有的2p都不可能取模得零，这其实就是素数筛！

// void decompose(int n, std::vector<int>& decomposition) {
//     for (int i = 0; n > 1 && i < primes.size(); i++) {
//         while (n % primes[i] == 0) {
//             n /= primes[i];
//             decomposition[i]++;
//         }
//     }
// }

uint64_t GetMinimumSumLCM(uint64_t n) {
    if (n == 1) {
        // 1 + 1 = 2
        return 2;
    }

    // 直接将n进行一个唯一分解
    // 但是这里的n很大 我们光是求解素数就会花掉很多时间
    // 这道题比上一刀题还简单
    // 如果求解素数太花时间
    // 有一个办法是先把所有素数求出来
    // 然后hard coded到代码中

    // std::vector<int> decomposition(primes.size());
    // decompose(n, decomposition, primes);

    uint64_t sum = 0;
    // 还要找到被分解出来的因子个数
    int factor_count = 0;

    // [[BUG]]
    // 我们修改了n 但是这里循环条件里的n不应该被修改
    const int N = n;
    // 代码是没错的，但是遍历不完
    // 这里也不是小于

    for (uint64_t p = 2; n > 1 && p * p <= N; p++) {
        if (n % p == 0) {
            factor_count++;
            // new prime
            // 我们不需要把这些素数保存下来
            // 我们一遍计算prime因子 一边计算和sum即可

            // 对于每个素数因子
            // 我们要一直除，知道无法除尽
            int k = 0;
            while (n % p == 0) {
                n /= p;
                k++;
            }
            // TMD 忘了 k可能是零
            if (k > 0) {
                sum += (uint64_t)std::pow(p, k);
            }
        }
    }

    // [[TIP]]
    // 判断素数只需要到sqrt(n)
    // 但是存在一种情况，就是n本身是一个大素数
    // 那么我们上述流程走完之后，不会找到任何素数因子
    if (n > 1) {
        // 这就以为着n本身是一个大素数
        factor_count++;
        sum += n;
    }

    // for (int i = 0; i < primes.size(); i++) {
    //     if (decomposition[i] > 0) {
    //         factor_count++;
    //         sum += (uint64_t)std::pow(primes[i], decomposition[i]);
    //     }
    // }

    if (factor_count < 2) {
        sum += 1;
    }
    return sum;
}

int main() {

    int n = 0;
    int t = 1;
    while (std::cin >> n) {
        if (n == 0) {
            break;
        }

        uint64_t sum = GetMinimumSumLCM(n);
        std::cout << "Case " << t << ": " << sum << "\n";
        t++;
    }
}