// 2024/11/10
// zhangzhong

#include <algorithm>
#include <vector>

// 1. 最优装载
// 给出n个物体，第i个重量为Wi，选择尽量多的物体，使得总重要不超过C
// 非常显然的贪心算法，因为要选择尽量多的物体，所以每次都选择最小的那个，直到装不下为止
int BestLoad(std::vector<int> bags, int max_weight) {
    // 首先按照重量从小到大排序
    // 哎，但是排完序之后 索引的位置就不对了呀
    // c++有间接排序吗？

    // 还有一个方法，就是建堆 O(n)
    // 但是就算是建堆，也无法保存索引啊
    // 所以如果想返回原数组的索引，那么需要写一个struct，保存索引和重量
    // 然后根据重量排序，最终返回索引
    // 还有一个简单的方法就是返回物体的个数
    // 这个比较简单，咱们返回这个
    int count = 0;

    std::sort(bags.begin(), bags.end());
    int weight = 0;
    for (auto iter = bags.begin(); iter != bags.end(); iter++) {
        if (weight + *iter > max_weight) {
            // return count;
            break;
        }

        weight += *iter;
        count++;
    }
    return count;
}

// 2. 部分背包
// 给出n个物体，第i个重量为Wi，价值为Vi，在总重量不超过C的情况下，让总价值近可能高
// 这样我们就按照性价比排序即可， Vi/Wi, 单位重量的价值，从大到小排序
// 然后直到重量为C

struct Object {
    double weight;
    double value;

    // 我们需要实现一个比较函数，这样才能用于sort

    friend bool operator<(const Object& lhs, const Object& rhs) {
        // 按照性价比排序
        return (lhs.weight / lhs.value) < (rhs.weight / rhs.value);
    }
};

double PartialBag(const std::vector<double>& weights,
                  const std::vector<double>& values, double max_weight) {

    std::vector<Object> objs;
    for (int i = 0; i < weights.size(); i++) {
        objs.push_back(Object{weights[i], values[i]});
    }

    std::sort(objs.begin(), objs.end());

    double current_weight = 0;
    double value = 0;
    // 因为我们是按照性价比从小到大排的
    // 所以要倒着遍历
    for (auto iter = objs.rbegin(); iter != objs.rend(); iter++) {
        if (current_weight + iter->weight > max_weight) {
            // 因为物体是可以分开的，所以我们需要加上部分物体的价值
            double delta_weight = max_weight - current_weight;
            double ratio = delta_weight / iter->weight;
            value += iter->value * ratio;
            current_weight = max_weight;
            break;
        }

        current_weight += iter->weight;
        value += iter->value;
    }
    return value;
}

// 这两个算法都相当的简单，leetcode上没有这么简单的题
// 背包相关的都是动态规划题目
// 在这里咱简单写写吧

int main() {}