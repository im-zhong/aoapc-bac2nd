// 2024/10/15
// zhangzhong

#include <iostream>
#include <list>
#include <string>

struct Range {
    size_t begin;
    size_t end;
};

std::list<Range> broke_line(const std::string& line) {

    std::list<Range> ranges;
    size_t begin = 0;
    size_t end = 0;

    // 默认是插在最后的
    bool is_insert_to_tail = true;

    for (const auto& ch : line) {

        end++;

        if (ch == '[' || ch == ']') {
            // put the current range to the head of the list
            // 我们不应该输出 [] a  所以end-1

            auto range = Range{begin, end - 1};
            if (is_insert_to_tail) {
                ranges.push_back(range);
            } else {
                ranges.push_front(range);
            }
            if (ch == '[') {
                is_insert_to_tail = false;
            } else {
                is_insert_to_tail = true;
            }

            begin = end;
        }
    }
    if (begin < end) {
        auto range = Range{begin, end};
        if (is_insert_to_tail) {
            ranges.push_back(range);
        } else {
            ranges.push_front(range);
        }
    }
    return ranges;
}

int main() {

    std::string line;

    while (std::cin >> line) {

        auto texts = broke_line(line);

        // according to the begin and end in texts
        // print out the broken line
        for (const auto& range : texts) {
            std::cout << line.substr(range.begin, range.end - range.begin);
        }
        std::cout << "\n";
    }
}