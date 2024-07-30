// 2024/7/30
// zhangzhong

#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

// 我们写一个函数专门用于输出小数
void print_decimals(const vector<int>& decimals, int cycle_length) {

    // 不对啊，cycle_index可以通过cycle_length 算出来！！！
    // we found the repeating!

    // 然后输出非循环的部分
    // 整数部分
    printf("%d.", decimals[0]);

    int repeating_index = decimals.size() - cycle_length;

    // 然后是从begin + 1 到 it - 1 部分 都是不循环的部分
    for (int i = 1; i < repeating_index; i++) {
        printf("%d", decimals[i]);
    }

    // 然后是循环小数部分
    printf("(");
    for (
        int i = repeating_index;
        // BUG：这里有一个题干描述的坑，就是右边的字符不能超过50个，而不是重复的字符不超过50个。。。
        i < repeating_index + 50 - (repeating_index - 1) && i < decimals.size();
        i++) {
        printf("%d", decimals[i]);
    }
    if (cycle_length >= 50) {
        printf("...");
    }
    printf(")\n");
}

int main() {
    // numerator >= 0
    // denominator > 0
    int numerator = 0, denominator = 0;

    vector<int> decimals;
    vector<int> remainders;

    // numerator = 1, denominator = 6

    // int test_case_count = 0;
    while (scanf("%d%d", &numerator, &denominator) == 2) {
        int original_numerator = numerator;

        // test_case_count++;
        // if (test_case_count != 1) {
        //     printf("\n");
        // }

        decimals.clear();
        remainders.clear();

        int cycle_length = 0;

        while (true) {
            // q = 0
            int quotient = numerator / denominator;
            decimals.push_back(quotient);
            // r = 1
            int remainder = numerator % denominator;

            if (remainder == 0) {
                // 如果到这里就表示我们除尽了
                // 已经没有尝试的必要的，直接输出就行
                // 为了能使用一个统一的输出
                cycle_length = 1;
                decimals.push_back(0);
                break;
            }

            numerator = remainder * 10;

            // before push to the remainder, check if we get the repeating
            auto it = find(remainders.begin(), remainders.end(), remainder);
            if (it != remainders.end()) {
                cycle_length = static_cast<int>(remainders.end() - it);
                break;
            }

            // push remainder to the vector
            remainders.push_back(remainder);
        }

        // 我们还需要保存整个小数部分
        // 整数部分直接到时候再次计算就行了
        printf("%d/%d = ", original_numerator, denominator);

        // 只要我们跳到了这里，就说明我们已经找到了循环
        // 直接输出就行了
        print_decimals(decimals, cycle_length);
        printf("   %d = number of digits in repeating cycle\n\n", cycle_length);
    }
}