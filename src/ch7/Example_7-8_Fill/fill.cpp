// 2024/10/27
// zhangzhong

#include <array>
#include <cstdint>
#include <iostream>
#include <queue>
#include <unordered_map>

struct State {
    // 要不这里改成一个数组吧 不然后面的循环也不好写

    std::array<int, 3> waters = {};

    friend bool operator==(const State& lhs, const State& rhs) noexcept {
        return lhs.waters == rhs.waters;
    }
};

namespace std {
template <> struct hash<State> {
    // this function must be const noexcept!
    size_t operator()(const State& state) const noexcept {
        return std::hash<uint64_t>{}(state.waters[0] * 100 +
                                     state.waters[1] * 10 + state.waters[2]);
    }
};
} // namespace std

class Water {
  public:
    Water() {
        // auto i = std::hash<State>{}(State{});
        this->ReadThenInitialize();
    }

    void Solve() {
        this->Visit(this->initial_state_, 0);

        // [[TIPS]]
        // special case
        // 就是初始的情况就是解
        // 这种直接判断吧 也不用走bfs了
        if (this->IsFinalState(this->initial_state_)) {
            std::cout << 0 << " " << this->target_water << "\n";
        } else {
            bool has_solved = bfs();

            if (has_solved) {
                std::cout << this->min_total_poured_water_ << " "
                          << this->target_water << "\n";
            } else {
                std::cout << this->cloest_total_poured_water << " "
                          << this->max_cloest_target_water << "\n";
            }
        }

        // 我们把整个visited打印出来看一下
        // for (const auto& pair : this->visited_) {
        //     for (int water : pair.first.waters) {
        //         std::cout << water << ", ";
        //     }
        //     std::cout << ": " << pair.second << "\n";
        // }
    }

    // 既然是状态空间搜索 那么应该首先定义状态
    // 按照顺序，三个杯子的装水量就是状态
    // 因为装水量不会超过200 所以用int就ok

    // 和之前的bfs一样，同样使用一个visited和一个queue牌做bfs

    // [[TIPS]]
    // 我突然想到如果bfs和dfs结合起来，就是外层是一个bfs用来做状态搜索
    // 但是从上一个状态到下一个状态之间需要用回溯进行枚举
    // 感觉这样就有一些复杂度了

    void Visit(const State& state, uint64_t poured_water) {
        // 我们需要记录每一个状态的最接近target water的倒水量
        for (int water : state.waters) {
            if (water < this->target_water &&
                water > this->max_cloest_target_water) {

                // 这可能是一个新的答案
                this->max_cloest_target_water = water;
                this->cloest_total_poured_water = poured_water;
            }

            // 还有一种可能就是我们和最大的答案一样，但是我们的poured water要小
            // 那么也需要更新
            if (water < this->target_water &&
                water == this->max_cloest_target_water) {
                if (poured_water < this->cloest_total_poured_water) {
                    this->cloest_total_poured_water = poured_water;
                }
            }
        }
        // [[BUG]]
        // https://en.cppreference.com/w/cpp/container/unordered_map/insert
        // TMD 第一次知道insert是可能失败的！
        // 如果key已经存在那么 数值是不会进行更新的
        // 正确的写法应该是用index 因为[] 操作会自动插入不存在的原序
        this->visited_[state] = poured_water;
        // this->visited_.insert({state, poured_water});
        // 在这里剪枝对吗
        // 如果这个状态是完成态呢？
        // 就算是完成态，只要poured water 已知最小的water小
        // 那么久已经没有必要visit了 但是这个状态需要做一下insert
        // 但是不在放入队列中了
        if (poured_water >= this->min_total_poured_water_) {
            return;
        }

        this->queue_.push(state);
    }

    bool bfs() {

        bool has_solved = false;

        while (!this->queue_.empty()) {
            const State current_state = this->queue_.front();
            this->queue_.pop();

            // 在这里就要做枚举
            // 也就是到水
            // 但是这里的枚举情况非常简单
            // 所以用一个双层循环就可以做
            // a -> b
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    // i -> j

                    // 如果杯子 i 里面没水 就下一个
                    if (current_state.waters[i] <= 0) {
                        continue;
                    }

                    // 杯子i里面有水
                    // 如果杯子j是满的 也不能到
                    if (current_state.waters[j] == this->volumes_[j]) {
                        continue;
                    }

                    // 那么我们就要把i杯子中的水倒到j杯子中
                    // j杯子可以被倒入的量是
                    int remains = this->volumes_[j] - current_state.waters[j];
                    // 然后我们就产生了一个新的状态
                    State state = current_state;
                    // 而i杯子中可以倒入j杯子的量是当前i杯子中的量和j杯子可以被倒入的量中的较小者
                    int water = std::min(current_state.waters[i], remains);
                    state.waters[i] = state.waters[i] - water;
                    // 而j杯子就增加相应的量
                    state.waters[j] = state.waters[j] + water;

                    // 然后我们需要visit这个状态
                    auto iter = this->visited_.find(state);

                    // [[BUG]]
                    // 某个状态对应的poured water可能是会更新的
                    // 也就输状态之间组成的图实际上是一个DAG 并不是一个静态的图
                    // 所以哪怕visited过，只要poured
                    // water比之前的water要小，那么也需要重新计算一遍
                    if (iter != this->visited_.end()) {
                        // 说明这个状态已经访问过了
                        // 那么continue
                        if (this->visited_[current_state] + water <
                            iter->second) {

                        } else {
                            continue;
                        }
                    }

                    // 这个状态没有被访问过，我们就进行一个访问
                    // 同时，我们还需要知道到达这个状态所需的pour water量
                    // 那么就是到达前一个状态所需的量加上这一步状态转换所需的量
                    this->Visit(state, this->visited_[current_state] + water);

                    // 然后在这里我们就需要进行判断，是否结束了了
                    // [[TIPS]]
                    // 但是就算是到了这里，也不意味着这是最优解
                    // bfs只是找到最短的路径而已
                    // 而我们要找的是最小的倒水量
                    // 所以这里要使用进行全局的搜索 同时加上最优化剪枝
                    if (this->IsFinalState(state)) {
                        has_solved = true;
                        uint64_t total_poured_water =
                            this->visited_[current_state] + water;
                        if (total_poured_water <
                            this->min_total_poured_water_) {
                            this->min_total_poured_water_ = total_poured_water;
                        }
                        // break;
                    }
                }

                // if (has_solved) {
                //     break;
                // }
            }
            // if (has_solved) {
            //     break;
            // }
        }

        return has_solved;
    }

    bool IsFinalState(const State& state) {
        // 只要三个杯子中有一个到达了目标水量 就行
        // 0 = a
        // 1 = b
        // 2 = c
        return state.waters[0] == this->target_water ||
               state.waters[1] == this->target_water ||
               state.waters[2] == this->target_water;
    }

    // void PrintSolution() {
    //     std::cout << this->target_water << " " << this->target_water << "\n";
    // }

  private:
    void ReadThenInitialize() {
        int a;
        int b;
        int c;

        std::cin >> a >> b >> c >> target_water;
        // this->total_water = c;
        this->volumes_[0] = a;
        this->volumes_[1] = b;
        this->volumes_[2] = c;

        this->initial_state_.waters[0] = 0;
        this->initial_state_.waters[1] = 0;
        this->initial_state_.waters[2] = c;
    }

    // 现在visited可以不保存路径，但是其可以保存倒水量

    std::unordered_map<State, uint64_t> visited_;
    std::queue<State> queue_;

    State initial_state_;
    // 我们不能用abc来表示，还是用一个数组来表示 这样方便索引

    // 用一个数组来表示三个杯子的容积
    // 因为容积的范围是0-200 所以用int足以
    std::array<int, 3> volumes_;

    uint64_t min_total_poured_water_ = 99999999;

    // int total_water = 0;
    int target_water = 0;

    uint64_t cloest_total_poured_water = -1;
    int max_cloest_target_water = -1;
};

int main() {
    int test_case_count = 0;

    std::cin >> test_case_count;
    for (int i = 0; i < test_case_count; i++) {
        Water water = {};
        water.Solve();
        // water.PrintSolution();
    }
}
