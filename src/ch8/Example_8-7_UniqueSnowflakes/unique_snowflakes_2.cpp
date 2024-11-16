// 2024/11/16
// zhangzhong

// 这个题目有两种解法，一种利用set 一种利用map
// 因为这个题目非常经典 我决定用两种解法 都实现一下
// 用哈希map的速度要快一些

#include <iostream>
#include <unordered_map>
#include <vector>

// 用set的方法实现
int GetMaximumContinuousDifferentSequenceByMap(
    const std::vector<int>& sequence) {

    // 在这里用一个last数组来保存
    std::vector<int> last;
    last.resize(sequence.size());

    std::unordered_map<int, int> curr_snowflakes;
    // 首先计算出last数组

    // 只需要按序遍历sequence即可

    for (int i = 0; i < sequence.size(); i++) {
        int snowflake = sequence[i];
        auto iter = curr_snowflakes.find(snowflake);
        if (iter == curr_snowflakes.end()) {
            // do not find
            // 说明当前的雪花前面没有与自己重复的元素
            last[i] = -1;
        } else {
            // 说明当前的雪花与之前的雪花存在重复
            last[i] = iter->second;
        }

        // 不论如何，我们都需要更新每个雪花最新的索引
        curr_snowflakes[snowflake] = i;
    }

    // 现在有了last数组，问题就简单多了
    int left = 0;
    int right = 0;
    int max_length = 0;
    while (right < sequence.size()) {

        // 只要没有雪花出现的[left, right]中，就不断的将right右移
        while (right < sequence.size() && last[right] < left) {
            right++;
        }

        // 一旦出现，说明有重复的元素出现在[l, r]中, last[right] >= left
        // 计算当前的序列长度
        max_length = std::max(max_length, right - left);

        // 然后将left移到重复数的下一个位置
        left = last[right] + 1;
    }

    return max_length;
}

int main() {

    int case_count = 0;
    std::cin >> case_count;

    for (int c = 0; c < case_count; c++) {

        int snowflake_count = 0;
        std::cin >> snowflake_count;

        std::vector<int> snowflakes;
        for (int i = 0; i < snowflake_count; i++) {
            int snowflake = 0;
            std::cin >> snowflake;
            snowflakes.push_back(snowflake);
        }

        int max_length = GetMaximumContinuousDifferentSequenceByMap(snowflakes);

        std::cout << max_length << "\n";
    }
}
