// 2024/12/11
// zhangzhong

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

constexpr int row_size = 6;
constexpr int col_size = 5;

char grid_1[row_size][col_size];
char grid_2[row_size][col_size];

std::string GetKthPassword(int k) {

    // 首先拿到每一列中不同的字符串
    // 每个字符都放到一个集合中，这个集合采用ordered set来存放
    std::vector<std::vector<char>> chars(col_size);

    for (int col = 0; col < col_size; col++) {
        for (int row_1 = 0; row_1 < row_size; row_1++) {
            for (int row_2 = 0; row_2 < row_size; row_2++) {
                if (grid_1[row_1][col] == grid_2[row_2][col]) {
                    chars[col].push_back(grid_1[row_1][col]);
                }
            }
        }
        // 果然是因为这个原因，可能存在重复元素
        // 对数组排序然后去重
        std::sort(chars[col].begin(), chars[col].end());
        // Removes all except the first element from every consecutive group of
        // equivalent elements from the range [first, last) and returns a
        // past-the-end iterator for the new end of the range.
        auto iter = std::unique(chars[col].begin(), chars[col].end());
        chars[col].erase(iter, chars[col].end());
    }

    // 然后计算总的数量

    // 可以预算计算出前几个字母固定的情况下的总的密码数量
    // 其实就是倒着乘
    int password_counts[col_size + 1];
    password_counts[col_size] = 1;
    for (int col = col_size - 1; col >= 0; col--) {
        password_counts[col] = password_counts[col + 1] * chars[col].size();
    }
    int all_password_count = password_counts[0];
    if (k > all_password_count) {
        return "NO";
    }

    std::string password;
    int offset = 0;
    // 依次计算五个位置的字母
    for (int col = 0; col < col_size; col++) {
        // 我们使用一个游标 指向当前选择的密码
        // 因为我们需要遍历字符 所以chars 里面最好是一个vector 而不是一个set

        // 我们还需要一个offset
        for (int i = 0; i < chars[col].size(); i++) {

            if (k <= offset + (i + 1) * password_counts[col + 1]) {
                // 密码就在这里面
                // offset 就表示我们跳过了多少个密码
                offset += i * password_counts[col + 1];
                password.push_back(chars[col][i]);
                break;
            }
        }

        // 我们有可能
    }

    return password;
}

int main() {
    int test_count = 0;
    std::cin >> test_count;

    for (int t = 0; t < test_count; t++) {

        int k = 0;
        std::cin >> k;
        // 我真是服了 这里又没有读到换行
        // 到底应该如何优雅的处理这种情况呢？
        // TODO
        std::string line;
        std::getline(std::cin, line);

        for (int row = 0; row < row_size; row++) {
            std::string line;
            std::getline(std::cin, line);
            for (int col = 0; col < col_size; col++) {
                grid_1[row][col] = line[col];
            }
        }

        for (int row = 0; row < row_size; row++) {
            std::string line;
            std::getline(std::cin, line);
            for (int col = 0; col < col_size; col++) {
                grid_2[row][col] = line[col];
            }
        }

        std::string password = GetKthPassword(k);
        std::cout << password << "\n";
    }
}