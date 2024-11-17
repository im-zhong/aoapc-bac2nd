// 2024/11/17
// zhangzhong

#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <vector>

// 这个方法的前面一部分和那个O(n^2)的算法是一样的，区别在于，我们不在进行i，j的遍历,
// 而是只遍历i 从前往后遍历，然后始终维护一个candidate
// candidate始终满足：key不重复，key越大value也就越大
// 这样我们就只需要通过lower_bound: Searches for the first element in the
// partitioned range [first, last) which is not ordered before value.
// 第一个 >= key的iterator
// 而我们想要的是 < key 的 iterator
// 所以搜索到之后 it--

// 用了一些优化手段，时间减少了2-300ms左右 感觉差距也不大

// 我们写一个函数来验证candidate始终满足上述条件
bool CheckCandidates(const std::map<int, int>& candidates) {

    int last = 0;
    for (const auto& pair : candidates) {

        if (pair.second < last) {
            return false;
        }

        last = pair.second;
    }

    return true;
}

static const int maxn = 200000 + 10;

int tail[maxn];
int head[maxn];

int GetLongestIncreasingSequenceLength(int* towers, int tower_count) {

    // 首先求两个数组
    // 一个是以当前元素为tail元素的连续序列的长度
    // 一个是以当前元素为head元素的连续序列长度

    // std::vector<int> tail;
    // tail.resize(towers.size());

    // 只需要O(n)的时间就可以算出来
    // 累计当前的最长长度即可
    // 一旦出现断裂 重置即可
    int last = -100000;
    int current_length = 0;
    for (int i = 0; i < tower_count; i++) {
        if (towers[i] > last) {
            current_length++;
            // tail[i] = current_length;
        } else {
            // 序列断掉了
            current_length = 1;
            // tail[i] = 1;
        }

        tail[i] = current_length;
        last = towers[i];
    }

    // 计算以当前元素为head的元素的连续序列长度
    // 其实就是倒过来算
    last = -100000;
    current_length = 0;
    // std::vector<int> head;
    // head.resize(towers.size());
    for (int i = tower_count - 1; i >= 0; i--) {
        // [[BUG]]
        // 这里错了，倒过来的话 大小关系也要倒过来
        if (towers[i] < last) {
            current_length++;
            // tail[i] = current_length;
        } else {
            // 序列断掉了
            current_length = 1;
            // tail[i] = 1;
        }

        head[i] = current_length;
        last = towers[i];
    }

    // 然后枚举head 和 tail
    // 保证 tail < head 即可
    // [[BUG]]
    // 不对，最小的length是1。因为再短再短 单个也是对的吗
    int max_length = 1;
    // for (int i = 0; i < towers.size(); i++) {
    //     for (int j = i + 1; j < towers.size(); j++) {
    //         // [[BUG]]
    //         if (towers[i] < towers[j]) {
    //             // 枚举的时候还要判断一个条件
    //             // 就是序列整体得是有序的
    //             max_length = std::max(max_length, tail[i] + head[j]);
    //         }
    //     }
    // }

    // 我们从第二个位置开始枚举，因为不论如何，第一个candidate都是首位
    // 这样设定初始状态 后序的循环写起来也更简单

    // 我感觉这里使用map也行吧
    std::map<int, int> candidates;
    candidates.insert({towers[0], tail[0]});

    for (int i = 1; i < tower_count; i++) {

        // 找到第一个 >= towers[i] 的值
        auto iter = candidates.lower_bound(towers[i]);

        // 这里有很多种情况
        // 可能的返回值 begin(), end()
        // 因为我们要的是前一个，所以不能是begin()
        // 如果确实是begin 意味着什么呢？
        // 没有一个数比当前的towers[i] 小，也就是无法组成一个序列,
        // 在此情况下，我们也是需要keep当前的towers[i]的
        // 反证法真TM好使
        // 直接假设一种极端情况，然后反证，很容易就想明白了
        bool keep = true;
        if (iter != candidates.begin()) {

            // 找到那个最合适的序列
            auto last = *(--iter);
            int tower_height = last.first;
            int length_at_tail = last.second;
            max_length = std::max(max_length, length_at_tail + head[i]);

            // 加下来就是最关键的操作
            // 我们现在需要将 towers[i], tail[i] 加入到candidate中，
            // 并始终维持我们的假设

            // 首先 towers[i] > last.first
            // 所以 以i为tail的序列长度也必须比 last.second 长 否则就违反了规则
            // if (tail[i] <= length_at_tail) {
            //     keep = false;
            // }
            // 如果没有重复元素的话，这个也是对的
            // keep = tail[i] > length_at_tail;

            // 还有一种特殊的情况需要处理
            // 就是iter指向的值刚好就是towers[i]的时候
            // 不对，我们的iter也可能是end呀
            iter = ++iter;
            if (iter != candidates.end() && iter->first == towers[i]) {
                // 只有当以现在为尾巴的序列长度比已经存在的尾巴长度要大的时候，才需要更新
                keep = tail[i] > iter->second;
            } else {
                // 否则的话，我们是和前一个元素进行比较
                keep = tail[i] > length_at_tail;
            }
        }

        if (keep) {

            // 现在我们需要将 tower[i]: tail[i] 插入到candidate中

            // 同时在插入之后，任何在我们之后的元素，其tail必须比我们大
            // 否则就会被删掉

            // 在插入之前，我们思考一下，key可能重复吗？
            // key当然是可能重复的
            // 当key已经存在的时候，last指向的就是key的前一个数
            // 所以我们这里是有可能会覆盖掉之前的值的
            // 而且之前的值也有可能会比我们现在的值要大,
            // 除非整个序列是不会发生重复的 测试用例里面确实都是没有重复的值
            candidates[towers[i]] = tail[i];

            auto iter = candidates.upper_bound(towers[i]);
            // 迭代iter
            while (iter != candidates.end()) {
                if (iter->second <= tail[i]) {
                    candidates.erase(iter++);
                } else {
                    break;
                }
            }
        }

        // assert(CheckCandidates(candidates));
    }

    return max_length;
}

int towers[maxn];

int main() {

    // std::vector<int> towers = {1, 2, 6, 7, 3, 4, 5, 8};
    // int length = GetLongestIncreasingSequenceLength(towers);
    // std::cout << length << std::endl;

    int case_count = 0;
    std::cin >> case_count;

    for (int c = 0; c < case_count; c++) {
        int tower_count = 0;
        std::cin >> tower_count;

        // std::vector<int> towers;
        for (int t = 0; t < tower_count; t++) {
            int tower_height = 0;
            std::cin >> tower_height;
            // towers.push_back(tower_height);
            towers[t] = tower_height;
        }

        // 输出一下vector
        // for (int i = 0; i < tower_count; i++) {
        //     std::cout << towers[i] << ", ";
        // }
        // std::cout << std::endl;
        int length = GetLongestIncreasingSequenceLength(towers, tower_count);
        // std::cout << c << ": " << length << std::endl;
        std::cout << length << "\n";
    }
}
