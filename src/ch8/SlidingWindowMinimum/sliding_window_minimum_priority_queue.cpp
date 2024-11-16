// 2024/11/16
// zhangzhong

#include <iostream>
#include <set>

// 问题：
// 输入正整数k和长度为n的序列
// 定义f(i) = min{Ai, Ai=1 ,, ... } 连续k个数的最小值
// 要求计算f(0), f(1), ... f(n-k+1)
// 为了方便起见，我们的算法输出这些个最小值的和吧

// 如果是输出连续k个数的和呢？那么同样使用滑动窗口解决，只不过每次滑动的时候，需要减去头部的值，加上尾部的值

int main() {
    std::vector<int> sequence = {5, 2, 6, 8, 10, 7, 4};

    std::set<int> set;

    int window_size = 4;

    int minimum_sum = 0;
    // 下面的循环不好写
    // 咱们手动把初始状态写一下，也就是先把前4个元素放到pg中
    for (int i = 0; i < window_size; i++) {
        set.insert(sequence[i]);
    }
    minimum_sum += *set.begin();

    for (int i = 1; i + window_size <= sequence.size(); i++) {
        // 然后我们直接从第二个窗口开始
        // 哦！不对，我们需要的是支持删除任意元素的优先队列
        // 也就是实际上我们需要的是一个map!
        // set就行。。。无语了 根本就不是优先队列 家人们
        // 首先把i-1给去掉
        set.erase(sequence[i - 1]);

        // 然后把新加入的元素给加进去
        // i + window_size - 1
        set.insert(sequence[i + window_size - 1]);

        // 然后加上这个最小值
        minimum_sum += *set.begin();
    }

    std::cout << minimum_sum << std::endl;
}