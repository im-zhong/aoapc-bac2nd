// 2024/8/8
// zhangzhong

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

void unix_ls(int count) {

    std::cout
        << "------------------------------------------------------------\n";

    auto files = std::vector<std::string>{};
    auto file = std::string{};
    for (int i = 0; i < count; i++) {
        std::cin >> file;
        files.push_back(file);
    }
    std::sort(files.begin(), files.end());

    // find the longest length
    int max_length = 0;
    for (const auto& file : files) {
        if (file.size() > max_length) {
            max_length = file.size();
        }
    }

    // Computes the largest integer value not greater than num
    auto column_count = static_cast<int>(std::floor(62.0 / (max_length + 2)));
    //
    auto row_count = static_cast<int>(
        std::ceil(static_cast<double>(files.size()) / column_count));

    int rightmost_column = column_count - 1;
    if (files.size() < column_count) {
        rightmost_column = files.size() - 1;
    }

    for (int r = 0; r < row_count; r++) {
        for (int c = 0; c < column_count; c++) {
            int i = c * row_count + r;
            if (i >= files.size()) {
                std::cout << std::endl;
                return;
            }

            std::cout << files[i];
            // 还要输出空格
            // 有可能我们充不满所有的列
            // 在这种情况下，rightmost column 就不是最后一列
            auto space_count = (max_length + 2 - files[i].size());
            if (c == rightmost_column) {
                space_count -= 2;
            }
            for (int s = 0; s < space_count; s++) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    int file_count = 0;
    while (true) {
        if (std::scanf("%d", &file_count) != 1) {
            break;
        }
        unix_ls(file_count);
    }
}