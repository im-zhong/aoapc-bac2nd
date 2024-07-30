// 2024/7/30
// zhangzhong

#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

char top[512] = "";
char bottom[512] = "";

int stripe[256] = {};

int find_min_stripe(char* top, char* bottom) {
    int min_stripe_len = 99999999;

    int top_len = strlen(top);

    for (int i = 0; i <= top_len; i++) {
        char* p = top;
        char* q = bottom - i;
        int* ps = stripe;

        while (*p || *q) {
            *ps++ = *p + *q;
            p++;
            q++;
        }

        bool is_ok = true;
        int stripe_len = ps - stripe;
        for (int i = 0; i < stripe_len; i++) {
            if (stripe[i] > 3) {
                // not a legal stripe, just return a very large number
                // try another stripe
                is_ok = false;
                break;
            }
        }

        if (is_ok && stripe_len < min_stripe_len) {
            min_stripe_len = stripe_len;
        }
    }

    return min_stripe_len;
}

int main() {
    while (scanf("%s%s", top + 128, bottom + 128) == 2) {

        // 接下来就是找一个停止的方法

        // memset(stripe, 0, sizeof(stripe));

        for (char* p = top + 128; *p; p++) {
            if (*p == '1') {
                *p = 1;
            } else if (*p == '2') {
                *p = 2;
            }
        }
        for (char* p = bottom + 128; *p; p++) {
            if (*p == '1') {
                *p = 1;
            } else if (*p == '2') {
                *p = 2;
            }
        }

        // 我们要让top从最左边一直滑动到最右边
        // 最简单的方式

        // 其实就是分成两段
        // 而且这两段是对称的
        // 实际上我们只需要写成一个函数
        // 然后调转指针，调用两次该函数即可

        int min_stripe_len = min(find_min_stripe(top + 128, bottom + 128),
                                 find_min_stripe(bottom + 128, top + 128));
        printf("%d\n", min_stripe_len);

        memset(top, 0, sizeof(top));
        memset(bottom, 0, sizeof(bottom));
    }
}