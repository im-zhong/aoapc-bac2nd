// 2024/10/25
// zhangzhong

#include <cstdint>
#include <iostream>
#include <vector>

struct Fraction {
    uint64_t x;
    uint64_t y;
};

class FractionDecompositor {

  public:
    FractionDecompositor(uint64_t k) : k_{k} {}

    std::vector<Fraction> Decompose() {

        auto fractions = std::vector<Fraction>{};

        for (uint64_t y = this->k_ + 1;; y += 1) {
            // 当最开始的我们就比较大时就停止吧
            if (y * y > this->k_ * (y + y)) {
                break;
            }

            // 不对，这是一个关系式，意味着，我们是可以直接把x计算出来的，而不是还得枚举出来
            // 现在这样枚举显然是慢一些的
            // for (uint64_t x = y;; x += 1) {
            //     if (x * y < this->k_ * (x + y)) {
            //         continue;
            //     } else if (x * y == this->k_ * (x + y)) {
            //         fractions.push_back(Fraction{x, y});
            //         break;
            //     } else {
            //         break;
            //     }
            // }
            if ((this->k_ * y) % (y - this->k_) == 0) {
                fractions.push_back(
                    Fraction{(this->k_ * y) / (y - this->k_), y});
            }
        }

        return fractions;
    }

  private:
    uint64_t k_;
};

int main() {

    uint64_t k = 0;
    while (std::cin >> k) {

        auto fd = FractionDecompositor{k};
        std::vector<Fraction> fractions = fd.Decompose();

        std::cout << fractions.size() << std::endl;
        for (const auto& fraction : fractions) {
            std::printf("1/%llu = 1/%llu + 1/%llu\n", k, fraction.x,
                        fraction.y);
        }
    }
}