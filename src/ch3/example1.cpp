// 2024/7/19
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cstdio>
#include <cstring>
#include <doctest/doctest.h>

char tex[4096] = {};
char transformed_tex[4096] = {};

// TEST_CASE("example 3-1 Tex Quotes, UVa 272") {
//     // 输入的问题
//     // 应该要一直读到EOF为止
//     // scanf %s读到空格就停了
//     // std::scanf("%s", tex);
//     char* p_tex = tex;
//     int ch = 0;
//     while ((ch = std::getchar()) != EOF) {
//         *p_tex++ = static_cast<char>(ch);
//     }

//     char* p = transformed_tex;

//     bool in_quote = false;
//     for (int i = 0; i < strlen(tex); i++) {
//         if (tex[i] == '\"') {
//             char quote = '`';
//             if (in_quote) {
//                 quote = '\'';
//             }

//             // https://en.cppreference.com/w/cpp/language/operator_precedence
//             // p++ > *p
//             // so p++ runs first, but returns the original p
//             // so *p access the origin memory location, but p already point
//             // to next location
//             *p++ = quote;
//             *p++ = quote;

//             in_quote = !in_quote;
//         } else {
//             *p++ = tex[i];
//         }
//     }
//     *p = '\0';

//     std::printf("%s\n", transformed_tex);
// }

TEST_CASE("example 3-1 Tex Quotes, UVa 272, book solution") {
    bool in_quote = false;
    int ch = 0;
    while ((ch = std::getchar()) != EOF) {
        char c = static_cast<char>(ch);
        if (c == '\"') {
            if (in_quote) {
                std::printf("''");
            } else {
                std::printf("``");
            }
            in_quote = !in_quote;
        } else {
            std::printf("%c", c);
        }
    }
}