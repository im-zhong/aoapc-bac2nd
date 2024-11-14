// 2024/11/14
// zhangzhong

#include <iostream>

static char country_names[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
};

class Building {
  public:
    Building(int country_count) : country_count_{country_count} {}

    void Solve() { // 采取书上的解法，第一层第i行都是国家i
        // 第二层第j列都是国家j
        // 妙哉！！！

        // 这样每一层都是 n * n，一共两层

        std::cout << "2 " << this->country_count_ << " " << this->country_count_
                  << "\n";

        // 我们直接构造某个国家的
        // 算了 打表吧 直接写一个表 索引到的就是国家的名字
        // 打印第一层

        for (int row = 0; row < this->country_count_; row++) {
            int country = row;
            for (int col = 0; col < this->country_count_; col++) {
                // 第一层，每一层都是country
                std::cout << country_names[country];
            }
            std::cout << "\n";
        }
        std::cout << "\n";

        // 第二层 每一列都是country j
        for (int row = 0; row < this->country_count_; row++) {
            for (int col = 0; col < this->country_count_; col++) {
                int country = col;
                std::cout << country_names[country];
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

  private:
    int country_count_;
};

int main() {
    int country_count = 0;

    while (std::cin >> country_count) {
        Building building{country_count};
        building.Solve();
    }
}