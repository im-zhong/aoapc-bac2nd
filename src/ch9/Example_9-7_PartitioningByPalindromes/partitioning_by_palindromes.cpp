// 2024/11/29
// zhangzhong

// A partition of a sequence of
// characters is a list of one or
// more disjoint non-empty groups
// of consecutive characters whose
// concatenation yields the initial
// sequence.

#include <iostream>
#include <string>
#include <vector>

constexpr int max_length = 1024;

void PrintPalindrome(bool is_palindrome[max_length][max_length], int length) {
    for (int left = 0; left < length; left++) {
        for (int right = 0; right < length; right++) {

            std::cout << is_palindrome[left][right] << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void PrintDP(int dp[max_length], int length) {
    for (int i = 0; i <= length; i++) {
        std::cout << dp[i] << " ";
    }
    std::cout << std::endl;
}

int GetMinimumPartitionGroup(const std::string& text) {
    int length = text.size();
    // at the first step, we preprocessing the text
    // get any range from [i..=j], if it is a palindrome
    bool is_palindrome[max_length][max_length] = {};
    // use left..=right to stand for a interval left closed right closed

    // for (int left = 0; left < length; left++) {
    //     for (int right = 0; right < length; right++) {
    //         is_palindrome[left][right] = false;
    //     }
    // }
    for (int middle = 0; middle < length; middle++) {

        // 回文串有两种模式
        // aaa
        int left = middle;
        int right = middle;
        while (left >= 0 && right < length && text[left] == text[right]) {
            is_palindrome[left][right] = true;
            left--;
            right++;
        }

        // aabb
        left = middle;
        right = middle + 1;
        while (left >= 0 && right < length && text[left] == text[right]) {
            is_palindrome[left][right] = true;
            left--;
            right++;
        }
    }

    // 第二部 开始dp
    // 设 dp[i] 表示 0..=i的最少的回文串个数
    // 和那个灯的题目是一样的 0..=j, j+1..=i
    // 所以我们需要j=0
    // 所以我们需要text的下标从1开始
    // 不过倒是还有一个办法
    // 那就是用dp[i]表示 0..i 不包括i的最少的回文串个数
    // 这样就不用修改text了
    // 初始状态 dp[0] = 0
    // 计算顺序 0 ->
    // solution: dp[length]
    constexpr int inf = 1 << 30;
    int dp[max_length];
    for (int i = 0; i <= length; i++) {
        dp[i] = inf;
    }
    dp[0] = 0;

    for (int i = 1; i <= length; i++) {
        int right = i - 1;
        for (int j = 0; j < i; j++) {
            int left = j;
            if (is_palindrome[left][right]) {
                dp[i] = std::min(dp[i], dp[j] + 1);
            }
        }
    }

    return dp[length];
}

int main() {
    int case_count = 0;
    std::scanf("%d\n", &case_count);

    for (int c = 0; c < case_count; c++) {

        std::string line;
        std::getline(std::cin, line);

        int minimum_group = GetMinimumPartitionGroup(line);
        std::cout << minimum_group << "\n";
    }
}
