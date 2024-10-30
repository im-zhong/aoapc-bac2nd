// 2024/10/29
// zhangzhong

#include <array>
#include <cstdint>
#include <iostream>
#include <unordered_map>

// 两段最多移动一次
// 九段最多移动八次
static const int MAX_DEPTH = 8;
static const int MAX_PARAGRAPH_COUNT = 9;

// 这里同样需要状态
// 为什么埃及分数不需要状态
// 哦！迭代加深只是一个思想
// 埃及分数是 迭代加深+回溯，所以没有状态
// 而本体是 迭代加深+状态搜索 所有需要状态
// 卧槽，真是受不了了，要报警啦！！！这些题太TM难了

struct State {
    // 使用一个数组来组织可能的状态
    // 同时还要使用visited 哈希数组来判断状态是否出现过
    // 还要考虑状态之间是否有更短的路径
    // 因为本体就是找最短的路径，所以不像倒水那道题一样一样，后来出现的相同解
    // 一定是更差的解

    std::array<int8_t, MAX_PARAGRAPH_COUNT> paragraphs;

    friend bool operator==(const State& lhs, const State& rhs) noexcept {
        return lhs.paragraphs == rhs.paragraphs;
    }
};

namespace std {
template <> struct hash<State> {
    size_t operator()(const State& state) const noexcept {
        uint64_t sum = 0;
        for (int paragraph : state.paragraphs) {
            sum = (sum << 1) + paragraph;
        }
        return std::hash<uint64_t>{}(sum);
    }
};
} // namespace std

class EditingBook {
  public:
    EditingBook(int test_case_id, int paragraph_count)
        : test_case_id_{test_case_id}, paragraph_count_{paragraph_count} {

        this->ReadThenInitialize();
    }

    void Solve() {

        // 我们好像忘了Visit Initial State！！！
        // [[BUG]]
        this->Visit(this->initial_state_, 0);

        // 还有一种最简单的情况
        // 就是我们不需要做任何事情
        if (this->IsFinalState(this->initial_state_)) {
            this->Visit(this->final_state_, 0);
            return;
        }

        for (int depth = 1; depth <= MAX_DEPTH; depth++) {

            // 迭代加深搜索
            // 只要在某个深度找到解
            // 就退出

            // 每次搜索之前，都需要重置一些状态
            this->Initialize();
            if (this->dfs(depth, 0, this->initial_state_)) {
                break;
            }
        }
    }

    void PrintSolution() {

        // 可以先打印出所有的段落 以验证我们的读取是正确的
        // for (int i = 0; i < this->paragraph_count_; i++) {
        //     std::cout << this->paragraphs_[i] << ", ";
        // }
        // std::cout << std::endl;
        //
        std::cout << "Case " << this->test_case_id_ << ": "
                  << this->visited_[this->final_state_] << "\n";
    }

  private:
    bool dfs(int max_depth, int current_depth, State current_state) {
        if (has_solved_) {
            return true;
        }

        // 这个题的最后一步会比较特殊吗？
        // 不会，所以就按照正常的节奏来写
        if (max_depth == current_depth) {

            // 检查我们的状态是不是最终状态
            // 我们有没有可能在没有达到max递归深度之前就找到解呢？
            // 是没有可能的，因为我们的深度是一点一点增加的
            // 所以只有可能在这里找到解
            if (this->IsFinalState(current_state)) {
                // 而且同一深度的不同解之间都是等价的
                // 我们也不需要记录最优解
                // 只需要记录深度即可
                // 而且一旦发现一个解，所有的递归都是无意义的
                // 直接返回就行
                this->has_solved_ = true;
                return true;
            }

            // 无论如何，我们都要退出，这是递归结束条件
            return false;
        }

        // 我们在这里就进行剪枝
        int count = this->GetCountOfWrongSuccessor(current_state);
        // 进行剪枝
        // 在一次copy paste中 我们最多对三个位置进行改动
        // 在最乐观的情况下
        // 我们的所有改动都是正确的
        // current_depth 表示当前的步数
        // max_depth表示所有的步数
        // 还剩下的步数是
        // 那么最多可以改动 3 * ((max_depth - current_depth) - 1)
        // 如果仍然小于 count
        // 那么我们必然无法完成
        // 所以就不进行下一个dfs了
        if (3 * ((max_depth - current_depth)) < count) {
            return false;
        }

        // 这里就要进行状态的枚举 然后递归
        // 我们要做的就是枚举range
        // TODO: 这里要不要都提前退出呢？
        // 我们有可能已经找到结果了，但是还在这里循环
        // int ok = false;
        for (int begin = 0; begin < this->paragraph_count_; begin++) {
            for (int end = begin + 1; end <= this->paragraph_count_; end++) {
                // [begin, end)
                // 怎么执行插入呢？
                // 给出初始状态，给出动作
                // begin前面和end后面都是插入点
                // 然后根据这些这些参数，构造一个新的状态即可
                // 下面那个循环就是给出
                for (int i = 0; i < this->paragraph_count_ - (end - begin) + 1;
                     i++) {
                    if (i == begin) {
                        continue;
                    }

                    // 咱们在特定情况下打印一些输出吧
                    // if (current_depth == 0) {
                    //     if (begin == 4 && end == 5 && i == 0 &&
                    //         current_state.paragraphs[begin] == 0) {
                    //         std::cout << "on depth 0, cut [4:5] to 0\n";
                    //     }
                    // }

                    // if (current_depth == 1) {
                    //     if (begin == 7 && end == 8 && i == 3 &&
                    //         current_state.paragraphs[begin] == 5) {
                    //         std::cout << "on depth 1, cut [7:8] to 3\n";
                    //     }
                    // }

                    // if (current_depth == 2) {
                    //     if (begin == 8 && end == 9 && i == 3 &&
                    //         current_state.paragraphs[begin] == 4) {
                    //         std::cout << "on depth 2, cut [8:9] to 3\n";
                    //     }
                    // }

                    State new_state =
                        this->CopyThenPaste(current_state, begin, end, i);

                    // 也就是在这里需要判断我们访问的步数是不是比已经访问的要小
                    // 如果小的话 我们坚持访问！
                    if (this->visited_.find(new_state) !=
                        this->visited_.end()) {

                        if (current_depth + 1 < this->visited_[new_state]) {

                        } else {
                            continue;
                        }
                    }

                    // [[BUG]] TMD学杂了。。。
                    // 不对卧槽！
                    // 我想错了
                    // 这不是bfs 只有层先的时候，我们访问的时候是一步一步的
                    // 后面访问的一定不如前面的
                    // 但是我们这里是dfs
                    // 也就是说我们不是先访问完一层 才去访问下一次层的
                    // 也就是说之后visit到的有可能是更优的解！！！
                    this->Visit(new_state, current_depth + 1);

                    // 然后要进行剪枝
                    // 首先统计后继不对的个数
                    // int count = this->GetCountOfWrongSuccessor(new_state);
                    // // 进行剪枝
                    // // 在一次copy paste中 我们最多对三个位置进行改动
                    // // 在最乐观的情况下
                    // // 我们的所有改动都是正确的
                    // // current_depth 表示当前的步数
                    // // max_depth表示所有的步数
                    // // 还剩下的步数是
                    // // 那么最多可以改动 3 * ((max_depth - current_depth) - 1)
                    // // 如果仍然小于 count
                    // // 那么我们必然无法完成
                    // // 所以就不进行下一个dfs了
                    // if (3 * ((max_depth - current_depth) - 1) < count) {
                    //     continue;
                    // }

                    // 然后继续深度
                    // 或许可以辩证的使用一个goto？
                    // 或者直接使用return?

                    if (this->dfs(max_depth, current_depth + 1, new_state)) {
                        return true;
                    }
                }
            }
        }
        return this->has_solved_;
    }

    int GetCountOfWrongSuccessor(const State& state) {

        int count = 0;
        for (int i = 0; i < this->paragraph_count_ - 1; i++) {
            if (state.paragraphs[i] != state.paragraphs[i + 1] - 1) {
                count += 1;
            }
        }

        if (state.paragraphs[this->paragraph_count_ - 1] !=
            this->paragraph_count_ - 1) {
            count += 1;
        }
        return count;
    }

    void Visit(const State& state, int depth) {
        // this->visited_.insert({state, depth});
        this->visited_[state] = depth;
    }

    State CopyThenPaste(const State& state, int begin, int end,
                        int insert_point) {

        // for (int i = 0; i < this->paragraph_count_ - (end - begin) + 1; i++)
        // {
        //     if (i == begin) {
        //         continue;
        //     }

        int i = insert_point;

        State new_state{};

        // 然后我们开始构造一个新的State并进行复制
        // 不如先把begin到end给复制进去，然后处理剩下的数据
        // TODO: 可以吧for循环里面的if去掉
        // 改成就是循环对应的区域
        // for (int j = 0; j < end - begin; j++) {
        //     new_state.paragraphs[i + j] = state.paragraphs[begin + j];
        // }
        // for (int j = 0; j < this->paragraph_count_; j++) {
        //     // 然后我们处理剩下的
        //     // 不论如何，剩下的就两个范围
        //     // 0:i
        //     // i+(end-begin):
        //     // 那我们就根据这两个范围来填写就行啊
        //     if (j < i) {
        //         //
        //         if (j < begin) {
        //             new_state.paragraphs[j] = state.paragraphs[j];
        //         } else {
        //             new_state.paragraphs[j] =
        //                 state.paragraphs[j + (end - begin)];
        //         }

        //     } else if (j >= i + (end - begin)) {
        //         if (j <)
        //     }
        // }

        // 我们无论如何都是要将结果写入new state
        // 用j表示将要写入 new state的位置
        // int j = 0;

        // 而我们要做的，无论如何也都是遍历一遍 state 然后把他的顺序打乱而已
        // 用k表示遍历state的下标

        int k = 0;

        // 而state可以被分成三个区间
        // 0:begin
        // begin:end
        // end:paragraph_count

        // 这个逻辑这么难写吗？
        // ！有一个非常简单的写法
        // 但是会牺牲一点点效率
        // 因为这个数组并不长
        // 所以采取模拟插入的方式是比较合适的
        // 就是我们首先先把去掉[begin:end]的部分复制到new_state 里面
        // 然后将插入点之后的数据全部向后复制
        // 然后在把数据插入！

        // 不对不对 不能用i
        for (int j = 0; j < begin; j++) {
            new_state.paragraphs[k] = state.paragraphs[j];
            k++;
        }
        for (int j = end; j < this->paragraph_count_; j++) {
            new_state.paragraphs[k] = state.paragraphs[j];
            k++;
        }
        // 然后把插入点开始
        // 不行，我们得倒着复制，就像插入排序那样
        // 这里还要注意越界
        // 先捋一捋要移动的范围
        int remain_count = this->paragraph_count_ - (end - begin);
        // [i:remain_count]
        // for (int k = i + (end - begin); k >= i; k--) {
        //     if (k >= this->paragraph_count_) {
        //         continue;
        //     }
        //     new_state.paragraphs[k] =
        //         new_state.paragraphs[k - (end - begin)];
        // }
        for (int k = remain_count - 1; k >= i; k--) {
            // 实际要复制到的位置是
            // k + (end - begin)
            new_state.paragraphs[k + (end - begin)] = new_state.paragraphs[k];
        }
        // 然后把[begin:end]插入到i位置
        k = i;
        for (int j = begin; j < end; j++) {
            new_state.paragraphs[k] = state.paragraphs[j];
            k++;
        }
        // }
        return new_state;
    }

    void ReadThenInitialize() {

        // 在读取之间需要把initial state和final state都set 0
        // 否则两次调用，下次会保留上次的结果
        for (int i = 0; i < MAX_PARAGRAPH_COUNT; i++) {
            this->initial_state_.paragraphs[i] = 0;
            this->final_state_.paragraphs[i] = 0;
        }

        for (int i = 0; i < this->paragraph_count_; i++) {
            int paragraph = 0;
            std::cin >> paragraph;
            // 把 1-> n 映射到 0 -> n-1
            this->initial_state_.paragraphs[i] = paragraph - 1;
        }

        for (int i = 0; i < paragraph_count_; i++) {
            this->final_state_.paragraphs[i] = i;
        }
    }

    void Initialize() {
        // 每次当前深度的状态空间搜索完毕之后，需要重置状态继续进行搜索

        has_solved_ = false;
        visited_.clear();
    }

    bool IsFinalState(const State& state) {
        for (int i = 0; i < this->paragraph_count_; i++) {
            if (state.paragraphs[i] != this->final_state_.paragraphs[i]) {
                return false;
            }
        }
        return true;
    }

    bool has_solved_ = false;
    int test_case_id_;
    int paragraph_count_;

    // 这个应该用State给包装起来

    // std::array<int, MAX_PARAGRAPH_COUNT> paragraphs_ = {};
    State initial_state_;
    State final_state_;

    // 保存到达每个状态时所经历的步数
    // 这个就是我们的答案
    std::unordered_map<State, int> visited_;
};

int main() {

    // [1, 10]
    int paragraph_count = 0;

    // [1, 20]
    int test_case_id = 1;
    while (std::cin >> paragraph_count) {
        if (paragraph_count == 0) {
            break;
        }

        EditingBook eb{test_case_id, paragraph_count};
        eb.Solve();
        eb.PrintSolution();

        test_case_id += 1;
    }
}