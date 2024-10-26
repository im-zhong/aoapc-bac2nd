// 2024/10/25
// zhangzhong

#include <cstring>
#include <iostream>

bool IsHardString(char* A, int len) {

    // special case
    // len = 1, 1 / 2 = 0, 1 < 0 false, 直接return true, ok!
    // 从最后两个字符开始比较
    // len = 2
    // slen = 1, 1 <= 1
    // len = 3
    // len = 4
    // slen = 1, 1 <= 2, slen = 2, 2 <= 2
    // len = 5, 1 <= 2, 2 <= 2
    // ok!
    for (int substr_len = 1; substr_len <= len / 2; substr_len++) {
        char* str_tail = A + len; // ptr -> \0
        char* str1 = str_tail - substr_len;

        char* str2 = str1 - substr_len;

        if (std::strncmp(str1, str2, substr_len) == 0) {
            // 如果有重复字串
            return false;
        }
    }

    return true;
}

void KryptonFactor(char* A, int& nth, int char_count, int cur) {

    // 还有当我们结束之后，要放置之后的递归调用，这里设置一个快速的结束条件
    if (nth <= 0) {
        return;
    }

    // 只要cur中存在字符，我们就需要输出当前的串
    // 知道我们输出了nth个串为止
    if (cur > 0) {

        nth -= 1;

        if (nth <= 0) {
            // time to finish

            // 根据输出格式输出即可
            for (int i = 0; i < cur; i++) {
                // TODO, 测试换行
                if (i != 0 && i != 16 * 4 && i % 4 == 0) {
                    std::cout << " ";
                } else if (i == 16 * 4) {
                    std::cout << "\n";
                }
                std::cout << A[i];
            }
            std::cout << "\n";
            // 输出序列长度
            std::cout << cur << "\n";
            return;
        }

        // 这里没有return，因为这不是递归结束条件, 上面的才是
    }

    // 遍历所有的char
    for (int c = 0; c < char_count; c++) {

        char ch = 'A' + c;

        // 什么情况下这个A可以放到A中呢
        // 如果cur是零，那么就是可以用的
        if (cur == 0) {
            A[cur] = ch;
            KryptonFactor(A, nth, char_count, cur + 1);
        } else {
            // 如果不是，那么我们就需要判断我们把ch放到A之后，构成的新串是不是困难串
            A[cur] = ch;
            if (IsHardString(A, cur + 1)) {
                KryptonFactor(A, nth, char_count, cur + 1);
            }
        }
    }
}

int main() {

    char A[128] = {};

    int nth = 0;
    int char_count = 0;
    while (std::cin >> nth >> char_count) {
        if (nth == 0 && char_count == 0) {
            break;
        }

        KryptonFactor(A, nth, char_count, 0);
    }
}