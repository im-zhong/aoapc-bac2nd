// 2024/8/8
// zhangzhong

// 先实现一个函数可以返回一个整数的所有因子
// 然后实现一个函数判断某个数是否是素数，可以使用一个hashmap来加速判断
// 对于已经判断过的整数，我们保存其结果即可
// 可以保存一个
// 这个题遍历数字进行计算非常慢，或许可以考虑构造法？

#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

#define range(c) c.begin(), c.end()

auto primes = std::unordered_map<int, bool>{{1, false}};

bool is_prime(int n) {
    auto r = primes.find(n);
    if (r != primes.end()) {
        return r->second;
    }

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            primes.insert({n, false});
            return false;
        }
    }
    primes.insert({n, true});
    return true;
}

// 把所有因子都计算出来太费时间了
// 只要我们在计算的时候 碰到不是 2 3 5 的素数，直接判断false即可
auto get_all_factors(int n) -> std::vector<int> {
    auto factors = std::vector<int>{};
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);
            factors.push_back(n / i);
        }
    }
    std::sort(range(factors));
    //  std::unique reorders the elements in the range and returns an iterator
    //  to the new end of the range. You need to resize the vector to remove the
    //  duplicates
    auto last = std::unique(range(factors));
    factors.erase(last, factors.end());
    return factors;
}

bool is_ugly(int factor) { return (factor == 2 || factor == 3 || factor == 5); }

// int main() {
//     // 这种题目岂不是可以线下算出来 然后直接一个print吗？
//     auto ugly_numbers = std::vector<int>{1};
//     for (int i = 2; ugly_numbers.size() <= 1500; i++) {
//         auto factors = get_all_factors(i);

//         bool is_ugly_number = true;
//         for (auto factor : factors) {
//             if (is_prime(factor)) {
//                 // only 2, 3, 5 should be ok
//                 if (!(factor == 2 || factor == 3 || factor == 5)) {
//                     // then this number is not ugly number
//                     // break and try another number
//                     is_ugly_number = false;
//                     break;
//                 }
//             }
//         }
//         if (is_ugly_number) {
//             ugly_numbers.push_back(i);
//             std::cout << ugly_numbers.size() << ": " << i << std::endl;
//         }
//     }
// }

// int main() {
//     auto ugly_numbers = std::vector<int>{1};

//     for (int n = 2; ugly_numbers.size() <= 1500; n++) {
//         // get all factors
//         bool is_ugly_number = true;
//         for (int f = 1; f * f <= n; f++) {
//             if (n % f == 0) {
//                 if (is_prime(f)) {
//                     if (!is_ugly(f)) {
//                         is_ugly_number = false;
//                         break;
//                     }
//                 }
//                 if (is_prime(n / f)) {
//                     if (!is_ugly(n / f)) {
//                         is_ugly_number = false;
//                         break;
//                     }
//                 }
//             }
//         }
//         if (is_ugly_number) {
//             ugly_numbers.push_back(n);
//             std::cout << ugly_numbers.size() << ": " << n << std::endl;
//         }
//     }
// }

// auto ugly_numbers = std::unordered_map<uint64_t, bool>{
//     {1, true},
// };

auto ugly_numbers = std::vector<bool>{true};

// bool is_ugly_number_impl(uint64_t n) {

//     // if seen, just return
//     // if not seen
//     // 关键的是我们没见过的数字
//     // 那只能分解因子啊
//     for (uint64_t f = 1; f * f <= n; f++) {
//         // 关键是分解的时候我们还是可能碰到见过的因子啊
//         // 递归啊，最关键的是递归结束条件是什么？
//         // 递归的结束条件就是我们的因子是一个素数，但是不是 2 3 5
//         if (n % f != 0) {
//             continue;
//         }

//         uint64_t f1 = f, f2 = n / f;

//         // 还有就是碰到一个不是丑书的因子
//         if ()

//             if (is_prime(f1) && !is_ugly(f1)) {
//                 return false;
//             }
//     }
// }

bool is_ugly_number(uint64_t n) {
    // if (n <= max_seen_number) {
    //     // 如果n是我们已经见过的数字，那么我们一定可以通过查表查到n是不是丑书
    //     return ugly_numbers.find(n) != ugly_numbers.end();
    // }

    if (n <= ugly_numbers.size()) {
        return ugly_numbers[n - 1];
    }

    // 卧槽！不对呀，我直接判断tm的这个整数能不能被 2 3 5
    // 整除的同时，不能被其他质数整除不久行了吗？

    // 我懂了，原因在这里，
    // 分解大整数太慢了，哪怕只是找到第一个因子都非常慢！！
    // 怎么
    for (uint64_t f = 1; f * f <= n; f++) {
        if (n % f != 0) {
            continue;
        }

        uint64_t f1 = f, f2 = n / f;
        if (f1 == n) {
            if (is_prime(f1) && !is_ugly(f1)) {
                return false;
            }
        } else {
            if (!ugly_numbers[f1 - 1]) {
                return false;
            }
            // if (!is_ugly_number(f1)) {
            //     return false;
            // }
        }
        if (f2 == n) {
            if (is_prime(f2) && !is_ugly(f2)) {
                return false;
            }
        } else {
            // if (!is_ugly_number(f2)) {
            //     return false;
            // }
            if (!ugly_numbers[f2 - 1]) {
                return false;
            }
        }

        // 不对的，我们不需要等待所有因子都判断结束
        //
        if (f1 != n && f2 != n) {
            return true;
        }

        // 本质上我们只需要判断因子是不是丑数
        // 也就是说这个函数是递归的
        // 我们如果直接使用一个hashmap来保存所有的数是不是丑书的话
        // 编程会非常简单 只不过会使用很多内存

        // if (f1 <= max_seen_number) {
        //     // 如果我没没有找到丑书 直接返回错误
        //     if (ugly_numbers.find(f1) == ugly_numbers.end()) {
        //         return false;
        //     } else {
        //         // 如果找到了呢？我们也不能保证这是丑书
        //     }
        // } else {
        //     // 如果是一个我们没见过的数，我们就需要走素数判断了
        //     // 如果是素数我们才需要判断，否则不需要
        //     if (is_prime(f1)) {
        //         if (!is_ugly(f1)) {
        //             return false;
        //         }
        //     }
        // }

        // f2 也是一样的判断方法 应该抽取出一个函数
    }

    // 如果最终都没有return false 那么这就是一个丑书
    return true;
}

int main() {
    int ugly_number_count = 1;
    for (int n = 2; ugly_number_count <= 1500; n++) {
        // 对于 每个数字 我们都判断是不是丑书
        // 然后保存到丑书set中
        // 即然如此 我们为什么不用一个vector呢?
        if (is_ugly_number(n)) {
            ugly_number_count++;
            ugly_numbers.push_back(true);
            std::cout << ugly_number_count << ": " << n << std::endl;
        } else {
            ugly_numbers.push_back(false);
        }
    }
}
