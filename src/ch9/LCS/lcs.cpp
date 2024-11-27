// 2024/11/27
// zhangzhong

#include <string>

int LCS(const std::string& text1, const std::string& text2) {

    // 这是一道二维的dp题目
    // 使用l[i, j]表示text1以i结尾，text2以j结尾的情况下的最长公共子序列
    // 则初始状态
    // l[i, 0] = l[j, 0] = 0 or 1 {if text1[0] = text2[j] or vice-verse}
    // 也就是在只考虑text1的首元素，看他与text2的最长公共子序列
    // O(n) + O(m)
    // 计算顺序：二维dp数组从左上到右下
    // 转移：l[i, j] = (text[i] == text[j])(1 or 0) + max{l[i-1, j], l[i, j-1]}
    // solution: d[n,m] 右下角
    // 时间复杂度：O(nm) 双层循环
    // 如果考虑打印出解呢？
    // 应该还是用一个数组表示路径 因为我们所选择的i和j分别表示text1和text2的索引
    // 使用一个prev数组，从右下角开始一路找到右上角
    // 那么对于每一步，我们要么向左，要么向上，要么向左上
    // 这个根据转移方程来就行
    // 如果我们向左上，说明这是公共元素，否则就不是。就这么简单

    static const int max_length = 1024;
    int dp[max_length][max_length];

    // 首先看一下dp[0][0]
    if (text1[0] == text2[0]) {
        dp[0][0] = 1;
    } else {
        dp[0][0] = 0;
    }

    // 首先初始化状态
    // 不对，这里的初始化没有写对
    int i = 0;
    // 因为上面考虑了0 0 所以这里可以从1开始
    for (int j = 1; j < text2.size(); j++) {
        // 这里不能只比较i和j
        // 只要从0->j出现过i dp就应该是1才对
        if (text1[i] == text2[j] || dp[i][j - 1] == 1) {
            dp[i][j] = 1;
        } else {
            dp[i][j] = 0;
        }
    }

    int j = 0;
    for (int i = 1; i < text1.size(); i++) {
        if (text1[i] == text2[j] || dp[i - 1][j] == 1) {
            dp[i][j] = 1;
        } else {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i < text1.size(); i++) {
        for (int j = 1; j < text2.size(); j++) {
            // 卧槽，这里的逻辑不对
            // 实际上是按照text1[i] == text2[j] 分成两种情况
            if (text1[i] == text2[j]) {
                // 那么就是text1和text2都不看i和j
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                // 否则 因为i和j不一样，所以就看看两个序列分别不看最后一个
                // 哪个最长
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[text1.size() - 1][text2.size() - 1];
}

int main() {}