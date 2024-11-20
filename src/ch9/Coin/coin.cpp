// 2024/11/19
// zhangzhong

#include <iostream>
#include <vector>

// 有n种硬币，面值分别为V1, V2, V3, ... 每种都有无限多
// 给定非负整数S，可以选用多少个硬币，使得面值之和恰好为S
// 输出硬币数目的最小值和最大值

int CoinChange(std::vector<int> coins, int amount) {

    // 状态就是amount，可选的状态是 0, ..., amount
    // 每一步就是减去可选的钱的数量
    // 这样整张图就是一个隐式图

    // dp的题大多都有两种写法，一种是记忆化搜索(递归+保存子问题解)
    // 然后就是递推，循环
    // 一般也是递推更快
    // 我们这里两种解法都写一下

    return 0;
}

// 先写递归的吧
// 求最长路及其字典序

// 先不求字典序了，先只求最长路
// dp
// 首先i是什么，是零钱，我们最开始的零钱是S，也就是这个distance数组的最后一个位置
// 先定义distance[i]表示以i为起点的距离{距离就是边的个数}, 终点就是s=0
// distance[i] = 1 + max(distance[j]), 边i->j存在

// 不对，咱们先写最简单的递归，没有distance数组
class CoinChangeSolver {

  public:
    int CoinChange(std::vector<int>& coins, int amount) {

        // explicit vector(size_type count)
        //  3) Constructs a vector with count default-inserted objects of
        //         T. No copies are made.
        //  If T is not DefaultInsertable into std::vector<T>, the behavior is
        //  undefined.
        //
        // explicit vector(size_type count, T value)
        // 4) Constructs a vector with count copies of elements with value
        // value. If T is not CopyInsertable into std::vector<T>, the behavior
        // is undefined.
        // 所以这两个实际上可以代替我们自己 先声明 再resize 在循环然后初始化
        // 要好的多
        // nice!

        // create n elements and initialize by default(0, false)
        std::vector<int> distances(amount + 1);
        // 我想知道这样会初始化吗？
        std::vector<bool> visited(amount + 1);

        int distance = dp(amount, coins, distances, visited);
        if (distance >= 1 << 30) {
            return -1;
        } else {
            return distance;
        }
    }

    // 用递归做dp实在是不占便宜
    int dp(int remain_amount, std::vector<int>& coins,
           std::vector<int>& distances, std::vector<bool>& visited) {

        // 如果remain_amount < 0 , 那么就是递归结束条件
        if (remain_amount <= 0) {
            return 0;
        }

        // 我们使用一个数组来保存distance 防止持续的重复计算
        // 还要记得 递归结束条件在最开始 才是对的

        if (visited[remain_amount]) {
            return distances[remain_amount];
        }
        visited[remain_amount] = true;

        int distance = 1 << 30;
        // 然后遍历所有邻接节点
        // 如果我们没有没有邻接节点了，我们应该返回什么？
        // 应该返回一个非常大的数，表示这个东西的距离是无限大
        // 并且在最终返回的时候，我们需要判断，如果超过这个最大数，代表没有路径可以选择
        for (int coin : coins) {
            if (remain_amount >= coin) {
                // 边存在，也就是零钱可以扣除
                // 因为这里可以选择的不止两个，所以需要在循环里，每一次循环都算一次min
                distance =
                    std::min(distance, 1 + dp(remain_amount - coin, coins,
                                              distances, visited));
            }
        }
        distances[remain_amount] = distance;
        return distance;
    }

    // 然后用递推的方式进行计算
    // 递推就是把状态转移方程倒过来进行计算
    // 然后要给distance数组来一个初始值，从那个初始值开始计算
    // 在这个题目里，显然初始值应该是amount=0
    // distance[0] = 0
    // 因为distance表示从0开始到终点的长度 0就是终点 所以distance是ling
    int dp_for_min(std::vector<int>& coins, int amount) {
        std::vector<int> distances(amount + 1);
        distances[0] = 0;

        // 我们要怎么计算这个distance数组呢？
        // 这里用s更好，表达的是状态
        // 或者用一个另外的词
        // 我们的钱就是状态，所以更好的词就是amount
        // 可惜的是 这个单词已经被用作入参了 所以还是用state吧
        for (int state = 1; state <= amount; state++) {
            // d就是distance，我们遍历的就是状态
            // 我们要计算的这个状态所依赖的状态一定已经都算出来了

            int distance = 1 << 30;
            // 我们只需要遍历所有的coins
            for (int coin : coins) {
                if (state - coin >= 0) {
                    // 那么说明我们可以转移到状态 d-coin
                    // 那么d的值就是这些值中最小的那一个
                    distance = std::min(distance, 1 + distances[state - coin]);
                }
            }
            distances[state] = distance;
        }
        // 最终返回最后一个的距离即可
        // [[BUG]] 忘了可能没有答案了，还要检测并返回-1
        if (distances[amount] >= 1 << 30) {
            return -1;
        } else {
            return distances[amount];
        }
    }

    // 现在写一下用递推的方式完成最长路径的实现
    int dp_for_max(std::vector<int>& coins, int amount) {

        // 仍然用distance[s]表示从状态s开始的最长路径
        // 则 distance[s] = 1 + max(distance[j]), 边s->j存在
        // 所以倒过来算

        std::vector<int> distances(amount + 1);
        // 而且默认值全部初始化为零

        for (int state = 1; state <= amount; state++) {
            // 遍历所有的邻接节点
            int distance = -(1 << 30);
            for (int coin : coins) {
                // 如果当前状态可以通过一条边到达某个已知状态
                // state - coin >= 0
                if (state - coin >= 0) {
                    // 说明边存在
                    distance = std::max(distance, 1 + distances[state - coin]);
                }
            }
            // 遍历完当前state的所有邻接节点之后
            // 我们就得到了它所有的路径中最长的
            distances[state] = distance;
        }

        // 最终返回起点的distance，记得处理特殊情况
        if (distances[amount] <= -(1 << 30)) {
            return -1;
        } else {
            return distances[amount];
        }
    }

    // 可以看到求最长路和最短路的代码是非常相似的 所以他们可以放到一块
    // 不过要声明两个distance数组分别保存最长路和最短路
    // 同时加上加上打印路径的部分 达到对例题的充分理解
    void dp_for(std::vector<int>& coins, int amount) {
        std::vector<int> min_distances(amount + 1, 0);
        std::vector<int> max_distances(amount + 1, 0);

        // 用于记录需要打印的路径
        // -1 表示路径结束了
        std::vector<int> min_paths(amount + 1, -1);
        std::vector<int> max_paths(amount + 1, -1);

        for (int state = 1; state <= amount; state++) {

            // 因为这里需要打印的是coin对应的下标？
            // 也不是吧 就是coin吧
            // 所以还是直接遍历coin
            int min_distance = 1 << 30;
            int max_distance = -(1 << 30);
            for (int coin : coins) {
                if (state - coin < 0) {
                    continue;
                }

                // 根据情况是否更新 min_distance
                int current_distance = 1 + min_distances[state - coin];
                if (current_distance < min_distance) {
                    min_distance = current_distance;
                    // 记录我们选择了边 state -> {state-coin}
                    // 其实就是记录状态之间的跳转
                    // 到时候倒序从amount开始依次跳转即可打印路径
                    min_paths[state] = state - coin;
                }

                // 计算最长路，和上面计算最短路逻辑上是非常相似的
                current_distance = 1 + max_distances[state - coin];
                if (current_distance > max_distance) {
                    max_distance = current_distance;
                    max_paths[state] = state - coin;
                }
            }
            // 最终别忘了在这里更新 distances数组
            min_distances[state] = min_distance;
            max_distances[state] = max_distance;
        }
    }

    int max_amount;
};

int main() {
    std::vector<int> coins{1, 2, 5};
    int amount = 11;

    CoinChangeSolver ccs;
    int distance = ccs.CoinChange(coins, amount);
    std::cout << distance << std::endl;

    distance = ccs.dp_for_min(coins, amount);
    std::cout << distance << std::endl;
}
