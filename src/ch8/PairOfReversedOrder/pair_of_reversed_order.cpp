// 2024/10/31
// zhangzhong

#include <cassert>
#include <chrono>
#include <cstddef>
#include <iostream>
#include <random>

int total_count = 0;

void ImplMergeSort(int* array, int begin, int end, int* temp) {

    if (end - begin == 1) {
        return;
    }

    int middle = begin + ((end - begin) / 2);

    // left span
    ImplMergeSort(array, begin, middle, temp);
    // right span
    ImplMergeSort(array, middle, end, temp);

    // 然后就是一个合并啦
    // 咱们采取代码行数较多 但是比较容易理解的方式

    // 将array中两个排好序的区间，合并到temp数组上
    // 注意两个数组都使用 [begin:end] 这个范围
    int left = begin;
    int right = middle;
    // 使用两个变量分别指向左和右两个区间
    // 使用t指向temp数组
    int t = begin;
    while (left < middle && right < end) {
        // 将两个数组中的较小者 放到temp
        // 是否可以stable呢？
        // 应该是可以的
        // 只要保证数据相同时
        // 左边的元素先复制到temp中即可
        if (array[left] <= array[right]) {
            temp[t] = array[left];
            left += 1;
        } else {
            // 什么时候应该统计呢
            // 每当右侧向temp中复制时
            // 说明左侧剩下的所有数和本数都是逆序的
            // ！ 而且上面我们还处理了两个数据相等的情况，damn right！
            total_count += middle - left;
            temp[t] = array[right];
            right += 1;
        }

        // 不论如何 temp的下标都要+1
        // 因为不论谁小 都会向temp中复制
        t += 1;
    }

    // 有可能left 或者 right还有剩余
    // 下面这两个循环实际上只会执行一个
    while (left < middle) {
        // 如果左侧有剩下的
        // 说明剩下的数字都比右侧最大的数字大
        // 一定不会相等，如果相等会复制到temp里面
        // 会比第二大的大吗 这是有可能的
        // 考虑一种极端的情况
        // left: 4 4 4
        // right: 1 2 3
        // 但是这个时候 其实 三个4的逆序对都统计完了
        // 其实 左边进入temp的时候时不需要统计的
        temp[t] = array[left];
        left += 1;
        t += 1;
    }
    // 如果右侧有剩下的 一定都是正序
    // 而在这里进入temp的时候 左边一定都已经没有了
    // 所以实际上我们已经写完了!
    while (right < end) {
        temp[t] = array[right];
        right += 1;
        t += 1;
    }

    // 现在temp[begin:end]就是已经排好顺序的
    // 我们把它复制到array中相同的位置即可
    for (int i = begin; i < end; i++) {
        array[i] = temp[i];
    }
}

// size must > 0
int GetReversedOrderCount(int* array, size_t size) {
    int temp[size];
    total_count = 0;

    ImplMergeSort(array, 0, size, temp);
    return total_count;
}

// 当然还有一个慢一点的实现方法
int GetReversedOrderCountSlowly(int* array, size_t size) {

    int count = 0;
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {

            // i < j
            if (array[i] > array[j]) {
                count += 1;
            }
        }
    }
    return count;
}

int main() {
    std::default_random_engine e(
        std::chrono::system_clock::now().time_since_epoch().count());

    // [0, 1023] both inclusive
    std::uniform_int_distribution<int> u(0, 10);

    const int size = 4;
    int array[size];
    for (int i = 0; i < size; i++) {
        array[i] = u(e);
        std::cout << array[i] << ",";
    }
    std::cout << std::endl;

    // assert(GetReversedOrderCount(array, size) ==
    //        GetReversedOrderCountSlowly(array, size));

    // 卧槽， 傻逼了，array已经被排过序了。。。
    std::cout << GetReversedOrderCountSlowly(array, size) << std::endl;
    std::cout << GetReversedOrderCount(array, size) << std::endl;
}