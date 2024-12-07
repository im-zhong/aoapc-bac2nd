// 2024/12/7
// zhangzhong

#include <cstdint>
#include <iostream>

// [[TIP]]
// 果然不出我所料
// 这道题目实际上只需要计算出最大的一个值即可
// 因为很明显我们会重复计算，每个case都相当于一个子问题
// 这是一个加速的点

// 还有一个就是约数筛

constexpr int maxn = 30000000;
uint64_t sums[maxn + 1];
uint64_t cnts[maxn + 1];

uint64_t gcd(uint64_t a, uint64_t b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

bool CheckGCDXOR(uint64_t a, uint64_t c) {
    // uint64_t b = a ^ c;

    uint64_t b = a - c;
    if (b > a) {
        return false;
    }
    if (b < 1) {
        return false;
    }

    // return gcd(a, b) == (a ^ b);
    return c == (a ^ b);
}

void init() {
    // 求的所有maxn的
    for (int c = 1; c <= maxn; c++) {
        // 筛
        // 在这里 a就是solve(n) 因为c是a的约数
        for (int a = c; a <= maxn; a += c) {

            // 如果我们想要solve(n)
            // sum(1, 2, 3, ... n)
            // 所以我们只需要把以a开头的都保存在a的位置，就可以O(n)遍历得到所有结果
            // 之后就是O(1)的查询即可

            if (CheckGCDXOR(a, c)) {
                cnts[a]++;
            }
        }
    }

    for (int i = 1; i <= maxn; i++) {
        sums[i] = sums[i - 1] + cnts[i];
    }
}

uint64_t GetPairCount(uint64_t n) {

    // std::vector<std::pair<int, int>> pairs;

    uint64_t pc = 0;
    for (uint64_t a = 1; a <= n; a++) {

        // 遍历所有的c
        // 试除法用起来不行 太慢了
        // 要不用筛法
        // 都很慢
        for (uint64_t c = 1; c * c <= a; c++) {

            if (a % c == 0) {
                uint64_t c1 = c;
                uint64_t c2 = a / c;

                if (c1 == c2) {
                    // only one factor
                    if (CheckGCDXOR(a, c1)) {
                        pc++;
                        // pairs.push_back({a, a ^ c1});
                    }

                } else {
                    // two both is factor
                    if (CheckGCDXOR(a, c1)) {
                        pc++;
                        // pairs.push_back({a, a ^ c1});
                    }
                    if (CheckGCDXOR(a, c2)) {
                        pc++;
                        // pairs.push_back({a, a ^ c2});
                    }
                }
            }
        }
    }

    // for (auto pair : pairs) {
    //     std::cout << pair.first << ", " << pair.second << std::endl;
    // }

    return pc;
}

int main() {

    init();

    int test_count = 0;
    std::cin >> test_count;

    for (int t = 1; t <= test_count; t++) {

        int n = 0;
        std::cin >> n;
        uint64_t pair_count = sums[n];

        std::cout << "Case " << t << ": " << pair_count << "\n";
    }
}