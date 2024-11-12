// 2024/11/11
// zhangzhong

#include <algorithm>
#include <limits>
#include <vector>

// 贪心
// 1.选择不相交区间
// 数轴上有n个开区间(ai, bi), 选择尽量多的区间，使得这些区间互相没有公共点
// 选择第一个区间，选择了一个区间之后，记录它的bi，后面有a<bi的区间直接跳过
// 然后碰到下一个a>bi的，说明是下一个不相交的区间，选择这个区间，然后持续，知道遍历了所有的区间

// 2. 区间选点
// 给出n个闭区间[ai, bi], 选择尽量少的点，在所有区间中

// 这两个问题的解决思路非常相似
// 都是根据b从小到大排序
// 然后顺序遍历一遍, 选择第一个区间的bi
// 后面有a<=bi的区间，全部跳过，知道找到下一个a>bi的，选择这个区间的右端点, loop

struct Interval {
    int left;
    int right;

    friend bool operator<(const Interval& lhs, const Interval& rhs) noexcept {

        // 按照b进行排序
        // 如果b相同，a从大到小排
        if (lhs.right < rhs.right) {
            return true;
        } else if (lhs.right == rhs.right) {
            return lhs.left > rhs.right;
        } else {
            return false;
        }
    }
};

// 为了简单起见，我们都返回所选择的区间数量吧
int DisjointInterval(std::vector<Interval>& intervals) {

    int interval_count = 0;

    std::sort(intervals.begin(), intervals.end());

    // 使用一个变量保存当前的b
    // 那么默认是无穷远处
    int current_right = std::numeric_limits<int>::max();
    for (const auto& interval : intervals) {
        // 所有区间都是开区间
        //
        if (interval.left < current_right) {
            // 这个区间与当前的区间是覆盖或者相交的，跳过
            continue;
        }

        // interval.left >= current_right
        // 是一个新的区间
        interval_count++;
        current_right = interval.right;
    }

    return interval_count;
}

int MinimumCommonPoint(std::vector<Interval>& intervals) {
    int point_count = 0;
    int current_right = std::numeric_limits<int>::max();

    // 不对，和上面的有一点不同，因为我们是闭区间
    // 所以a要 > b 才会开新的
    for (const auto& interval : intervals) {
        if (interval.left > current_right) {
            point_count++;
            current_right = interval.right;
        }
    }

    return point_count;
}

int main() {}