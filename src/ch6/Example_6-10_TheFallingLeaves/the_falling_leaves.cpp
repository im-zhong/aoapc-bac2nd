// 2024/10/17
// zhangzhong

#include <cstdint>
#include <iostream>
#include <map>

std::map<int, uint64_t> values;

void construct_tree(int position) {
    uint64_t value = -1;

    std::cin >> value;
    if (value == -1) {
        return;
    }

    // 在position上加上我们的value
    // 最简单的方式是用一个hash table
    // 还有一个方法是用一个循环数组
    values[position] += value;

    construct_tree(position - 1);
    construct_tree(position + 1);
}

int main() {
    int case_id = 1;
    while (true) {
        values.clear();

        construct_tree(0);
        if (values.empty()) {
            break;
        }
        std::cout << "Case " << case_id << ":\n";
        int i = 0;
        for (const auto& pair : values) {
            std::cout << pair.second;
            if (i < values.size() - 1) {
                std::cout << " ";
            }
            i++;
        }
        std::cout << "\n\n";

        ++case_id;
    }
}