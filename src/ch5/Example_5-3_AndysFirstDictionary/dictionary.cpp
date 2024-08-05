// 2024/8/5
// zhangzhong

#include <cctype>
#include <cstring>
#include <set>
#include <string>

using namespace std;

char word[128] = "";

int main() {

    set<string> words;

    // scanf 必须要判断读到了多少东西
    while (scanf("%s", word) == 1) {
        // check if word contains non alpebet word
        // if it contains then split it
        char* begin = word;

        // 卧槽，这种重复读取到word里面的写法，不能这样循环来写
        // 因为有可能我们会碰到没有被清理掉的上一次读取的内容
        // 导致死循环
        // 不对，怎么会呢？
        for (char* p = word; *p; p++) {
            // 我们读到一个完整的单词 没有标点符号 反而没有插入
            if (isalpha(*p)) {

                *p = tolower(*p);
                if (*begin == '\0') {
                    begin = p;
                }
            } else {
                // else we found a biaodianfuhao
                // split the word[begin, p)
                *p = '\0';

                if (*begin != '\0') {
                    words.insert(string{begin});
                    begin = p;
                }
            }
        }

        if (*begin != '\0') {
            words.insert(string{begin});
        }
    }

    for (const auto& word : words) {
        printf("%s\n", word.c_str());
    }
}