// 2024/10/25
// zhangzhong

#include <cassert>
#include <cstdint>
#include <iostream>

static const int max_number_count = 18;

class MaximumProduct {
  public:
    MaximumProduct(int number_count) : number_count_{number_count} {
        this->ReadNumbers();
    }

    int64_t GetMaximumProduct() {
        // [[BUG]]
        // 哪怕用 int64_t 全部的数字连乘起来其结果也是溢出的
        // 难到要用uint64_t 然后额外保存一个正负号吗？
        int64_t product = this->CalculateProudct(0, this->number_count_);
        this->max_product_ = product;

        // 递归计算
        this->GetMaximumProductImpl(product, 0, this->number_count_);

        if (this->max_product_ > 0) {
            return this->max_product_;
        } else {
            return 0;
        }
    }

  private:
    void ReadNumbers() {
        for (int i = 0; i < this->number_count_; i++) {
            int number = 0;
            std::cin >> number;
            this->numbers[i] = number;
        }
    }

    void GetMaximumProductImpl(int64_t product, int begin, int end) {
        if (begin >= end) {
            return;
        }

        if (end - begin == 1) {
            this->SetMaxProduct(this->numbers[begin]);
        } else {
            // 是不是这里出了问题？
            // 我们检查一下输入范围
            // 没有问题，因为我们的范围是一直在缩小的，不会越界
            assert(begin >= 0);
            assert(end <= this->number_count_);

            // [[BUG]]
            // 重大bug，我们是可能除以零的！！！
            // 这里给我们两个启示
            // 1. RunTimeError除了数组内存指针相关错误之外，还有可能是整数除零
            // 2.
            // 边界条件除了序列长度为最小，最大之外，一些特殊的值也非常值得测试，比如0，
            // 1 ，-1 之类的东西
            // 3.
            // TMD又忘了，只要是涉及到整数计算的，不管是相加还是相乘，统统给我用int64!
            // 防止数值溢出！
            int64_t left_product = 0;
            if (this->numbers[begin] == 0) {
                left_product = this->CalculateProudct(begin + 1, end);
            } else {
                // 就算这个数不是零。我们的计算就是对的吗？
                left_product = product / this->numbers[begin];
            }
            // int left_product = product / this->numbers[begin];
            this->SetMaxProduct(left_product);
            this->GetMaximumProductImpl(left_product, begin + 1, end);

            int64_t right_product = 0;
            if (this->numbers[end - 1] == 0) {
                right_product = this->CalculateProudct(begin, end - 1);
            } else {
                right_product = product / this->numbers[end - 1];
            }
            // int right_product = product / this->numbers[end - 1];
            this->SetMaxProduct(right_product);
            this->GetMaximumProductImpl(right_product, begin, end - 1);
        }
    }

    void SetMaxProduct(int64_t product) {
        if (product > this->max_product_) {
            this->max_product_ = product;
        }
    }

    // [[BUG]]
    // TMD 这里返回的是int 而不是 int64 调试了半天。。。
    int64_t CalculateProudct(int begin, int end) {
        // if (begin >= end) {
        //     return -99999;
        // }

        // calculate the proudct in this range
        int64_t product = 1;
        for (int i = begin; i < end; i++) {
            product *= this->numbers[i];
        }

        return product;
    }

  private:
    int64_t max_product_;
    int number_count_;
    int64_t numbers[256];
};

int main() {

    int test_case_id = 0;
    int number_count = 0;

    while (std::cin >> number_count) {
        auto mp = MaximumProduct{number_count};

        test_case_id++;
        std::cout << "Case #" << test_case_id << ": The maximum product is "
                  << mp.GetMaximumProduct() << ".\n\n";
    }
}