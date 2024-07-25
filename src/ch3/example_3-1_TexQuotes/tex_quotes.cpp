// 2024/7/25
// zhangzhong

#include <cstdio>
using namespace std;

int main() {
    bool in_quote = false;
    int ch = 0;
    while ((ch = getchar()) != EOF) {
        char c = static_cast<char>(ch);
        if (c == '\"') {
            if (in_quote) {
                printf("''");
            } else {
                printf("``");
            }
            in_quote = !in_quote;
        } else {
            printf("%c", c);
        }
    }
}
