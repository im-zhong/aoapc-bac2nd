// 2024/7/21
// zhangzhong

// 还有一个方法，就是查表
// 这是一个典型的正算简单，到算难的问题
// 可以事先建立所有n=1 -> n =100000的生成元
// 然后来了一个数直接查表就行
// 这张表必须是编译期计算的，不然每次执行程序都算一遍也很慢

#include <cstdio>
#include <cstring>
using namespace std;

const int max_count = 100000 + 1;
int table[max_count] = {};

int main(int argc, char* argv[]) {

    // first calculate the whole table
    for (int i = 0; i < max_count; i++) {
        int sum = i;
        int m = i;
        while (m) {
            sum += (m % 10);
            m /= 10;
        }

        if (sum >= max_count) {
            break;
        }
        // 这里还有一个坑，后面生成的生成数有可能覆盖之前生成的
        // 同时我们需要的是最小的
        // 所以要先判断是否为零
        if (table[sum] == 0) {
            table[sum] = i;
        }
    }

    int count = 0;
    scanf("%d", &count);

    int n = 0;
    for (int i = 0; i < count; i++) {
        scanf("%d", &n);
        printf("%d\n", table[n]);
    }
}
