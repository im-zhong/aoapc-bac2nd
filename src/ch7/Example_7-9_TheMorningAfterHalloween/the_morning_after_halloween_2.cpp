// 2024/10/27
// zhangzhong

// 一道典型的状态空间搜索题

#include <algorithm>
#include <array>
#include <bitset>
#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>

// 首先定义状态
// 我们最多有三个鬼
// 所以使用一个数组保存鬼
// 然后还需要保存鬼的数量
// 但是这个东西不应该保存在状态里面，

// 我们的状态其实就是鬼的位置 为了节省空间，鬼的位置虽然是一个二维的坐标
// 但是保存一个数字也可以还原鬼的位置
// 且我们的地图是很小的 (weight, height <= 16)
// 所以使用int类型是ok的

static const int max_height = 16;
static const int max_width = 16;

struct State {
    std::array<int, 3> pos = {};

    // 同样的，我们需要实现operator==
    // 和哈希
    friend bool operator==(const State& lhs, const State& rhs) noexcept {
        return lhs.pos == rhs.pos;
    }
};

namespace std {
template <> struct hash<State> {
    size_t operator()(const State& state) const noexcept {
        return std::hash<uint64_t>{}(state.pos[0] + state.pos[1] * 10 +
                                     state.pos[2] * 100);
    }
};
} // namespace std

class Halloween {
  public:
    Halloween(int width, int height, int ghost_count)
        : row_{height}, col_{width}, ghost_count_{ghost_count} {
        this->ReadThenInitialize();
        this->ConstructLegalAdjs();
    }

    void Solve() {

        this->Visit(this->initial_state_, 0);

        this->bfs();
    }

    void PrintSolution() {
        // for (int r = 0; r < this->row_; r++) {
        //     for (int c = 0; c < this->col_; c++) {
        //         std::cout << this->map_[r][c];
        //     }
        //     std::cout << "\n";
        // }

        std::cout << this->visited_[final_state_] << "\n";
    }

    // 给出一个鬼的坐标 和 方向 返回鬼的新的坐标和方向
    // int Move(int pos, int dir) {
    //     // 给出pos 我们怎么知道row和col呢？

    //     // int col = pos % this->col_;
    //     // int row = pos / this->col_;

    //     switch (dir) {
    //     case 0: {
    //         return pos;
    //     }

    //     case 1: {
    //         // left
    //         // col -= 1;
    //         return pos - 1;
    //     }

    //     case 2: {
    //         // up
    //         // row -= 1;
    //         // return row * this->col_ + col_;
    //         return pos - this->col_;
    //     }

    //     case 3: {
    //         // right

    //         // col += 1;
    //         return pos + 1;
    //     }

    //     case 4: {
    //         // down
    //         // row += 1;

    //         return pos + this->col_;
    //     }
    //     }
    //     return pos;
    // }

    bool IsLegalMove(const State& from, const State& to) {

        // 首先 from state一定是合法的

        std::bitset<16 * 16> set = {};

        for (int i = 0; i < this->ghost_count_; i++) {
            // int row = to.pos[i] / this->col_;
            // int col = to.pos[i] % this->col_;

            // if (this->map_[row][col] == '#') {
            //     return false;
            // }

            // 所有的新的ghost的位置 不能有重叠
            // 最简单的办法就是用一个bitset
            // 遍历的过程中发现bitset已经被设置了，那么就不对了
            // 但是还有更简单的办法
            // 这个bitset最大就是 16 * 16的

            if (set.test(to.pos[i])) {
                return false;
            }
            set.set(to.pos[i]);
        }

        if (this->ghost_count_ == 1) {
            return true;
        }

        for (int i = 0; i < this->ghost_count_; i++) {
            for (int j = i + 1; j < this->ghost_count_; j++) {
                // i != j
                if (from.pos[i] == to.pos[j] && from.pos[j] == to.pos[i]) {
                    return false;
                }
            }
        }
        return true;
    }

    // bool IsWall(int pos) {
    //     int col = pos % this->col_;
    //     int row = pos / this->col_;

    //     return this->map_[row][col] == '#';
    // }

    // [[TIP]]
    // 这道题目的要想做对其实不难，最关键的是怎么削减时间
    // 由题目条件知道，墙非常多
    // 在这种情况下，与其每次都先生成在测试(generate then test)
    // 不如直接构造一个空的地图，没有墙的地图位置
    // 然后我们就只遍历这个空的地图就行了
    // 应该会加快一些速度
    void bfs() {

        // bool has_solved = false;

        while (!this->queue_.empty()) {

            State current_state = this->queue_.front();
            this->queue_.pop();

            // 拿到当前的状态之后，我们就要枚举接下来可能发生的状态
            // 这应该是这道题主要的难点了

            for (int pos_2 : this->legal_adjs_[current_state.pos[2]]) {
                for (int pos_1 : this->legal_adjs_[current_state.pos[1]]) {
                    for (int pos_0 : this->legal_adjs_[current_state.pos[0]]) {
                        State state = {};
                        state.pos[0] = pos_0;
                        state.pos[1] = pos_1;
                        state.pos[2] = pos_2;

                        // 现在我们就拿到了移动之后的state
                        // 接下来我们就要判断，这个state是不是合法的state
                        if (!this->IsLegalMove(current_state, state)) {
                            continue;
                        }

                        // 假设我们已经枚举出来了
                        // 那么我们只需要判断状态是否被用过
                        if (this->visited_.find(state) !=
                            this->visited_.end()) {
                            continue;
                        }

                        this->Visit(state, this->visited_[current_state] + 1);

                        // 判断是否到达final state
                        if (this->IsFinalState(state)) {
                            // has_solved = true;
                            return;
                        }
                    }
                }
            }

            // 咱们的算法本身是对的 但是就是太慢了
            // 原因肯定是在于搜索了大量的无效的解
            // for (int i = 0; i < (this->ghost_count_ == 3 ? 5 : 1); i++) {
            //     State state = current_state;
            //     int pos = Move(state.pos[2], i);
            //     // 因为只move了一下，所以只能判断是不是撞上墙了
            //     if (IsWall(pos)) {
            //         continue;
            //     }

            //     for (int j = 0; j < (this->ghost_count_ >= 2 ? 5 : 1); j++) {
            //         //
            //         但是这样其实也不对，我们在循环里面move，在下一次循环之前还得把move的修改给转变回来
            //         // 因为move并不会花费很多的成本
            //         // 所以最好的办法是每次都声明一个state
            //         // 然后分别复制 只看能不能移动
            //         pos = Move(state.pos[1], j);
            //         if (IsWall(pos)) {
            //             continue;
            //         }

            //         for (int k = 0; k < 5; k++) {
            //             // 这里就是做一个 0 1 2 的排列的枚举
            //             // i表示第三只鬼
            //             // j表示第二只鬼
            //             // k表示第一只鬼

            //             // 0 1 2 3 4  代表四个方向
            //             // 0 表示不动
            //             State state = current_state;
            //             state.pos[2] = Move(state.pos[2], i);
            //             state.pos[1] = Move(state.pos[1], j);
            //             state.pos[0] = Move(state.pos[0], k);

            //             // 现在我们就拿到了移动之后的state
            //             // 接下来我们就要判断，这个state是不是合法的state
            //             if (!this->IsLegalMove(current_state, state)) {
            //                 continue;
            //             }

            //             // 假设我们已经枚举出来了
            //             // 那么我们只需要判断状态是否被用过
            //             if (this->visited_.find(state) !=
            //                 this->visited_.end()) {
            //                 continue;
            //             }

            //             this->Visit(state, this->visited_[current_state] +
            //             1);

            //             // 判断是否到达final state
            //             if (this->IsFinalState(state)) {
            //                 has_solved = true;
            //                 return;
            //             }
            //         }
            //     }
            // }
        }
    }

    void Visit(const State& state, uint64_t step) {
        this->queue_.push(state);
        this->visited_.insert({state, step});
    }

    bool IsFinalState(const State& state) {
        for (int i = 0; i < this->ghost_count_; i++) {
            if (state.pos[i] != this->final_state_.pos[i]) {
                return false;
            }
        }
        return true;
    }

    // 如果可以结合一个state和map来打印当前的状态就好了
    // void PrintMap(const State& state) {

    //     char no_ghost_map[max_height][max_width];
    //     for (int r = 0; r < this->row_; r++) {
    //         for (int c = 0; c < this->col_; c++) {
    //             no_ghost_map[r][c] = this->no_ghost_map_[r][c];
    //         }
    //     }

    //     for (int i = 0; i < this->ghost_count_; i++) {

    //         int pos = state.pos[i];
    //         int col = pos % this->col_;
    //         int row = pos / this->col_;

    //         // copy the no ghost map
    //         no_ghost_map[row][col] = 'a' + i;
    //     }

    //     for (int r = 0; r < this->row_; r++) {
    //         for (int c = 0; c < this->col_; c++) {
    //             std::cout << no_ghost_map[r][c];
    //         }
    //         std::cout << std::endl;
    //     }
    // }

  private:
    void ReadThenInitialize() {

        // 构建一个数组
        // 因为其规定了最大的数组范围，我们可以不使用堆
        // 直接在栈上构造一个大的数组
        // 现在我们读入这个数组
        std::string line;
        // get the first blank line
        std::getline(std::cin, line);

        for (int r = 0; r < this->row_; r++) {
            std::getline(std::cin, line);
            for (int c = 0; c < this->col_; c++) {
                this->map_[r][c] = line[c];
                // if (!(line[c] >= 'a' && line[c] <= 'c')) {
                //     this->no_ghost_map_[r][c] = line[c];
                // }

                // 还要在读取过程中 统计出鬼的初始位置和最终位置
                // 字母一定是abc开始的 所以读取a久放到state的第一个位置就ok了
                if (line[c] >= 'a' && line[c] <= 'c') {
                    this->initial_state_.pos[line[c] - 'a'] =
                        r * this->col_ + c;
                } else if (line[c] >= 'A' && line[c] <= 'C') {
                    this->final_state_.pos[line[c] - 'A'] = r * this->col_ + c;
                }
            }
        }
    }

    int GetPos(int row, int col) { return row * this->col_ + col; }

    void ConstructLegalAdjs() {

        // 找到所有空地的相近的空地
        // 由题目条件知道，四周都是墙
        // 所以可以从第一行和第一列开始
        for (int row = 1; row < this->row_ - 1; row++) {
            for (int col = 1; col < this->col_ - 1; col++) {
                if (this->map_[row][col] == '#') {
                    continue;
                }
                int pos = GetPos(row, col);
                this->legal_adjs_[pos] = {pos};

                // 然后寻找其合法邻居
                // 首先他自己本身就是一个合法
                if (this->map_[row - 1][col] != '#') {
                    // int pos =
                    // 不对啊 这里写错啦！！
                    // 不能重新定义pos啊
                    this->legal_adjs_[pos].push_back(GetPos(row - 1, col));
                }

                if (this->map_[row + 1][col] != '#') {
                    // int pos = ;
                    this->legal_adjs_[pos].push_back(GetPos(row + 1, col));
                }

                if (this->map_[row][col - 1] != '#') {
                    // int pos = ;
                    this->legal_adjs_[pos].push_back(GetPos(row, col - 1));
                }

                if (this->map_[row][col + 1] != '#') {
                    // int pos = ;
                    this->legal_adjs_[pos].push_back(GetPos(row, col + 1));
                }
            }
        }

        this->legal_adjs_[0] = {0};
    }

    std::unordered_map<int, std::vector<int>> legal_adjs_;

    State initial_state_;
    State final_state_;

    std::queue<State> queue_;
    // 要记录步数的
    std::unordered_map<State, uint64_t> visited_;

    int row_;
    int col_;
    int ghost_count_;

    char map_[max_height][max_width];

    // char no_ghost_map_[max_height][max_width];
};

int main() {

    for (;;) {
        int width = 0;
        int height = 0;
        int ghost_count = 0;
        std::cin >> width >> height >> ghost_count;

        if (width == 0 && height == 0 && ghost_count == 0) {
            break;
        }

        Halloween h = {width, height, ghost_count};
        h.Solve();
        h.PrintSolution();
    }
}
