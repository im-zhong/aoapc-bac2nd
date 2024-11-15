// 2024/10/15
// zhangzhong

// 我们先写一个处理一维数据的算法

#include <algorithm>
#include <iostream>
#include <vector>

struct Interval {
    int left;
    int right;
};

std::vector<int> PlacePoint(const std::vector<Interval>& intervals) {

    std::vector<int> placements;
    // 这里同样也用错了
    // 因为我们想把这个vector当数组使 要random access
    // 所以不能用reserve 需要用resize
    placements.resize(intervals.size());

    // 我还需要一个数组来标识某个区间是否使用了

    std::vector<bool> is_used;
    // 这样写不对 不能用reserve 因为reserve只会改变capacity 不会改变size
    // 所以下面的fill实际上什么都不会做 因为数组的大小是零
    // 这里应该用resize
    is_used.resize(intervals.size());
    std::fill(is_used.begin(), is_used.end(), false);

    // 区间按照编号 i = 0 -> n-1
    // 低于每一个区间，我们从0 -> n-1 中选择一个数，放在里面，
    // 同时这个数要在对应的区间中

    // 我这个算法是O(n^2)的 没想到更好的算法

    // 我们从0开始放置，为每一个数字找一个合适的区间

    for (int place_index = 0; place_index < intervals.size(); place_index++) {
        int shortest_interval_index = -1;
        int shortest_interval_length = 1000000;
        for (int interval_index = 0; interval_index < intervals.size();
             interval_index++) {

            // 如果这个区间已经用过了 就跳过
            if (is_used[interval_index]) {
                continue;
            }

            // 我们需要寻找所有包含当前place_index的区间中，right -
            // place_index最短的那个
            // 如果找到了，我们就将palce_index放到这个区间里面，并且在之后的遍历中，不遍历这个区间了
            // 那么一个比较简单的实现方法，就是把这个找出来的区间和数组的首位置(place_index)进行交换
            // 然后下一次迭代的时候从下一个位置开始就ok了
            const Interval& interval = intervals[interval_index];
            // place index 不在区间中
            if (!(place_index >= interval.left &&
                  place_index <= interval.right)) {
                continue;
            }

            // place index 在区间中
            int interval_length = interval.right - place_index;
            if (interval_length < shortest_interval_length) {
                shortest_interval_length = interval_length;
                shortest_interval_index = interval_index;
            }
        }

        // 我们有可能找不到满足条件的区间
        if (shortest_interval_index == -1) {
            return {};
        }

        // 我们找到了对应的区间
        // 但问题是，我们可以进行区间的交换吗？
        // 我们交换过之后，区间的顺序就不对了呀
        // 想一想 我们的答案要求我们输出什么
        // 我们不能改动 intervals 数组 否则就无法对应上正确的interval index了
        is_used[shortest_interval_index] = true;
        placements[shortest_interval_index] = place_index;
    }

    return placements;
}

int main() {
    int n = 0;
    while (std::cin >> n) {
        if (n == 0) {
            break;
        }

        // 准备两个数组
        std::vector<Interval> xs;
        std::vector<Interval> ys;
        for (int _ = 0; _ < n; _++) {

            int xl = 0;
            int xr = 0;
            int yl = 0;
            int yr = 0;

            // 这里还有一个问题
            // 就是输入的都是从1开始的
            // 但是我们的算法都是从0开始的
            // 所以都要减去1
            std::cin >> xl >> yl >> xr >> yr;
            xs.push_back(Interval{xl - 1, xr - 1});
            ys.push_back(Interval{yl - 1, yr - 1});
        }

        std::vector<int> x_placement = PlacePoint(xs);
        std::vector<int> y_placement = PlacePoint(ys);
        if (x_placement.empty() || y_placement.empty()) {
            std::cout << "IMPOSSIBLE\n";
        } else {
            for (int i = 0; i < n; i++) {
                std::cout << x_placement[i] + 1 << " " << y_placement[i] + 1
                          << "\n";
            }
        }
    }
}