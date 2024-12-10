// 2024/12/10
// zhangzhong

#include <iostream>

// 本题目实际上非常简单
// 就是求n以内的互质的数一共有多少对
// 其实就是欧拉函数的和
// 我们在nlogn的时间内求出欧拉函数
// 然后n的时间内求一下和即可
// 我们只需要在最开始求一边欧拉函数即可
// 然后再开一个数组求一次和
// 之后的test case 都是 o1 直接查表！
// 你还别说，和这个题目主人公的做法还挺像的

constexpr int maxn = 50000;
int phi[maxn + 1];
int sum[maxn + 1];

void Euler() {
    phi[1] = 1;

    for (int p = 2; p <= maxn; p++) {
        // 为什么不在一开始就把phi[i] = i
        // 因为在这里我们需要靠phi[i] == 0 来区分素数！素数筛
        if (phi[p] == 0) {
            // p is prime, 素数筛
            // 只不过这里不像真的素数筛那样，会跳过一些数字，所有phi[n]
            // 都要除以相应的素数的因式
            for (int kp = p; kp <= maxn; kp += p) {
                // 有可能kp对应的phi[n]还没有被初始化
                if (phi[kp] == 0) {
                    phi[kp] = kp;
                }

                // phi[n] =  n (1 - 1/p) ...
                // 先除再乘 防止溢出
                phi[kp] = phi[kp] / p * (p - 1);
            }
        }
    }
}

void Init() {
    Euler();

    // 计算和
    // 这里统计的只是x <= y 的互质数对
    // 如果把1去掉 sum[n] - sum[1]
    // 还有对称的情况 (sum[n] - sum[1])*2
    // 然后再考虑 x == y == 1的情况 再加上1
    for (int i = 1; i <= maxn; i++) {
        sum[i] = sum[i - 1] + phi[i];
    }
}

uint64_t Solve(int n) {

    return 1 + 2 * (sum[n] - sum[1]);

    return 0;
}

int main() {

    Init();

    int n = 0;
    while (std::cin >> n) {
        if (n == 0) {
            break;
        }

        uint64_t answer = Solve(n);
        std::cout << answer << "\n";
    }
}