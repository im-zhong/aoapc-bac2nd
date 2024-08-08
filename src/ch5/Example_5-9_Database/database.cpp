// 2024/8/8
// zhangzhong

#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

void is_pnf(int row, int col) {
    auto line = std::string{};

    // 二维数组表示一个database
    auto database = std::vector<std::string>{};

    for (int i = 0; i < row; i++) {
        // std::cin >> line;
        std::getline(std::cin, line);
        size_t offset = 0;
        while (offset < line.size()) {
            auto it = line.find(",", offset);
            if (it == line.npos) {
                it = line.size();
            }
            database.push_back(
                std::string{line.begin() + offset, line.begin() + it});
            offset = it + 1;
        }
    }

    // for (const auto& field : database) {
    //     std::cout << field << std::endl;
    // }

    // for (int r = 0; r < row; r++) {
    //     for (int c = 0; c < col; c++) {
    //         int i = r * col + c;

    //         // 这个破题遍历都不好遍历
    //         // 我们要找到的是有相同值的两行
    //     }
    // }

    auto bnfs = std::map<std::pair<int, int>, int>{};

    // for (int c = 0; c < col; c++) {
    //     for (int r1 = 0; r1 < row - 1; r1++) {
    //         for (int r2 = r1 + 1; r2 < row; r2++) {
    //             if (database[r1 * col + c] == database[r2 * col + c]) {

    //                 auto it = bnfs.find({r1, r2});
    //                 if (it != bnfs.end()) {
    //                     std::printf("NO\n");
    //                     std::printf("%d %d\n", r1 + 1, r2 + 1);
    //                     std::printf("%d %d\n", it->second + 1, c + 1);
    //                     return;
    //                 }

    //                 // 把有相同列的两行统计出来
    //                 // 这是一个pair，我们在hash中存储这个pair即可
    //                 // 始终保证 r1 < r2
    //                 // map <<r1,r2>, column>
    //                 //
    //                 只要在后续的排查中，发现有任何一个已经存在的pair和我门的行一样，但是列不一样，就不是PNF的
    //                 // 否则就是PNF的

    //                 bnfs.insert({{r1, r2}, c});
    //             }
    //         }
    //     }
    // }

    // 2700ms
    // 字符串进行匹配还是太慢了，或许使用id来匹配更快
    // 但是这样真的简单，而且感觉也不会快多少吧
    for (int c1 = 0; c1 < col - 1; c1++) {
        for (int c2 = c1 + 1; c2 < col; c2++) {
            auto bnfs = std::map<std::pair<std::string, std::string>, int>{};
            for (int r = 0; r < row; r++) {
                auto pair = std::make_pair(database[r * col + c1],
                                           database[r * col + c2]);
                auto it = bnfs.find(pair);
                if (it != bnfs.end()) {
                    std::printf("NO\n");
                    std::printf("%d %d\n", it->second + 1, r + 1);
                    std::printf("%d %d\n", c1 + 1, c2 + 1);
                    return;
                }
                bnfs.insert({pair, r});
            }
        }
    }
    std::printf("YES\n");
}

int main() {
    int n = 0, m = 0;
    while (std::scanf("%d %d\n", &n, &m) == 2) {
        is_pnf(n, m);
    }
}