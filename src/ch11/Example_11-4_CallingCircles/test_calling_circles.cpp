// 2025/3/30
// zhangzhong

#include <iostream>
#include <set>
#include <string>
#include <vector>
// 两个set是否相同应该是可以比较的吧

// 感觉这个测试程序不如用python写啊，说实话

// 对于每一行 我们都可以获得一个calling circles
std::set<std::string> GetCallingCircle(const std::string& line){
    // 将circle按照 , 进行拆分 split
    std::set<std::string>

}

std::set<std::set<std::string>> GetCallingCircles(
    const std::vector<std::string>& lines) {}

int main(int argc, char* argv[]) {
    std::string line;
    while (std::getline(std::cin, line)) {
        // 然后我们要持续的读取每一行
        // 直到读取到了一个空行
        std::vector<std::string> lines;
        while (std::getline(std::cin, line)) {
            if (line.empty()) {
                break;
            }
            lines.push_back(line);
        }

        // 然后根据这个lines 我们应该就可以拿到一个set的set
    }
}