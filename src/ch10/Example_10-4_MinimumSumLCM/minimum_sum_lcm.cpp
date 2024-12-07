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

std::vector<int> GetPrimes(int n) {

    std::vector<bool> not_prime((size_t)n + 4);

    // [[TIPS]]
    // 卧槽 这里会溢出
    // 不管是内层循环还是外层循环 都有可能溢出
    for (uint64_t i = 2; i * i <= (uint64_t)n; i++) {
        if (not_prime[i]) {
            continue;
        }

        for (uint64_t ki = i * i; ki <= (uint64_t)n; ki += i) {
            not_prime[ki] = true;
        }
    }

    std::vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (!not_prime[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}

void decompose(int n, std::vector<int>& decomposition,
               const std::vector<int>& primes) {
    for (int i = 0; n > 1 && i < primes.size(); i++) {
        while (n % primes[i] == 0) {
            n /= primes[i];
            decomposition[i]++;
        }
    }
}

uint64_t GetMinimumSumLCM(int n, const std::vector<int>& primes) {
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

    std::vector<int> decomposition(primes.size());
    decompose(n, decomposition, primes);

    uint64_t sum = 0;
    // 还要找到被分解出来的因子个数
    int factor_count = 0;
    for (int i = 0; i < primes.size(); i++) {
        if (decomposition[i] > 0) {
            factor_count++;
            sum += (uint64_t)std::pow(primes[i], decomposition[i]);
        }
    }

    if (factor_count < 2) {
        sum += 1;
    }
    return sum;
}

int main() {

    // std::vector<int> primes = GetPrimes(std::numeric_limits<int>::max());
    // 不对，题目中是说 最小公倍数是n 所以大概可能也不需要那么多素数
    // 10^6个顶天了
    std::vector<int> primes = GetPrimes(std::numeric_limits<int>::max());

    // std::cout << primes.size() << std::endl;

    int n = 0;
    int t = 1;
    while (std::cin >> n) {
        if (n == 0) {
            break;
        }

        uint64_t sum = GetMinimumSumLCM(n, primes);
        std::cout << "Case " << t << ": " << sum << "\n";
        t++;
    }
}