// 2024/11/1
// zhangzhong

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <iostream>
#include <random>
#include <semaphore>

// https://en.cppreference.com/w/cpp/algorithm/binary_search
bool BinarySearch(int* array, int begin, int end, int key) {
    while (begin < end) {
        int middle = begin + ((end - begin) / 2);

        // 总共三种情况
        if (array[middle] == key) {
            return true;
        } else if (array[middle] > key) {
            end = middle;
        } else {
            begin = middle + 1;
        }
    }
    return false;
}

// std::lower_bound()
int LowerBoundSimple(int* array, int begin, int end, int key) {

    // 算法会返回最靠前的key所在的位置
    // 或者插入key后 数组仍然有序的位置
    // 不如说，算法会返回所有 >= key的位置中最小的那个
    // 也就是如果我们采取暴力枚举算法的话
    // 其实就是从左向右所搜，碰到的第一个 >= key 的位置
    int i = begin;
    for (; i < end; i++) {
        if (array[i] >= key) {
            return i;
        }
    }
    // 如果整个数组都没有找到，则直接返回i，因为此时i=end
    return i;
}

int LowerBound(int* array, int begin, int end, int key) {
    while (begin < end) {
        // 相较于bianry search，相等的情况不会直接返回，而是继续在左侧区间中搜索
        // 知道算法将区间缩小到只有一个元素，而那个元素对应的位置就是答案
        int middle = begin + ((end - begin) / 2);
        if (array[middle] >= key) {
            // 算法可能的结果是[begin, middle], 注意是左闭右闭的
            end = middle;
        } else {
            // 否则下界一定在右侧 也就是[middle+1, end]
            begin = middle + 1;
        }
    }
    // 最终返回beign, 此时实际上begin + 1 = end
    // 也就是区间里只有一个元素，而begin就是那个元素的索引
    return begin;
}

// lower_bound和upper_bound可能返回的区间都是[begin, end] 左闭右闭
int UpperBoundSimple(int* array, int begin, int end, int key) {

    // 找到所有 <= key 的元素中，最靠右的那个
    // 也就是说，从右向左找，第一个 <= key的元素
    // 如果找不到，那么久返回begin
    // 这样才是对的吧
    // 这样才有可能返回 begin..=end
    int i = end;
    for (; i > begin; i--) {
        if (array[i - 1] <= key) {
            // 而在这里，反而要加上1
            return i;
        }
    }
    return i;

    // 卧槽，这么短短的几行代码，感觉case非常多啊
    // 1. begin >= end, 此时 i = end, 返回i 合理，表示没有找到
    // 2. begin < end
    //   2.1 all_number <= key
    //      程序刚进入循环，条件就成立, 此时 i = end -1,
    //      也就是最后一个元素，成立，返回i 也就是end 合理
    //    2.2 key < all_number
    //      程序在整个循环中，都不成立 最后一次循环是 i = begin + 1,
    //      array[begin] 范围ok, 然后i--, i = begin, i > begin false 跳出循环
    //      此时i = begin, 返回begin，合理
    //      2.3 ... <= key <= ...
    // 那么此时就非常好分析了，就是从后向前找，直到找到某个位置，<= key,
    // 然后按照定义，返回这个位置的后一个位置 因为我们访问的是i-1,所以刚好返回i
    // 综上所述，这个实现完全正确！
    // 卧槽，我简直要高潮了，太对了
    // lower 和 upper 是如此的对称！而且刚好返回的就是 equal range 的
    // 左闭右开的区间 这个左闭右开到底是谁研究的，是人我吃
}

// 同理可以实现UpperBound
// 我理解错了
// https://en.cppreference.com/w/cpp/algorithm/equal_range
// https://en.cppreference.com/w/cpp/algorithm/lower_bound
// https://en.cppreference.com/w/cpp/algorithm/upper_bound
// 可以看到equal_range的实现就是简单的 return make_pair(lower_bound,
// upper_bound) 而这个区间刚好是左开右闭的
//
// 所以lower_bound返回的是所有 >= key的元素中，最小的那个的索引
// 但是 upper_bound返回的是所有 <= key的元素中，最大的那个的索引+1
// 原来如此，所以下面的实现，刚好不需要考虑额外的情况，原来需要特殊处理的情况，反而不用特殊处理了！
// 这TM的太神奇了
int UpperBound(int* array, int begin, int end, int key) {

    while (begin < end) {
        int middle = begin + ((end - begin) / 2);

        // 可以对称的实现才对
        // 其实主要就是考虑相等的情况

        // if (array[middle] == key) {
        //     // 则upper bound 会在 [middle, e]
        //     // 这是与lower bound不同的地方
        //     // 这个范围是对的，就是不知道 这样返回会不会导致死循环呢?
        //     // 如果只剩一个元素，[middle, e]会变成死循环
        //     // 但是只剩一个元素，begin就是答案啊
        //     if (end - begin == 1) {
        //         break;
        //     }

        //     begin = middle;
        // }
        if (array[middle] <= key) {
            // 则upper bound 一定在 [middle+1, e]
            begin = middle + 1;
        } else {
            // 则 upper bound 会在 [begin, middle]
            end = middle;
        }
        // if (array[middle] > key) {
        // }
    }

    return begin;
}

struct Range {
    int begin;
    int end;
};

// https://en.cppreference.com/w/cpp/algorithm/equal_range
Range EqualRange(int* array, int begin, int end, int key) {
    return Range{
        LowerBound(array, begin, end, key),
        UpperBound(array, begin, end, key),
    };
}

int main() {

    // 现在让我们随机生成一些序列，然后排好序
    // 然后随机的寻找一些数字的上界和下界吧
    // 然后和标准库的实现做比较 看看我们的实现对不对

    // https://en.cppreference.com/w/cpp/algorithm/binary_search

    std::default_random_engine e(
        std::chrono::system_clock::now().time_since_epoch().count());

    // [0, 1023] both inclusive
    int min = 0;
    int max = 0;
    std::uniform_int_distribution<int> u(min, max);

    const int size = 1024;
    std::array<int, size> array;
    for (int i = 0; i < size; i++) {
        array[i] = u(e);
    }

    // 然后对数组进行排序
    std::sort(array.begin(), array.end());

    for (int i = min - 1; i <= max + 1; i++) {
        bool found1 = std::binary_search(array.begin(), array.end(), i);
        bool found2 = BinarySearch(array.data(), 0, size, i);
        assert(found1 == found2);

        auto lower_it = std::lower_bound(array.begin(), array.end(), i);
        int lower_index1 = lower_it - array.data();
        int lower_index2 = LowerBound(array.data(), 0, size, i);
        assert(lower_index1 == lower_index2);

        auto upper_it = std::upper_bound(array.begin(), array.end(), i);
        int upper_index_1 = upper_it - array.data();
        int upper_index_2 = UpperBound(array.data(), 0, size, i);
        assert(upper_index_1 == upper_index_2);

        int lower_index_3 = LowerBoundSimple(array.data(), 0, size, i);
        assert(lower_index1 == lower_index_3);

        int upper_index_3 = UpperBoundSimple(array.data(), 0, size, i);
        assert(upper_index_1 == upper_index_3);
    }
}