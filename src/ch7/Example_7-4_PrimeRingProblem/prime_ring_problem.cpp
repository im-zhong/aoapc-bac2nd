// 2024/10/25
// zhangzhong

#include <iostream>

// 竟然没有超时，其实这个IsPrime会被重复调用非常多次
// 更好的方法是预先计算出所有1-16是不是素数，然后查表就行
// 应该会更快一些
bool IsPrime(int n) {

    if (n == 1) {
        return false;
    }

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

void PrimeRing(int n, int* A, int cur) {

    // 当整个整数环被充满时，判断首尾两个数字是否是质数
    if (cur == n) {

        // n是偶数，所以不用考虑只有一个元素的情况
        if (IsPrime(A[0] + A[n - 1])) {
            // 找到一组符合条件的
            // 输出
            for (int i = 0; i < n; i++) {
                if (i != 0) {
                    std::cout << " ";
                }
                std::cout << A[i];
            }
            std::cout << "\n";
        }

        // 递归结束
        return;
    }

    // TODO: 数字是从1开始的，改一下这里的循环条件
    // 不对，我们的排列的首个元素一定是1！，我们不需要在这里搞一个循环
    // 在最开始的时候不需要循环，直接把首元素赋值为1
    if (cur == 0) {
        A[cur] = 1;
        PrimeRing(n, A, cur + 1);
    } else {

        // 这里也是可以改进的，其实不需要每次都遍历所有的数字
        // 可以预算计算出可以组成素数的组合，变成一个二维数组，然后遍历二维数组中的一行即可
        for (int i = 1; i <= n; i++) {
            bool ok = true;
            for (int j = 0; j < cur; j++) {
                if (A[j] == i) {
                    ok = false;
                }
            }
            if (!ok) {
                continue;
            }

            // 检查要插入的数字和cur-1组成的数字的和是不是素数，如果是素数就继续
            // 否则就直接下一个
            // if (cur == 0) {
            //     // 如果是第一个数字，那么久继续
            //     // 卧槽，又忘了给A赋值了
            //     A[cur] = i;
            //     PrimeRing(n, A, cur + 1);
            // } else {
            if (IsPrime(A[cur - 1] + i)) {
                A[cur] = i;
                PrimeRing(n, A, cur + 1);
            }
            //}
        }
    }
}

int main() {
    int number = 0;
    int A[16] = {};
    int test_case_id = 1;
    while (std::cin >> number) {

        if (test_case_id != 1) {
            std::cout << "\n";
        }
        std::cout << "Case " << test_case_id << ":\n";
        PrimeRing(number, A, 0);

        test_case_id += 1;
    }
}