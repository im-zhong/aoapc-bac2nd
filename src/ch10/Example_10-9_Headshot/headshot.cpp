// 2024/12/15
// zhangzhong

#include <iostream>
#include <string>

int main() {

    std::string buffer;
    while (std::cin >> buffer) {
        if (buffer.empty()) {
            break;
        }

        int slot_count = buffer.size();
        int zero_count = 0;
        int double_zero_count = 0;

        // repeat trick, copy!
        buffer.push_back(buffer.front());
        for (int i = 1; i < buffer.size(); i++) {
            if (buffer[i] == '0') {
                zero_count++;
                if (buffer[i - 1] == '0') {
                    double_zero_count++;
                }
            }
        }

        double p1 = (double)(double_zero_count) / (double)(zero_count);
        double p2 = (double)zero_count / (double)(slot_count);
        if (p1 > p2) {
            std::cout << "SHOOT";
        } else if (p2 > p1) {
            std::cout << "ROTATE";
        } else {
            std::cout << "EQUAL";
        }
        std::cout << "\n";
    }
}