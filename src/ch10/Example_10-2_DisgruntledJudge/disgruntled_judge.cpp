// 2024/12/4
// zhangzhong

#include <iostream>

constexpr int maxt = 100;

int main() {

    int T = 0;
    std::cin >> T;

    int x[2 * maxt];

    for (int i = 0; i < 2 * T; i += 2) {
        std::cin >> x[i];
    }

    // 枚举所有的a和b
    for (int a = 0; a <= 10000; a++) {
        bool ok = true;
        for (int b = 0; b <= 10000; b++) {

            ok = true;
            // 然后开始根据公式挨个计算
            // x = (a * xi-1 + b) mod 10001
            for (int i = 1; i < 2 * T; i += 2) {
                int xi = (a * x[i - 1] + b) % 10001;
                x[i] = xi;

                // 我们需要看一下我们推算出来的和序列中的下一个是否是一致的
                if (i + 1 < 2 * T) {
                    if (x[i + 1] != (a * xi + b) % 10001) {
                        ok = false;
                        break;
                    }
                }
                // if (i + 1 < 2 * T && x[i + 1] == (a * xi + b) % 10001) {
                //     continue;
                // }

                // 出错了 break
                // ok = false;
                // break;
            }

            if (ok) {
                // we found the answer
                // and the answer is in the xs
                // 卧槽 这里不应该break 应该直接return
                //
                break;
            }
        }
        if (ok) {
            break;
        }
    }

    for (int i = 1; i < 2 * T; i += 2) {
        std::cout << x[i] << "\n";
    }
}