// 2025/3/31
// zhangzhong
// 这道题简单的说 就是状态图的单源最短路

// While all patches fix some bugs,
// they often rely on other bugs to be present to be installed
// 对于每个patch，他要求某些bug必须存在，某些bug必须不存在，这两者不相交
// 然后修复之后，某些bug会被修复，然后会引入额外的bug，这两者同样不相交
// 把当前程序的bug存在情况视为一种状态，patch视为状态的转移
// 那么这就是一张状态图

// 就是在状态图上找start -> finish
// 之间的最短路，因为只需要找finish，所以找到了之后，算法可以提前退出
// Q：Given the original version of their software, which contains all the bugs
// in B, it is possible to apply a sequence of patches to the software which
// results in a bug- free version of the software? And if so, assuming that
// every patch takes a certain time to apply, how long does the fastest sequence
// take?

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using state_t = int;
using weight_t = int;

struct Patch {
    int second;
    std::string before_patch;
    std::string after_patch;
};

// 简单的说，咱们要实现一个单源最短路算法
// 但是首先要构建状态图
// 但是构建完整的状态图太慢了，所以构建隐式图
// 所以还是要先直接写单源最短路算法

struct State {
    state_t state;
    weight_t weight;

    bool operator<(const State& other) const noexcept {
        return this->weight < other.weight;
    }

    bool operator>(const State& other) const noexcept {
        return this->weight > other.weight;
    }
};

struct DirectedEdge {
    state_t head;
    state_t tail;
    weight_t weight;
};

class Solution {
  public:
    Solution(int bug_count, const std::vector<Patch>& patches)
        : _bug_count(bug_count), _patch_count(patches.size()),
          _patches(patches) {}

    int GetSolveTime() {

        // 回想一下最短路算法是怎样工作的
        // 对于图中的所有节点，维护一个distance数组
        // 初始化的时候，distance[source] = 0
        // 但是其他的节点的distance = INF
        // 然后我们把source加入到优先队列中
        // 然后设置source已经visited了

        // 然后每个从优先队列中出来的节点，都会被visited，他们不会再加入到优先队列中了
        // 对于每个出来的节点，我们要执行relax操作
        // 对于这个节点的每条边 edge a b
        // s -> a -> b < s -> b
        // 更新distance[b] = s -> a -> b
        // 更新parent[b] = a, 不过在这个题中 好像还用不到parent，暂时就不写了吧

        // 但是这个题的问题在于，我们没有节点，
        // 我们的节点都是用字符串表示的
        // 我们用一连串的字符串表示现在的状态，状态就是图的节点
        // 我们就用+表示bug存在，-表示bug不存在
        // std::string bugs = "++++++++"

        // 状态会被重复保存吗？
        // 有一个比较好的方法是用int表示bug
        // 因为 n = [1, 20] 所以一个int就可以表示了
        // 1 表示bug存在，0 表示bug不存在
        // 所以 11111111111111 就是初始状态
        // 0 就是final状态

        return this->SSSP(this->GetStartState(), this->GetFInalState());
    }

    int SSSP(int start, int final) {
        // 让我们从start 开始
        // 因为我们没有一个固定的状态数量 所以我们使用hashmap来保存distance
        std::unordered_map<state_t, weight_t> distance;

        // 初始化
        distance[start] = 0;
        // 其他所有不存在的节点，我们都认为是INF

        // 然后我们吧start放到优先队列中
        // 同时优先队列需要按照distance排序，同时需要保存他的state

        // 我们希望权重小的在堆顶
        std::priority_queue<State, std::vector<State>, std::greater<State>>
            queue;
        queue.push(State{start, 0});

        // 咱们显然不需要遍历完所有的状态，只要我们碰到final state就可以结束了
        while (!queue.empty()) {
            State state = queue.top();
            queue.pop();

            if (final == state.state) {
                // 从队列中取出来的时候，这个状态的最短路已经求完了
                return distance[state.state];
            }

            // TODO
            // 应该是通过distance来判断
            // 如果这个状态被用过了，应该也跳过才对
            // 不对，就算图有环也能用，因为环路一定不会被选择上，因为distance一定是更长的
            // 只要权是正的就行了
            if (state.weight != distance[state.state]) {
                // 说明这个节点已经被取出来过了
                // 直接跳过
                continue;
            }

            // 等我们拿到state之后，我们就找到state的所有邻接边
            // 因为这里我们使用的是隐式图
            // 所以我们需要将这些边即时的计算出来
            // 其实也非常简单，就是通过枚举所有的patch来判断是否构成一条边？构成了什么边？
            // Note that in such a sequence a patch may be used multiple times
            // 因为一个patch可能被使用多次，所以对于每个状态我们都枚举所有的patch
            for (const Patch& patch : this->_patches) {
                // 我们需要一个函数来判断某个patch是否可以应用在一个状态上
                if (!this->CouldApply(state.state, patch)) {
                    continue;
                }

                // 如果能够apply，那么我们自然就要apply这个state
                // 这回形成一个新的state
                state_t new_state = this->ApplyPatch(state.state, patch);

                // 也就是我们的图存在一条边 [state.state -> new_state], weight =
                // patch.time

                // 对于这条边，我们要做relax操作
                DirectedEdge edge{state.state, new_state, patch.second};
                // 这里有一个问题，就是distance[edge.tail] 可能是不存在的
                // head一定是存在的吗？是的。
                if (distance.count(edge.tail) == 0 ||
                    // 草这里写烦了，只有当新加入的一条边比目前的sitance要小的时候，才relax
                    distance[edge.tail] > distance[edge.head] + edge.weight) {

                    // 不对，就算我们在这里找到了final
                    // state，你怎么知道当前的解就是最优的呢？
                    // 最优解只有跑完整个算法才能知道吧
                    // 什么时候状态是确定的？
                    // 当状态从队列中读取的时候，就一定是确定的，在这里不是
                    // 在上面才是

                    distance[edge.tail] = distance[edge.head] + edge.weight;
                    // 然后我们需要更新队列中的值
                    queue.push(State{new_state, distance[edge.tail]});
                }
            }
        }

        // 反而是在这里，说明我们遍历了所有的状态，都没有找到答案
        // 这个时候应该返回ling
        return 0;
    }

    state_t ApplyPatch(state_t old_state, const Patch& patch) {
        // after patch
        // The second string describes which bugs are fixed and introduced
        // by the patch.
        // + bug was introduced
        // - bug if remove if it exits
        // 0 not affected, leave it not modified
        state_t new_state = old_state;
        for (int i = 0; i < this->_bug_count; i++) {
            switch (patch.after_patch[i]) {
            case '+': {
                new_state = this->IntroduceBug(new_state, i);
                break;
            }
            case '-': {
                new_state = this->ClearBug(new_state, i);
                break;
            }
            }
        }
        return new_state;
    }

    int GetStartState() { return (1 << this->_bug_count) - 1; }
    int GetFInalState() { return 0; }

  private:
    int GetState(state_t state, int pos) { return (state >> pos) & 1; }
    int IntroduceBug(state_t state, int pos) {
        // 我们要么新增了某个bug
        // 要么消除了某个bug
        // 还是叫这些名字好一些
        return state | (1 << pos);
    }

    int ClearBug(state_t state, int pos) {
        // 把某个位置置为零
        return state & ~(1 << pos);
    }

    bool CouldApply(state_t state, const Patch& patch) {
        // The first of these strings describes the bugs that have to be
        // present or absent before the patch can be applied
        // + means bug bi has to be present
        // - has to be absent
        // 0 do not mind
        for (int i = 0; i < this->_bug_count; i++) {
            switch (patch.before_patch[i]) {
            case '+': {
                // 这是把state的某位取出来
                if (this->GetState(state, i) != 1) {
                    return false;
                }
                break;
            }
            case '-': {
                if (this->GetState(state, i) != 0) {
                    return false;
                }
                break;
            }
            case '0': {
                // not mind
                break;
            }
            }
        }
        return true;
    }

    int _bug_count;
    int _patch_count;
    std::vector<Patch> _patches;
};

int main(int argc, char* argv[]) {
    // [1, 20]
    int bug_count = 0;
    // [1, 100]
    int patch_count = 0;

    for (int kase = 1; std::cin >> bug_count >> patch_count; kase++) {
        if (bug_count == 0 && patch_count == 0) {
            break;
        }

        // TODO: 有一个问题，如果这些patch之间本来就会导致图产生环呢？
        // 我们是不是不能用dj算法？

        // input
        std::vector<Patch> patches;
        for (int i = 0; i < patch_count; i++) {
            // This is followed by m lines describing the m patches in order
            // time of seconds, two strings of n chars
            Patch patch{};
            // The first of these strings describes the bugs that have to be
            // present or absent before the patch can be applied
            // + means bug bi has to be present
            // - has to be absent
            // 0 do not mind
            //
            // after patch
            // The second string describes which bugs are fixed and introduced
            // by the patch.
            // + bug was introduced
            // - bug if remove if it exits
            // 0 not affected, leave it not modified
            std::cin >> patch.second >> patch.before_patch >> patch.after_patch;
            patches.push_back(patch);
        }

        Solution solution{bug_count, patches};

        // output
        // first output the number of the produc
        std::cout << "Product " << kase << "\n";
        // if could remove all the bugs,
        int time = solution.GetSolveTime();
        if (time > 0) {
            std::cout << "Fastest sequence takes " << time << " seconds.\n";
        } else {
            std::cout << "Bugs cannot be fixed.\n";
        }
        std::cout << std::endl;
    }
}
