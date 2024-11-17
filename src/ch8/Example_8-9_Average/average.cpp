// 2024/11/17
// zhangzhong

#include <iostream>
#include <vector>

struct Range {
    int begin;
    int end;
};

Range GetSubsequence(const std::string& sequence, int min_length) {

    // 预先计算前n项he
    std::vector<int> sums;

    int sum = 0;
    // sums表示 [0, i)的序列和
    // 所以 i = 0时，和为零
    // 这样可以非常变黄的计算 [i, j) 和为 sums[j] - sums[i]
    //
    sums.push_back(0);

    for (const char ch : sequence) {
        // ch is '0' or '1'
        sum += ch - '0';
        sums.push_back(sum);
    }

    // 序列和就是 [begin, end) = sums[end] - sums[begin]
    //

    Range range;
    double max_slope = 0;

    for (int begin = 0; begin < sequence.size(); begin++) {
        for (int end = begin + min_length; end <= sequence.size(); end++) {

            // 计算斜率
            double slope = (double)(sums[end] - sums[begin]) / (end - begin);
            if (slope > max_slope) {
                max_slope = slope;
                range = Range{begin, end};
            }
        }
    }

    // 我们输出一下range吧
    // for (int i = range.begin; i != range.end; i++) {
    //     std::cout << sequence[i] << " ";
    // }
    // std::cout << std::endl;

    return range;
}

int main() {
    int case_count = 0;
    std::cin >> case_count;

    for (int c = 0; c < case_count; c++) {
        int length = 0;
        int min_length = 0;
        // char newline = 0;
        std::cin >> length >> min_length;

        std::string line;
        // read the newline
        std::getline(std::cin, line);
        // read the line
        std::getline(std::cin, line);

        Range range = GetSubsequence(line, min_length);
        std::cout << range.begin + 1 << " " << range.end << "\n";
    }
}