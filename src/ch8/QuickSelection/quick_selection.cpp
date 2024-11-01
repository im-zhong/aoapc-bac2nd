// 2024/10/31
// zhangzhong

// 我们有三本算法书，我看看看这三个算法书上的快排实现都有什么区别吧

// 快排适合使用[begin:end]这样的范围进行编写吗？
// 最起卖在左右分割的时候是不合适的
// 因为left和right显然都需要指向数字
// 而不是左侧指向 右侧right-1才指向
// 但是如果只是点名范围呢？合适吗
// 感觉是比较合适的
// 咱们尝试一下

#include <cassert>
#include <chrono>
#include <cstddef>
#include <iostream>
#include <random>

// 标准库的实现大概我们快一倍
const int cutoff = 16;

// 咱们给这个加一个范围 更好的检查顺序
bool CheckOrder(int* array, int begin, int end) {
    for (int i = begin; i < end - 1; i++) {
        if (array[i] > array[i + 1]) {
            return false;
        }
    }
    return true;
}

// 这两个插入排序都是对的，但是V2显然更容易理解，更不容易写错！ nice！
inline void InsertionSortV2(int* array, int begin, int end) {
    // 如果只有0 or 1个元素 直接不排序
    // if (end - begin < 2) {
    //     return;
    // }
    // 这个判断是不需要的，因为下面的循环可以做出同样的判断

    for (int i = begin + 1; i < end; i++) {
        // 我们就从i开始向左交换即可
        // 然后在不需要交换时 跳出即可
        for (int j = i; j > 0; j--) {
            if (array[j - 1] <= array[j]) {
                // 这就是正确的顺序 应该直接退出
                break;
            }
            // 否则我们就交换他们
            std::swap(array[j - 1], array[j]);
        }
    }

    // if (!CheckOrder(array, begin, end)) {
    //     for (int i = begin; i < end; i++) {
    //         std::cout << array[i] << ", ";
    //     }
    //     std::cout << std::endl;
    // }
    // assert(CheckOrder(array, begin, end));
}

void InsertionSort(int* array, int begin, int end) {

    // 如果只有0 or 1个元素 直接不排序
    if (end - begin < 2) {
        return;
    }

    // 插入排序就是不断向后看，每次把最新的一个数字插入到前面已经排好序的数组中
    // 在最开始，我们假设只包含一个元素的数组是排好序的
    // [[BUG]]
    // 这里有bug呀！
    // i 应该从begin + 1 开始的呀！
    for (int i = begin + 1; i < end; i++) {
        // 现在将i=1的元素插入到[0:i]的序列中

        int j = begin;
        for (; j < i; j++) {
            // 首先找到开始插入的位置
            // 也就是 array[i] > array[j]
            // 当 array[i] == array[j]时我们跳过，可以少复制一点元素
            // 也就是尽量让j大一点
            // 因为j:i的元素都要向后复制一位

            // 不对啊，是不是写反了
            // 碰到的第一个我们比他小的数字就停下
            // 相等的话不停下，上面讨论了
            // ==
            // 碰到 > 才应该跳过
            if (array[i] < array[j]) {

                // 在这里进行复制就行
                // 算了，还是跳出去写吧，这样嵌套程度更小

                break;
            }
        }

        // 算了 还是不要写这么危险的句子
        // 代码越简单越
        // for (; j < i && array[i] < array[j]; j++)
        //     ;

        // 那么在这里就有一种特殊情况
        // 就是我们比所有的数字都大，也就是此时j == i
        // 我们不应该做任何数据的移动
        // 而下面的循环刚好处理了这种情况，nice！

        // 现在array[j] > array[i]
        // 也就是说 当前元素array[i] 应该放到j的位置
        // 而从[j:i] -> [j+1:i+1]
        // 咱们显然array[i] 给复制出来 别复制的时候给覆盖了
        int temp = array[i];
        // 而且我们复制的时候也要倒着复制
        for (int k = i; k > j; k--) {
            array[k] = array[k - 1];
        }
        // 然后将temp复制到j对应的位置
        array[j] = temp;
    }

    if (!CheckOrder(array, begin, end)) {
        for (int i = begin; i < end; i++) {
            std::cout << array[i] << ", ";
        }
        std::cout << std::endl;
    }
    assert(CheckOrder(array, begin, end));
}

inline int Median3(int* array, int begin, int end) {

    int middle = begin + ((end - begin) / 2);

    // 因为end指向最后一个元素的后一个位置
    // 所以想要取得最后一个元素 需要 end -1
    int last = end - 1;

    if (array[begin] > array[middle]) {
        std::swap(array[begin], array[middle]);
    }
    if (array[begin] > array[last]) {
        std::swap(array[begin], array[last]);
    }
    if (array[middle] > array[last]) {
        std::swap(array[middle], array[last]);
    }

    // 然后把pivot交换到数组的倒数第二个位置
    // 为什么是-2呢？因为end-1是数组的最后一个位置，已经保存了一个>=pivot的数字，用作guard防止i越界
    // 所以是end-2
    // 这一句确实写在Median3这个函数里面更好 因为我们的函数就是获得一个pivot
    // 这里的swap明显是属于上面的逻辑范畴
    std::swap(array[middle], array[last - 1]);

    // 倒数第二个位置是pivot
    return last - 1;
}

void QuickSort(int* array, const int begin, const int end, const int k) {

    // 先输出一下排序之前的状态
    // std::cout << "before sort\n";
    // for (int i = begin; i < end; i++) {
    //     std::cout << array[i] << ", ";
    // }
    // std::cout << std::endl;

    // 如果数组较短，则直接进行插入排序
    if (end - begin <= cutoff) {
        InsertionSort(array, begin, end);
        return;
    }

    // 首先三数取中
    // [[BUG]]
    // 这里写错了
    // 这里返回的数
    // 但是我们下面当坐标使了...
    int pivot_index = Median3(array, begin, end);
    int pivot = array[pivot_index];

    // left从begin+1开始
    int left = begin;
    // right从pivot-1处开始
    int right = pivot_index;
    // 为什么这么说呢？下面的循环会告诉你
    for (;;) {
        // 当array[left] >= pivot时会停下
        // form 1
        // while (array[++left] < pivot)
        //     ;
        while (array[++left] < pivot) {
        }
        // form 2
        // do {
        //     left += 1;
        // } while (array[left] < pivot);
        // the same form 3
        // 这种形式显然不容易理解，
        // 感觉do while是最容易理解的，就是无论如何我们都至少执行一次 left
        // 一定会向前移动一次
        // left += 1; while (array[left] < pivot) {
        //     left += 1;
        // }
        // 当array[right] <= pivot时会停下
        // 傻逼吗，应该是--啊
        while (array[--right] > pivot)
            ;

        // 如果此时 left < right 交换他们
        // 否则 left >= right 直接退出
        if (left < right) {
            std::swap(array[left], array[right]);
        } else {
            break;
        }
    }

    // partition 之后, left指向的位置就是pivot应该呆的位置
    // 为什么不是right呢？应该都行吧

    // 不对啊！因为我们要和pivot进行交换啊
    // pivot在右边，所以必须是一个>=pivot的数啊，如果交换right的话，那不是就破坏了partition的要求吗！！！
    std::swap(array[left], array[pivot_index]);

    // 然后我们知道 在 begin:left 都是 <= pivot的数字
    // 在 left:end 都是 >= pivot的数字
    // 递归！
    // 是不是从pivot处向左寻找直到一个 < pivot的数字
    // 向右寻找直到一个 > pivot的数字
    // 会让整个算法更好？
    // also corrent!
    // does it more quick?
    // 这个优化真的有用！ 75000us -> 60000us 我好厉害啊
    // int new_left = left;
    // while (array[--new_left] >= pivot)
    //     ;
    // QuickSort(array, begin, new_left + 1);
    // int new_right = left;
    // while (array[++new_right] <= pivot)
    //     ;
    // QuickSort(array, new_right, end);

    // correct implementation
    // quick selection 的实现想较于 quick sort的实现的唯一区别就在这里
    // 首先我们检查 pivot的位置 和 我们想要返回的 kth element 是否就是同一个
    // 这个就是递归结束条件了
    // 因此 我们需要给函数添加一个参数 k
    // 而且我们假设k是从0开始的，这样就不用+1 -1的了
    // 最终pivot所在的位置是
    pivot_index = left;
    if (k == pivot_index) {
        // 我们已经找到了，什么都不用干了
        // 那么这个分支实际上是没什么用的
        // 但是写出来，代码的意图更加明显，可读性应该会更好
        return;
    }
    // 否则 我们根据k和pivot的相对位置，走不同的递归分支
    // 正是因为这个特性，快速选择算法的时间复杂度不是O(nlogn),而是O(n)
    else if (k < pivot_index) {
        // 还有值得注意的是，我们的实现中，全部使用的都是绝对索引
        // 所以 k不用随着范围变化，代码更简单，更容易理解，更不容易出错
        QuickSort(array, begin, left, k);
    } else {
        QuickSort(array, left + 1, end, k);
    }

    // 在递归结束之后，序列应该是排好序的
    // if (!CheckOrder(array, begin, end)) {
    //     for (int i = begin; i < end; i++) {
    //         std::cout << array[i] << ", ";
    //     }
    //     std::cout << std::endl;
    // }
    // assert(CheckOrder(array, begin, end));
}

int main() {

    std::default_random_engine e(
        std::chrono::system_clock::now().time_since_epoch().count());

    // [0, 1023] both inclusive
    std::uniform_int_distribution<int> u(0, 1000);

    const int size = 1024000;
    int array[size];
    std::array<int, size> array2;
    for (int i = 0; i < size; i++) {
        array[i] = u(e);
        array2[i] = array[i];
        // std::cout << array[i] << ",";
    }
    // std::cout << std::endl;

    // QuickSort(array, 0, size);
    // assert(CheckOrder(array, 0, size));

    // check the time of our implementation and std::sort

    // 不对啊！
    // 这个排序没有问题！
    // int array[8] = {
    //     2, 5, 4, 1, 4, 3, 6, 8,
    // };
    // InsertionSort(array, 0, 8);

    // 只排序一个可能太快了
    // 咱们可以多排序几个 或者让队列长一些
    auto start = std::chrono::system_clock::now();
    std::sort(array2.begin(), array2.end());
    auto stop = std::chrono::system_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(
                     (stop - start))
                     .count()
              << std::endl;

    int k = 10000;
    start = std::chrono::system_clock::now();
    QuickSort(array, 0, size, k);
    stop = std::chrono::system_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(
                     (stop - start))
                     .count()
              << std::endl;

    // 然后两者对应的数字需要一样
    assert(array[k] == array2[k]);
}
