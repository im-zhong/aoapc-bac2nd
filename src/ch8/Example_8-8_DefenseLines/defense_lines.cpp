// 2024/11/17
// zhangzhong

#include <iostream>
#include <vector>

int GetLongestIncreasingSequenceLength(const std::vector<int>& towers) {

    // 首先求两个数组
    // 一个是以当前元素为tail元素的连续序列的长度
    // 一个是以当前元素为head元素的连续序列长度

    std::vector<int> tail;
    tail.resize(towers.size());

    // 只需要O(n)的时间就可以算出来
    // 累计当前的最长长度即可
    // 一旦出现断裂 重置即可
    int last = -100000;
    int current_length = 0;
    for (int i = 0; i < towers.size(); i++) {
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
    std::vector<int> head;
    head.resize(towers.size());
    for (int i = towers.size() - 1; i >= 0; i--) {
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
    for (int i = 0; i < towers.size(); i++) {
        for (int j = i + 1; j < towers.size(); j++) {
            // [[BUG]]
            if (towers[i] < towers[j]) {
                // 枚举的时候还要判断一个条件
                // 就是序列整体得是有序的
                max_length = std::max(max_length, tail[i] + head[j]);
            }
        }
    }

    return max_length;
}

int main() {
    int case_count = 0;
    std::cin >> case_count;

    for (int c = 0; c < case_count; c++) {
        int tower_count = 0;
        std::cin >> tower_count;

        std::vector<int> towers;
        for (int t = 0; t < tower_count; t++) {
            int tower_height = 0;
            std::cin >> tower_height;
            towers.push_back(tower_height);
        }

        int length = GetLongestIncreasingSequenceLength(towers);
        std::cout << length << "\n";
    }
}
