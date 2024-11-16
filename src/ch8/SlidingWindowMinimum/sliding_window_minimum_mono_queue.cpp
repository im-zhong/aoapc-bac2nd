// 2024/11/16
// zhangzhong

#include <deque>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> sequence = {5, 2, 6, 8, 10, 7, 4};

    // 使用双端队列实现

    // 因为我们需要在队尾插入和删除元素

    // https://devblogs.microsoft.com/oldnewthing/20230809-00/?p=108577
    std::deque<std::pair<int, int>> q;

    // 同样是滑动窗口遍历序列
    int window_size = 4;

    int minimum_sum = 0;

    // 现在唯一的问题就是如何启动
    // 最开头的前四个元素我们也按照下面的逻辑放到q中
    // 但是这样的代码写出来就不好看
    // 怎么才能写到一块呢？
    // 其实是写不到一块取的
    // 更合理的逻辑是把下面对这个队列的操作单独提取出来
    // 变成一个push操作
    for (int i = 0; i < window_size; i++) {
        int rear = sequence[i];

        // 下面这段话 就是单调队列的push操作
        while (!q.empty() && q.back().first > rear) {
            q.pop_back();
        }
        q.push_back({rear, i});
    }
    minimum_sum += q.front().first;

    // 现在结果就对了，如果是工程上写代码，我绝对不会用这种方法
    for (int i = 1; i + window_size <= sequence.size(); i++) {

        // 相较于之前的基于优先队列的方法，这里的处理要稍微麻烦一些

        // 忘了pop了 不好意思
        // 这里不对的，我们不知道什么才能pop
        // 这个队列还必须保存每个元素在原数组中的索引才行
        // 只有当滑动窗口超过去的时候才能进行pop
        // 快的算法编程起来就麻烦，所以那种又快又好写的算法实在是可遇而不可求啊
        if (q.front().second < i) {
            q.pop_front();
        }

        // 当我们拿到一个新的队尾元素时
        // 我们需要向前比较，所有比当前元素大的元素都需要排除掉
        int rear = sequence[i + window_size - 1];
        while (!q.empty() && q.back().first > rear) {
            q.pop_back();
        }
        q.push_back({rear, i});

        // 然后当前窗口的最小值就是对首
        minimum_sum += q.front().first;
    }

    std::cout << minimum_sum << std::endl;
}
