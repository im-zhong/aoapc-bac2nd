// 2024/8/6
// zhangzhong
// solution from book: standardize

#include <algorithm>
#include <array>
#include <cctype>
#include <cstdio>
#include <map>
#include <string>
#include <vector>

using namespace std;

auto standardize(string const& word) -> string {
    auto str = string{word};
    for (auto& ch : str) {
        ch = tolower(ch);
    }
    sort(str.begin(), str.end());
    return str;
}

auto buffer = array<char, 128>{};

int main() {
    auto original_words = vector<string>{};
    auto standardized_words = map<string, int>{};
    while (scanf("%s", buffer.data()) == 1) {
        auto word = string{buffer.data()};
        if (word == "#") {
            break;
        }

        original_words.push_back(word);
        standardized_words[standardize(word)]++;
    }

    auto final_words = vector<string>{};

    // 这样写比较慢，因为原始数组会被遍历许多次
    // n * n * logn
    // 可以反过来进行遍历，就是遍历数组而不是遍历map，
    // for (auto const& value : standardized_words) {
    //     if (value.second != 1) {
    //         continue;
    //     }

    //     for (auto const& original_word : original_words) {
    //         if (standardize(original_word) == value.first) {
    //             final_words.push_back(original_word);
    //         }
    //     }
    // }
    // TIP: 这样反过来写又快又简单！！！
    for (auto const& word : original_words) {
        if (standardized_words[standardize(word)] != 1) {
            continue;
        }
        final_words.push_back(word);
    }
    sort(final_words.begin(), final_words.end());
    for (const auto& word : final_words) {
        printf("%s\n", word.c_str());
    }
}