// 2024/7/18
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cmath>
#include <cstdio>
#include <cstring>
#include <doctest/doctest.h>

const int max_count = 1000;
// int arr[max_count] = {};

// TEST_CASE("program 3-3") {

//     int n = 0;
//     std::scanf("%d", &n);

//     // int[n][n]
//     // int[i][j] = i*n + j
//     // 这样就不需要动态申请一个二维数组了
//     int min = 0;
//     int max = n - 1;
//     int num = 1;
//     int i = 0;
//     int j = 0;
//     while (num <= n * n) {

//         if (min > max) {
//             break;
//         }
//         if (min == max) {
//             arr[min * n + max] = num;
//             break;
//         }

//         // start from [min, max] -> [max - 1, max]
//         j = max;
//         for (i = min; i < max; i++) {
//             arr[i * n + j] = num;
//             num += 1;
//         }
//         // start from [max, max] -> [max, min + 1]
//         i = max;
//         for (j = max; j > min; j--) {
//             arr[i * n + j] = num;
//             num += 1;
//         }
//         // start from [max, min] -> [min + 1, min]
//         j = min;
//         for (i = max; i > min; i--) {
//             arr[i * n + j] = num;
//             num += 1;
//         }
//         // start from [min, min] -> [min, max - 1]
//         i = min;
//         for (j = min; j < max; j++) {
//             arr[i * n + j] = num;
//             num += 1;
//         }

//         min += 1;
//         max -= 1;
//     }

//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             std::printf("%d ", arr[i * n + j]);
//         }
//         std::printf("\n");
//     }
// }

int arr2[20][20] = {};
TEST_CASE("program 3-3 book solution") {
    int n = 0;
    std::scanf("%d", &n);
    int num = 1;

    int i = 0;
    int j = n - 1;

    // 这里必须也得有一个初始化
    // 三折结合起来，这个逻辑才是对的
    arr2[i][j] = num;

    while (num < n * n) {
        // while (i < n && arr2[i][j] == 0) {
        //     arr2[i][j] = num;
        //     num += 1;
        //     i += 1;
        // }
        // // 在这里 i已经越界 所以要-1变回来
        // i -= 1;
        // 但是这样写很麻烦
        // 所以在条件里就需要对下一个位置进行判断
        // 但是while超前判断可能会导致落下最后一个位置
        // 所以在循环体内部也需要进行+1操作
        // 两者配合起来才能正常工作
        // 讲道理，这个版本的代码真的不好理解

        while (i + 1 < n && arr2[i + 1][j] == 0) {
            arr2[++i][j] = ++num;
        }
        while (j - 1 >= 0 && arr2[i][j - 1] == 0) {
            arr2[i][--j] = ++num;
        }
        while (i - 1 >= 0 && arr2[i - 1][j] == 0) {
            arr2[--i][j] = ++num;
        }
        while (j + 1 < n && arr2[i][j + 1] == 0) {
            arr2[i][++j] = ++num;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::printf("%d ", arr2[i][j]);
        }
        std::printf("\n");
    }
}