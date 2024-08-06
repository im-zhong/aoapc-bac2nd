// 2024/8/6
// zhangzhong

#include <cctype>
#include <cstdio>
#include <map>
#include <string>
#include <vector>

using namespace std;

char buffer[128] = "";

bool is_rearranged(const string& lhs, const string& rhs) {
    if (lhs.size() != rhs.size()) {
        return false;
    }

    if (lhs == rhs) {
        return true;
    }

    const int alphabet_count = 26;
    vector<int> alphabet_lhs(alphabet_count, 0);
    for (auto ch : lhs) {
        alphabet_lhs[tolower(ch) - 'a']++;
    }
    vector<int> alphabet_rhs(alphabet_count, 0);
    for (auto ch : rhs) {
        alphabet_rhs[tolower(ch) - 'a']++;
    }

    // then this two vector should be the same, then the two words could be
    // rearranged
    for (size_t i = 0; i < alphabet_count; i++) {
        if (alphabet_lhs[i] != alphabet_rhs[i]) {
            return false;
        }
    }
    return true;
}

int main() {

    auto words = map<string, bool>{};

    // 首先写一个函数，判断两个两个单词能否通过重排得到
    // 这个其实相当简单
    while (scanf("%s", buffer) == 1) {
        auto word = string{buffer};
        if (word == "#") {
            break;
        }

        // auto to_be_erased = vector<string>{};
        bool is_rearranged_flag = false;
        for (auto& other_word : words) {
            if (is_rearranged(other_word.first, word)) {
                // TIP:
                // 这种需要在遍历的时候删除元素的情况太常见了
                // 要怎么写才好呢?
                // 哎！最好的方法是不删除啊！！！
                // 就像数据库对待数据的方式一样
                // 假删除
                // to_be_erased.push_back(other_word);
                other_word.second = true;
                is_rearranged_flag = true;
            } else {
            }
        }
        if (!is_rearranged_flag) {
            words.insert({word, false});
        }
    }

    for (auto const& word : words) {
        if (!word.second) {
            printf("%s\n", word.first.c_str());
        }
    }
}