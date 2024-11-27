// 2024/11/27
// zhangzhong

#include <algorithm>
#include <iostream>
#include <vector>

struct Lamp {
    int voltage;
    int source_cost;
    int lamp_cost;
    int requirement;

    // 数组需要按照电压排序

    friend bool operator<(const Lamp& lhs, const Lamp& rhs) noexcept {
        return lhs.voltage < rhs.voltage;
    }
};

int GetMinimumCost(std::vector<Lamp>& lamps) {
    int lamp_count = lamps.size();

    // place holder for the index = 0
    // 因为下面的所有讨论都是建立在下标从1开始的
    lamps.push_back(Lamp{0, 0, 0, 0});

    // 一维dp

    // 0. 将lamps按照电压排序
    std::sort(lamps.begin(), lamps.end());

    // 2. 定义状态为
    // minimum_cost[i] 表示 从1..=n种的灯的最低开销
    // 显然 solution = minimum_cost[lamps.size()]
    // 这道题目用了一个非常nice的处理方法
    // 每当我们引入一种新的灯
    // 我们需要尝试所有的替换方案
    // 也就是用一个j将现有的序列 1..=i 切分成 1..j..i
    // 然后在内层循环中遍历j 寻找i的最优解
    // 这种处理方法我记得在学马尔可夫链的时候也用到了
    // ok
    // 准确的写出转移方程
    // 规定minimum_cost[0] = 0,
    // 用于表示我们用当前电源把所有之前的灯泡的电源都替换了
    // 我们还需要当前种类之前的所有灯泡的数量
    // 我们用同样的方式处理区间灯泡数量的计算
    // 我竟然想出了这么好用的trick 我真厉害！

    // lamp的下标从1开始的
    std::vector<int> lamp_counts(lamp_count + 1, 0);
    // 下标从1开始
    for (int i = 1; i <= lamp_count; i++) {
        lamp_counts[i] = lamps[i].requirement + lamp_counts[i - 1];
    }

    // 傻逼了 要求最小值 算成最大值了
    // 那这样的话 都要初始化成一个大数才行
    const int INF = 1 << 30;

    // dp state
    std::vector<int> minimum_cost(lamp_count + 1, INF);
    minimum_cost[0] = 0;
    // 从前往后算
    for (int i = 1; i <= lamp_count; i++) {
        for (int j = 0; j < i; j++) {
            minimum_cost[i] = std::min(minimum_cost[i],
                                       minimum_cost[j] +
                                           (lamp_counts[i] - lamp_counts[j]) *
                                               lamps[i].lamp_cost +
                                           lamps[i].source_cost);
        }
    }

    return minimum_cost[lamp_count];
}

int main() {

    int category = 0;
    while (std::cin >> category) {
        if (category == 0) {
            break;
        }

        std::vector<Lamp> lamps;
        for (int i = 0; i < category; i++) {
            Lamp lamp;
            std::cin >> lamp.voltage >> lamp.source_cost >> lamp.lamp_cost >>
                lamp.requirement;
            lamps.push_back(lamp);
        }

        int minimum_cost = GetMinimumCost(lamps);
        std::cout << minimum_cost << "\n";
    }
}