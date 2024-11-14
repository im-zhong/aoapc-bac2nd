// 2024/11/14
// zhangzhong

#include <iostream>
#include <sstream>
#include <vector>

class FlipStack {

  public:
    FlipStack(std::vector<int> flapjacks) : flapjacks_{std::move(flapjacks)} {}

    void Solve() {

        // 在每个循环中，我们都需要寻找最大的直径
        // 先把他翻到最上面 然后再翻到最底下

        // [[BUG]]
        // 从今以后，不准使用i j k
        // 必须具有明确的含义
        for (int end_index = this->flapjacks_.size(); end_index > 0;
             end_index--) {

            int max_diamiter = 0;
            int max_index = 0;
            // 只有在这里我们可以使用i这个变量 来表示我们在遍历当前数组
            // 他也确实代表当前数组的索引
            for (int i = 0; i < end_index; i++) {
                // 首先找到最大的盘子
                if (this->flapjacks_[i] > max_diamiter) {
                    max_diamiter = this->flapjacks_[i];
                    max_index = i;
                }
            }

            // 做两次反转动作, 也可能不做
            // 我们的目的是将煎饼放到i-1的位置上
            // 但是如果煎饼一开始就在这个位置上 则什么动不需要做
            if (max_index == end_index - 1) {
                continue;
            }

            // 第一次反转是将煎饼翻到最上面
            // 如果我们已经在最上面了 则不用翻转
            if (max_index != 0) {
                this->Flip(max_index);
            }
            // 第二次翻转是将煎饼翻装到i-1的位置上
            this->Flip(end_index - 1);
        }

        std::cout << "0\n";
    }

    void Flip(int index) {

        // 需要一个栈辅助实现
        // 不对，最简单的方式是交换
        for (int left = 0, right = index; left < right; left++, right--) {
            std::swap(this->flapjacks_[left], this->flapjacks_[right]);
        }

        // 我们的index表示的是从上往下数的位置
        // 也就是程序语言中的索引
        // 而题目要求的是从底下向上树的位置
        // 其实是 size() - index
        std::cout << this->flapjacks_.size() - index << " ";
        // 在程序的最后还要输出一个零
    }

  private:
    std::vector<int> flapjacks_;
};

int main() {

    // 读取的工作在外面做吧 这样容易控制程序结束
    std::string line;
    while (std::getline(std::cin, line)) {
        std::cout << line << "\n";

        std::stringstream ssr{line};

        // 最多有30个煎饼，或许可以使用一个固定的数组来节省内存分配的时间
        std::vector<int> plapjacks;
        int diamiter = 0;
        while (ssr >> diamiter) {
            plapjacks.push_back(diamiter);
        }

        FlipStack fs{plapjacks};
        fs.Solve();
    }
}