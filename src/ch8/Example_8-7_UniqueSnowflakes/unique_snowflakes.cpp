// 2024/11/16
// zhangzhong

// 这个题目有两种解法，一种利用set 一种利用map
// 因为这个题目非常经典 我决定用两种解法 都实现一下

#include <iostream>
#include <set>
#include <vector>

// 用set的方法实现
int GetMaximumContinuousDifferentSequenceBySet(
    const std::vector<int>& sequence) {

    int max_length = 0;
    int left = 0;
    int right = 0;

    std::set<int> curr_snowflakes;

    while (left < sequence.size() && right < sequence.size()) {

        // 看一下right指定的元素是不是在当前的集合里
        int snowflake = sequence[right];

        auto iter = curr_snowflakes.find(snowflake);
        if (iter == curr_snowflakes.end()) {
            // 当前的雪花不在集合中，那么将这个雪花加入集合中，并且right++
            curr_snowflakes.insert(snowflake);
            right++;
        } else {

            // 新的问题来了
            // 什么时候统计序列呢
            // 只有当我们碰到重复的时候，和跳出循环的时候，才需要统计序列长度
            int length = right - left;
            if (length > max_length) {
                max_length = length;
            }

            // 否则我们就需要将left向右，直到碰到right
            while (left < right) {
                int snowflake = sequence[left];
                curr_snowflakes.erase(snowflake);
                left++;

                // [[TIP]]
                // 我们不断的删除left指向的元素
                // 直到删除与right重复的元素
                // 想象我们是rust 上面left已经被修改了，这里再访问left很容易出错
                // 所以使用一个临时变量来保存旧的元素
                if (snowflake == sequence[right]) {
                    break;
                }
            }
        }
    }

    int length = right - left;
    if (length > max_length) {
        max_length = length;
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

        int max_length = GetMaximumContinuousDifferentSequenceBySet(snowflakes);

        std::cout << max_length << "\n";
    }
}
