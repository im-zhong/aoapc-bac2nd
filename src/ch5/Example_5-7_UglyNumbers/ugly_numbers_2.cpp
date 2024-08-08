// 2024/8/8
// zhangzhong

#include <cstdint>
#include <iostream>
#include <set>
#include <unordered_set>

// 难道是set太慢了？不对啊，素数密度很低的啊？
// 哦 我们都是一只按照一个顺序进行插入的，会导致不平衡
// 用unordered_set应该会好一点
auto primes = std::unordered_set<uint64_t>{};
auto max_seen_number = 6;

bool is_prime(int n) {
    // auto r = primes.find(n);
    // if (r != primes.end()) {
    //     return r->second;
    // }

    bool is = true;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            is = false;
            break;
        }
    }
    if (is) {
        primes.insert(n);
    }
    return true;
}

bool is_ugly_number(uint64_t n) {

    // 对于每一个数，我们首先判断是不是素数
    // 因为我们对素数的判断是持续增长的，所以不需要使用map来记录
    // 一个set + max unseen number 即可

    // 为什么 这么慢？
    // 和之前一样啊 也是相当于每个数都要判断一下是不是素数
    is_prime(n);

    for (auto prime : primes) {
        if (n % prime == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    // 首先找到所有小于该数的所有质数 > 5 < n
    // 然后遍历这些质数 只要能被整除，就不是丑书

    // 因为我们已经知道前几个丑书了，我们直接从6开始计算
    //
    auto ugly_number_count = 5;
    for (uint64_t n = 6; ugly_number_count <= 1500; n++) {
        if (is_ugly_number(n)) {
            ugly_number_count++;
            std::cout << ugly_number_count << ": " << n << std::endl;
        }
    }
}