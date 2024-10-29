// 2024/10/29
// zhangzhong

#include <chrono>
#include <fstream>
#include <random>

int main() {
    std::ofstream fout("in.txt");

    std::default_random_engine e(static_cast<uint64_t>(
        std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_real_distribution<double> u(0.0, 1.0);

    // // 0 < a < b < 500
    // 测试用例太多了，有12w个
    // 咱们只取十分之一吧
    for (int a = 1; a < 500; a++) {
        for (int b = a + 1; b < 500; b++) {

            if (u(e) < 0.1) {
                fout << a << " " << b << "\n";
            }
        }
    }
}
