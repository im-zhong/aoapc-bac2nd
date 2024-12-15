// 2024/12/15
// zhangzhong

#include <iostream>

constexpr int maxn = 20;

double p[maxn];

// 这个只是计数的 最后还要除以 total count
double ans[maxn];

//
double total_p = 0;

// 枚举函数
void Enum(int n, int r, int k, int* arrange) {
    // 递归结束
    // r可以是零 需要特殊考虑
    // 我们让k表示人数吧，先不考虑剪枝
    if (k == n) {
        // 统计所有1的个数
        int ones_count = 0;
        for (int i = 0; i < n; i++) {
            ones_count += arrange[i];
        }

        if (ones_count == r) {

            // 计算当前排列的概率
            double cp = 1;

            // 不对啊，我这样没有考虑概率啊
            for (int i = 0; i < n; i++) {
                if (arrange[i] == 1) {
                    cp *= p[i];
                } else {
                    cp *= (1 - p[i]);
                }
            }

            total_p += cp;

            // 而且所有买了东西的都要加上cp
            for (int i = 0; i < n; i++) {
                if (arrange[i] == 1) {
                    ans[i] += cp;
                }
            }
        }

        return;
    }

    // 0...k已经枚举过了
    // 那么我们需要从
    // 剪纸也简单，加一个参数，表示当前1的数量，如果1太多了，我们就不走另外一个分支了，完美！
    arrange[k] = 0;
    Enum(n, r, k + 1, arrange);
    arrange[k] = 1;
    Enum(n, r, k + 1, arrange);
}

void Solve(int n, int r) {

    // 初始化
    total_p = 0;

    // 首先所有ans全部清零
    for (int i = 0; i < n; i++) {
        ans[i] = 0;
    }

    if (r == 0) {
        // TODO: 特殊情况
        // 防止除零
        total_p = 1;
        return;
    }

    // 使用一个数组来保存某个人是否购买
    int arrange[maxn] = {};

    Enum(n, r, 0, arrange);
}

int main() {
    int n = 0;
    int r = 0;

    int t = 1;
    while (std::cin >> n >> r) {
        if (n == 0 && r == 0) {
            break;
        }

        for (int i = 0; i < n; i++) {
            std::cin >> p[i];
        }

        std::cout << "Case " << t << ":\n";
        t++;

        Solve(n, r);
        for (int i = 0; i < n; i++) {
            std::printf("%.6f\n", ans[i] / (double)total_p);
        }
    }
}