// 2024/10/31
// zhangzhong

// 先写最简单的方式 枚举

#include <cassert>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <numeric>
#include <ostream>
#include <random>
#include <system_error>

struct Result {
    int begin;
    int end;
    int64_t sum;
};

// 重载一些cout的运算符
std::ostream& operator<<(std::ostream& out, const Result& result) {
    out << "[" << result.begin << ":" << result.end << "] = " << result.sum;
    return out;
}

// O(n^3)
Result MaximumContinuousSumV1(const int64_t* array, size_t size) {

    // 枚举所有range
    // 最好是用0，有可能我们的最大和都是负数
    // 所以最好用 int64_t的最小值
    // 或者是array的值
    int64_t max_sum = std::numeric_limits<int64_t>::min();
    int max_begin = 0;
    int max_end = 0;

    for (int begin = 0; begin < size; begin++) {
        for (int end = begin + 1; end < size + 1; end++) {
            // 计算range内的和

            int64_t sum = 0;
            for (int i = begin; i < end; i++) {
                sum += array[i];
            }

            if (sum > max_sum) {
                max_sum = sum;
                max_begin = begin;
                max_end = end;
            }
        }
    }

    return Result{max_begin, max_end, max_sum};
}

// O(n^2)
Result MaximumContinuousSumV2(const int64_t* array, const size_t size) {

    // 首先计算出钱i项和
    int64_t first_n_term_sums[size + 1];

    first_n_term_sums[0] = 0;
    // 不对，我们仍然要遍历整个数组
    // 也就是从零开始
    // 但是前n项和数组要从1 开始 因为0已经被占了
    for (int i = 0; i < size; i++) {
        first_n_term_sums[i + 1] = first_n_term_sums[i] + array[i];
    }

    int64_t max_sum = std::numeric_limits<int64_t>::min();
    int max_begin = 0;
    int max_end = 0;
    // 然后 sum[i:j] = s[j] - s[i];
    for (int begin = 0; begin < size; begin++) {
        for (int end = begin + 1; end < size + 1; end++) {
            int64_t sum = first_n_term_sums[end] - first_n_term_sums[begin];

            if (sum > max_sum) {
                max_sum = sum;
                max_begin = begin;
                max_end = end;
            }
        }
    }

    return Result{max_begin, max_end, max_sum};
}

int64_t ImplMaximumContinuousSumV3(const int64_t* array, int begin, int end) {
    if (end - begin == 1) {
        return array[begin];
    }

    int middle = begin + ((end - begin) / 2);

    // 子问题
    int64_t max_sub_sum =
        std::max(ImplMaximumContinuousSumV3(array, begin, middle),
                 ImplMaximumContinuousSumV3(array, middle, end));
    // 然后寻找跨中点的最大序列
    // begin -> middle，我们向前寻找

    int64_t max_left_sum = std::numeric_limits<int64_t>::min();
    // 我们需要一个数组来保存这些和呀，否则无法在O(n)的时间内完成
    // 不对，因为我们不需要所有的数字
    // 所以只需要一个额外的值保存当前的钱n项和即可！
    int64_t current_sum = 0;
    for (int i = middle - 1; i >= begin; i--) {
        current_sum += array[i];
        max_left_sum = std::max(max_left_sum, current_sum);
    }

    // middle -> end, 我们向后寻找
    current_sum = 0;
    int64_t max_right_sum = std::numeric_limits<int64_t>::min();
    for (int i = middle; i < end; i++) {
        current_sum += array[i];
        max_right_sum = std::max(max_right_sum, current_sum);
    }

    return std::max(max_sub_sum, max_left_sum + max_right_sum);
}

// O(nlogn)
int64_t MaximumContinuousSumV3(const int64_t* array, const size_t size) {

    // 使用分治的思想

    // 每次将序列分成两个子序列
    // 子序列会返回该序列中和最大的序列
    // 然后我们会寻找跨中点的序列
    // [[TIPS]]
    // 跨中点的最大的序列一定是从中点开始向左最大的加上从中点开始向右最大的
    // 确实是这样
    // 用反证的思路想一下就很简单
    //
    // 然后递归结束的条件就是序列只有一个元素，直接返回自身就行
    return ImplMaximumContinuousSumV3(array, 0, size);
}

// ok, 最后一种，O(n)
// 这一个最快 但是最难写正确了
Result MaximumContinuousSumV4(const int64_t* array, const size_t size) {
    // 首先计算前n项和
    // 统计注意统计最小的钱n项和
    int64_t min_sum = std::numeric_limits<int64_t>::max();

    int64_t first_n_term_sums[size + 1];

    first_n_term_sums[0] = 0;
    for (int i = 0; i < size; i++) {
        first_n_term_sums[i + 1] = first_n_term_sums[i] + array[i];
    }

    // 我们把两个循环分开写，这样更好写
    // 其实这一步的操作，就是循环然后记录看到的最小值
    int64_t min_first_sums[size + 1];
    min_first_sums[0] = 0;
    min_sum = std::numeric_limits<int64_t>::max();
    int min_sum_end = 0;

    for (int i = 1; i <= size; i++) {
        if (first_n_term_sums[i] < min_sum) {
            min_sum = first_n_term_sums[i];
            min_sum_end = i;
        }

        min_first_sums[i] = min_sum_end;
    }

    // 感觉不太对啊
    // 如果所有项加起来的和最小呢？
    // 我这个实现非常明显的不对啊。。。
    // 将序列的第一个值作为初始值
    int64_t max_sum = first_n_term_sums[1];
    int max_begin = 0;
    int max_end = 1;
    // for (int end = min_end + 1; end < size + 1; end++) {
    //     // max_sum = std::max(max_sum,
    //     //                    first_n_term_sums[end] -
    //     //                    first_n_term_sums[min_end]);
    //     int sum = first_n_term_sums[end] - first_n_term_sums[min_end];
    // }
    // 哎！
    // 我们确实需要在遍历一次数组
    // 因为上述条件只在j确定是成立
    // 但是我们怎么在O(1)的时间内，知道从0到j中最小的S呢
    // 对了
    // 我们使用一个数组，保存在每一步的最小的S即可！
    // nice/
    // 这样我们可以在O(1)的时间内确定在j确定时的最大的和
    // 然后记录最大的和即可
    // 这样算法整体就有两个单层的循环，就是O(n)

    // 同时从第二个值开始
    for (int end = 2; end <= size; end++) {
        // begin = 0

        // 当前end确定的情况下的最大和为
        // 不对啊，这样我们无法输出range了
        // 所以min_first_sums需要保存range
        // ，然后我们可以根据first_n_terms_sum来找到对应的和
        int begin = min_first_sums[end];

        // 有一个特殊的情况，就是当前序列内的最小和就是整个序列
        // 这种情况如何处理?
        // 这种情况直接跳过就行了
        // 因为 如果 [0:end] 全序列加起来最小
        // 那么最大的序列一定出现在[0:end-1]
        // 而算法始终保证[0:end-1]的最大序列已经找到（通过初始赋值 int64_t
        // max_sum = first_n_term_sums[1]; 和 for循环 一步一步的求解来保证）
        // 所以直接跳过就是正确的
        if (begin == end) {
            continue;
        }

        int sum = first_n_term_sums[end] - first_n_term_sums[begin];
        // sum还需要和[0:end]
        // 即整个序列的和，因为这个算法的假设中，那个最小的序列始终存在，即不是零
        // 但是在有些时候，可能是零，所以需要比较
        if (sum < first_n_term_sums[end]) {
            sum = first_n_term_sums[end];
            begin = 0;
        }
        if (sum > max_sum) {
            max_begin = begin;
            max_end = end;
            max_sum = sum;
        }
    }

    return Result{max_begin, max_end, max_sum};
}

// 无意中找到一个非常简单但是异常高效的算法
int64_t MaximumContinuousSum(const int64_t* array, size_t size) {

    int64_t max_sum = array[0];
    int64_t current_sum = 0;

    for (int i = 0; i < size; i++) {
        if (current_sum > 0) {
            current_sum += array[i];
        } else {
            current_sum = array[i];
        }

        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
    }

    return max_sum;
}

void TestByRandomGeneration() {

    const int number_count = 1024;
    std::default_random_engine e(
        std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int64_t> u(-10, 10);

    int test_count = 10000;
    for (int i = 0; i < test_count; i++) {
        int64_t numbers[number_count] = {};
        for (int i = 0; i < number_count; i++) {
            numbers[i] = u(e);
            // std::cout << numbers[i] << ",";
        }
        // std::cout << std::endl;

        Result r1 = MaximumContinuousSumV1(numbers, number_count);
        Result r2 = MaximumContinuousSumV2(numbers, number_count);
        int64_t r3 = MaximumContinuousSumV3(numbers, number_count);
        Result r4 = MaximumContinuousSumV4(numbers, number_count);
        int64_t r = MaximumContinuousSum(numbers, number_count);

        // 四个数字必须完全相等
        // 这个句子要怎么写呢
        // 根据相等的递推性
        // 写三个assert即可
        assert(r1.sum == r2.sum);
        assert(r2.sum == r3);
        assert(r3 == r4.sum);
        assert(r4.sum == r);

        std::cout << "test case: " << i << " done." << std::endl;
    }
}

int main() {

    // 我们随机选择一些数字
    //
    const int number_count = 10;

    // std::default_random_engine e(
    //     std::chrono::system_clock::now().time_since_epoch().count());
    // std::uniform_int_distribution<int64_t> u(-10, 10);

    // int64_t numbers[number_count] = {};
    // for (int i = 0; i < number_count; i++) {
    //     numbers[i] = u(e);
    //     std::cout << numbers[i] << ",";
    // }
    // std::cout << std::endl;

    // std::cout << MaximumContinuousSumV1(numbers, number_count) << std::endl;
    // std::cout << MaximumContinuousSumV2(numbers, number_count) << std::endl;
    // std::cout << MaximumContinuousSumV3(numbers, number_count) << std::endl;
    // std::cout << MaximumContinuousSumV4(numbers, number_count) << std::endl;

    // // 测试一个特殊的例子

    // for (int i = 0; i < number_count; i++) {
    //     numbers[i] = -i;
    //     std::cout << numbers[i] << ",";
    // }
    // std::cout << std::endl;
    // std::cout << MaximumContinuousSumV1(numbers, number_count) << std::endl;
    // std::cout << MaximumContinuousSumV2(numbers, number_count) << std::endl;
    // std::cout << MaximumContinuousSumV3(numbers, number_count) << std::endl;
    // std::cout << MaximumContinuousSumV4(numbers, number_count) << std::endl;

    // 这个竟然也错了！！！
    // 3,-2,3,-3,8,-4,10,-8,-1,7
    int64_t case_3[] = {3, -2, 3, -3, 8, -4, 10, -8, -1, 7};
    std::cout << MaximumContinuousSumV1(case_3, number_count) << std::endl;
    std::cout << MaximumContinuousSumV2(case_3, number_count) << std::endl;
    std::cout << MaximumContinuousSumV3(case_3, number_count) << std::endl;
    std::cout << MaximumContinuousSumV4(case_3, number_count) << std::endl;
    // 终于对了
    // 我需要写一个完整的程序，给出-10到10的所有排列
    // 也就是有20！
    // 有点太多了吼 改成-5到5吧
    // 一共有11个数字
    // 这11个数字需要放在10个位置上
    // 总共有11^10 = 25,937,424,601
    // 我去，感觉测不完啊
    // 算法的输出中，range是不唯一的
    // 所以我们只测试最小值对不对就ok了

    // 而枚举全排列我们使用回溯法
    // 算了，要不还是疯狂的随机吧
    // 随机上1kw次 也足够测试了

    TestByRandomGeneration();
}