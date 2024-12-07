// 2024/12/7
// zhangzhong

#include <bitset>
#include <cmath>
#include <iostream>
#include <vector>

std::vector<int> GetPrimes(int n) {
    // return [1, n] 中的所有素数

    // all is false, means all is prime
    // 用这个就会出错
    // std::bitset<1000000000 + 16> not_prime;

    // 用这个就ok
    std::vector<bool> not_prime(n + 16);

    for (int p = 2; p * p <= n; p++) {
        if (not_prime[p]) {
            continue;
        }

        // all 2p 3p 4p ... <= n 的 都不是素数
        for (int kp = 2 * p; kp <= n; kp += p) {
            not_prime[kp] = true;
        }
    }

    // finally traverse the not_prime, collect the primes
    std::vector<int> primes;
    for (int p = 2; p <= n; p++) {
        if (!not_prime[p]) {
            primes.push_back(p);
        }
    }

    return primes;
}

void decompose(int n, int k, std::vector<int>& decompostion,
               const std::vector<int> primes) {

    // 这一部分包装成一个函数
    // 这一部分本质上就是将某个整数进行唯一分解
    // n >= 2 才能进行分解 TODO：如果n是1 该怎么办呢？
    for (int j = 0; n > 1 && j < primes.size(); j++) {
        int prime = primes[j];

        while (n % prime == 0) {
            n /= prime;
            decompostion[j] += k;
        }
    }
}

void fractoril(int p, int k, std::vector<int>& decompostion,
               const std::vector<int> primes) {

    // 我们要求 p!

    // 对于1和零要特殊考虑，因为最小的素数是二 他没法分解0和1
    for (int i = 2; i <= p; i++) {
        decompose(i, k, decompostion, primes);
    }
}

double solve(int p, int q, int r, int s, const std::vector<int>& primes) {

    int prime_count = primes.size();
    std::vector<int> decomposition(prime_count);

    fractoril(p, 1, decomposition, primes);
    fractoril(p - q, -1, decomposition, primes);
    fractoril(q, -1, decomposition, primes);
    fractoril(r, -1, decomposition, primes);
    fractoril(r - s, 1, decomposition, primes);
    fractoril(s, 1, decomposition, primes);

    // 最终把decompostion变成浮点数即可
    double ans = 1;
    // 哦 卧槽！ 可以处理1 因为如果所有的decomposition都是零 那么结果就是1
    for (int i = 0; i < prime_count; i++) {
        ans *= std::pow(primes[i], decomposition[i]);
    }
    return ans;
}

int main() {

    // std::cout << "hello, world!\n";

    // test GetPrimes
    // std::vector<int> primes = GetPrimes(100);
    // for (int prime : primes) {
    //     std::cout << prime << " ";
    // }
    // std::cout << std::endl;

    // [[TIP]]
    // 留意数值的范围，我们是对数值更小的pqrs进行分解，最大值时10000
    // 所以只需要求10000以内的素数即可
    std::vector<int> primes = GetPrimes(10000);

    int p = 0;
    int q = 0;
    int r = 0;
    int s = 0;
    while (std::cin >> p >> q >> r >> s) {
        double ans = solve(p, q, r, s, primes);
        std::printf("%.5f\n", ans);
    }
}