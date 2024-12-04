// 2024/12/4
// zhangzhong
// https://en.wikipedia.org/wiki/Pisano_period
// https://math.stackexchange.com/questions/631171/proof-that-fibonacci-sequence-modulo-m-is-periodic
// 有一些证明给出了序列重复一定会从01开始
// 所以hashmap不是必须的

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <unordered_map>

struct FibonacciPair {
    uint64_t f0;
    uint64_t f1;

    friend bool operator==(const FibonacciPair& lhs,
                           const FibonacciPair& rhs) noexcept {
        return lhs.f0 == rhs.f0 && lhs.f1 == rhs.f1;
    }
};

namespace std {
template <> struct hash<FibonacciPair> {
    size_t operator()(const FibonacciPair& fp) const noexcept {
        return std::hash<uint64_t>{}(fp.f0) ^ std::hash<uint64_t>{}(fp.f1);
    }
};
} // namespace std

uint64_t MulMod(uint64_t a, uint64_t b, int n) {
    return ((a % n) * (b % n)) % n;
}

uint64_t PowMod(uint64_t a, uint64_t b, int n) {
    if (b == 0) {
        return 1;
    }

    // 这里所有的乘法都可能会溢出 所以也要使用 MulMod
    uint64_t ans = PowMod(a, b / 2, n);
    // ans = ans * ans % n;
    ans = MulMod(ans, ans, n);
    if (b % 2 == 1) {
        // ans = ans * a % n;
        ans = MulMod(ans, a, n);
    }
    return ans;
}

int ColossalFibonacci(uint64_t a, uint64_t b, int n) {

    // 数组的长度定的太随意了
    // [[BUG]]
    // 数组的长度始终保持一致
    uint64_t fibonacci[n * n + 16];

    fibonacci[0] = 0;
    fibonacci[1] = 1;

    // TMD服了 pair没有hash
    // std::unordered_map<FibonacciPair, int> fib_pairs;
    // fib_pairs.insert({{0, 1}, 0});

    int i = 2;
    int repeated_index = -1;
    for (; i < n * n + 16; i++) {
        // 出现重复的意思 不一定从01开始重复吧
        // 所以我们需要把所有二元组(fi, fi+1)都存到hashmap中
        fibonacci[i] = (fibonacci[i - 1] + fibonacci[i - 2]) % n;

        // auto iter_ok =
        //     fib_pairs.insert({{fibonacci[i - 1], fibonacci[i]}, i - 1});
        // if (!iter_ok.second) {
        //     // 没有插入成功，说明pair已经存在
        //     repeated_index = iter_ok.first->second;
        //     break;
        // }
        // check if repeat with 0 and 1
        if (fibonacci[i] == 1 && fibonacci[i - 1] == 0) {
            break;
        }
    }

    // repeated_index always is 0
    repeated_index = 0;

    int repeat_count = i - 1 - repeated_index;
    uint64_t index = PowMod(a, b, repeat_count) + repeated_index;
    // [[BUG]]
    // 卧槽！种类出现了逻辑错误竟然也Accepted了
    // 我最后忘了 % n 了
    return fibonacci[index] % n;
}

int main() {
    int t = 0;
    std::cin >> t;

    while (t-- > 0) {
        uint64_t a = 0;
        uint64_t b = 0;
        int n = 0;
        std::cin >> a >> b >> n;

        int r = ColossalFibonacci(a, b, n);
        std::cout << r << "\n";
    }
}