// 2024/11/26
// zhangzhong

#include <iostream>
#include <vector>

// 有很多DP题目的状态定义都可以是对称的，尤其是DAG的题目
// 这两道背包题都是对称的

// 完全背包
// 有一个容量为Capacity的背包
// 有n种物品，每种都有无限个，分别为数组Volumes，重量数组Weights
// 要求能放到背包中的最大重量

int CompeleteBag(int capacity, const std::vector<int>& volumes,
                 const std::vector<int>& weights) {
    // 完全背包问题和之前学到的硬币问题非常相似
    // 他的状态空间是一维的
    // 我们用 max_weight[volume] 来表示当背包的剩余空间为volumes的时候
    // 能够放到背包中的最大重量
    // 初始状态：max_weight[0] = 0
    // 计算顺序：正着算
    // 答案：max_weight[capacity]
    // 状态转移方程 max_weight[volume] = max(0, volumes[sth.] <= volume,
    // weights[sth.] + max_weight[volume-volumes[sth.]])
    // 如果当前的容量放不下任何物品，那么背包能放下的最大重量只能是零

    std::vector<int> max_weight(capacity + 1, 0);

    for (int volume = 1; volume <= capacity; volume++) {

        // 获得引用，下面的代码更易读
        int& mw = max_weight[volume];

        // 遍历所有的物品
        for (int t = 0; t < volumes.size(); t++) {
            if (volumes[t] <= volume) {
                // 如果该物品能放下
                mw = std::max(mw, weights[t] + max_weight[volume - volumes[t]]);
            }
        }
    }

    return max_weight[capacity];
}

// 0-1 背包
// 有一个容量为Capacity的背包
// 有n个物品，分别为数组Volumes，重量数组Weights
// 要求能放到背包中的最大重量

int ZeroOneBag(int capacity, const std::vector<int>& volumes,
               const std::vector<int>& weights) {

    // 01背包的状态空间是二维的
    // 我突然意识到 我写这些注释就是写作
    // 简单的想就是顺序的考察每一个物品，决策要不要放入到背包中
    // 对每一个物品的考虑称之为一个阶段 stage
    // 用thing对物品进行索引

    int thing_count = volumes.size();
    // stage = 1, 2, ..., thing_count

    // 状态：max_weight[stage][volume] 表示
    // 在某个阶段，我们已经考虑了前面的一些物品，背包的容量还剩volume的时候，
    // 能够放到背包中的最大重量
    // 那么显而易见的
    // 答案：max_weight[thing_count][capacity]
    // 初始状态：stage = 0, all colums = 0
    // 状态转移方程 max_weight[stage][volume] = max of
    //      1. 我们不要当前的物品 max_weight[stage-1][volume]
    //      2. 如果当前背包的容量放得下，我们要当前的物品 if volume >=
    //      volumes[thing]: weights[thing] + max_weight[stage-1][volume -
    //      volumes[thing]]

    const int max_capacity = 100;
    const int max_stage = 10;

    // 这是个方阵！TMD傻逼了，这怎么会是个方阵呢
    // 第一个维度表示物品的个数
    // 第二个维度表示容量 傻逼
    int max_weight[max_stage][max_capacity];
    // 初始化第一列(stage=0)全部都是0

    for (int stage = 1; stage <= thing_count; stage++) {

        // 不对，我们不需要像完全背包那样，考虑所有的物品
        // 而是考虑当前的物品！
        // 也就是stage表示的物品
        // 哎 也不对呀
        int thing = stage - 1;
        // 不对不对，第二个维度是容量！

        for (int volume = 0; volume <= capacity; volume++) {
            // 我们在不同的容量下，考虑要不要物品

            // 拿到这个东西的引用
            int& mw = max_weight[stage][volume];

            if (volumes[thing] <= volume) {
                // 可以放下当前的物品
                // 我们就尝试把当前物品放下，看看会不会更好
                mw = std::max(mw,
                              max_weight[stage - 1][volume - volumes[thing]] +
                                  weights[thing]);
            } else {
                // 放不下当前的物品
                // 那么就不放了
                mw = max_weight[stage - 1][volume];
            }
        }
    }

    return max_weight[thing_count][capacity];
}