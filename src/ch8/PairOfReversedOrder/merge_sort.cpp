// 2024/10/31
// zhangzhong

// 先写一个merge sort吧 热热身

#include <cassert>
#include <chrono>
#include <cstddef>
#include <random>

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
            temp[t] = array[right];
            right += 1;
        }

        // 不论如何 temp的下标都要+1
        // 因为不论谁小 都会向temp中复制
        t += 1;
    }

    // 有可能left 或者 right还有剩余
    while (left < middle) {
        temp[t] = array[left];
        left += 1;
        t += 1;
    }
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
void MergeSort(int* array, size_t size) {
    int temp[size];

    ImplMergeSort(array, 0, size, temp);
}

bool CheckOrder(int* array, size_t size) {
    for (int i = 0; i < size - 1; i++) {
        if (array[i] > array[i + 1]) {
            return false;
        }
    }
    return true;
}

int main() {

    // 随机产生一些数字，然后排序
    // 然后验证顺序即可

    std::default_random_engine e(
        std::chrono::system_clock::now().time_since_epoch().count());

    // [0, 1023] both inclusive
    std::uniform_int_distribution<int> u(0, 1023);

    const int size = 1024;
    int array[size];
    for (int i = 0; i < size; i++) {
        array[i] = u(e);
    }

    MergeSort(array, size);

    assert(CheckOrder(array, size));
}