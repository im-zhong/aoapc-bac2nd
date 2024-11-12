// 2024/11/12
// zhangzhong

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    int minTaps(int n, vector<int>& ranges) {
        // 这道题目确实是区间覆盖，但是贪心是O(nlogn)的时间复杂的

        // 首先构造区间
        vector<vector<int>> intervals;
        for (int i = 0; i <= n; i++) {
            vector<int> interval{i - ranges[i], i + ranges[i]};
            intervals.push_back(interval);
        }

        // 按照左侧区间端点进行排序
        std::sort(intervals.begin(), intervals.end(),
                  [](const std::vector<int>& lhs, const std::vector<int>& rhs) {
                      return lhs[0] < rhs[0];
                  });

        const int min = -1000000;

        int left = 0;
        const int right = n;
        int max_right = min;
        int interval_count = 0;
        for (int i = 0; i < intervals.size(); i++) {
            const auto& interval = intervals[i];
            // 我们已经覆盖了整个区间
            if (left >= right) {
                break;
            }

            // 有些区间 left = right
            // 这种废物区间应该直接跳过
            // 这个也可以不用管
            // if (interval[0] == interval[1]) {
            //     continue;
            // }

            // oooo!!!
            // 还有一种情况
            // 就是整个区间都在代覆盖区间的左侧
            // 这种也应该直接跳过
            // if (interval[1] <= left) {
            //     continue;
            // }
            // 不应该提前跳过，后序会处理的
            // 因为后序会拿到max_right
            // 如果最终的max_right <= left 那么会直接return -1

            // 如果我们最小的区间的左侧无法覆盖
            // 那么看看我们是否已经选择了一个合适的区间
            // 如果没有
            // 则说明整个区间无法被完全覆盖 直接return
            if (interval[0] > left) {
                if (max_right != min) {
                    // 到这里说明我们选择了这个区间
                    // 如果当前的max_right 比left还要小呢？
                    // 说明我们根本就没有覆盖上啊
                    if (max_right <= left) {
                        return -1;
                    }
                    // [[BUG]]
                    // 真正的bug出现在对最后一个区间的处理
                    // 当我们的max_right指向最后一个区间时
                    // 我们的遍历结束了
                    // 但是没有一个额外的区间来帮助我们触发这个条件
                    // 我们需要在循环外面主动处理
                    interval_count++;
                    left = max_right;
                    max_right = min;

                    // 不对啊，当前区间忘了处理了呀。。。
                    i--;
                } else {
                    return -1;
                }
            } else {
                // interval.left <= left
                if (interval[1] > max_right) {
                    max_right = interval[1];
                }
            }
        }

        // [[BUG]]
        // 这种循环完成之后还需要额外处理的情况实际上非常多，应该格外注意
        if (max_right != min) {
            // 还有最后一个区间需要处理
            if (max_right <= left) {
                return -1;
            }
            interval_count++;
            left = max_right;
            max_right = min;
        }

        // 看看最中有没有覆盖整个区间
        if (left >= right && interval_count > 0) {
            return interval_count;
        }
        return -1;
    }
};

int main() {
    int n = 7;
    std::vector<int> ranges = {1, 2, 1, 0, 2, 1, 0, 1};

    int count = Solution{}.minTaps(n, ranges);
    std::cout << count << std::endl;
}