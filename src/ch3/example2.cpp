// 2024/7/19
// zhangzhong

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cstdio>
#include <cstring>
#include <doctest/doctest.h>

// just construct a map table
// char - 'A'
// char letter_map_table[26] = {
//     // A -> 0
//     0,
//     // B -> V
//     'V',
//     // C -> X
//     'X',
//     // D -> S
//     'S',
//     // E -> W
//     'W',
//     // F -> D
//     'D',
//     // G -> F
//     'F',

//     // H -> G
//     'G',
//     // I -> U
//     'U',
//     // J -> H
//     'H',
//     // K -> J
//     'J',
//     // L -> K
//     'K',
//     // M -> N
//     'N',
//     // N -> B
//     'B',

//     // O -> I
//     'I',
//     // P -> O
//     'O',
//     // Q -> 0
//     0,
//     // R -> E
//     'E',
//     // S -> A
//     'A',
//     // T -> R
//     'R',

//     // U -> Y
//     'Y',
//     // V -> C
//     'C',
//     // W -> Q
//     'Q',
//     // X -> Z
//     'Z',
//     // Y -> T
//     'T',
//     // Z -> 0
//     0,
// };

// char digit_map_table[10] = {
//     // 0 -> `
//     '9',
//     // 1 -> `
//     '`',
//     // 2 -> 1
//     '1',
//     // 3 -> 2
//     '2',
//     // 4 -> 3
//     '3',
//     // 5 -> 4
//     '4',
//     // 6 -> 5
//     '5',
//     // 7 -> 6
//     '6',
//     // 8 -> 7
//     '7',
//     // 9 -> 8
//     '8'};

// 标点符号比较分散，可以写成一个switch
// char punctuaction_map_table[]

// 发现从39 - 93 是包含所有的字符的
// 这样编写一张表是可以直接进行映射的，应该是最简单的实现方法
char map_table[] = {
    // 39 '
    ';',
    // 40 (
    0,
    // 41 )
    0,
    // 42 *
    0,
    // 43 +
    0,
    // 44 ,
    'M',
    // 45 -
    '0',
    // 46 .
    ',',
    // 47 /
    '.',
    // 48 0 -> `
    '9',
    // 49 1 -> `
    '`',
    // 50 2 -> 1
    '1',
    // 51 3 -> 2
    '2',
    // 52 4 -> 3
    '3',
    // 53 5 -> 4
    '4',
    // 54 6 -> 5
    '5',
    // 55 7 -> 6
    '6',
    // 56 8 -> 7
    '7',
    // 57 9 -> 8
    '8',
    // 58 :
    0,
    // 59 ;
    'L',
    // 60 <
    0,
    // 61 =
    0,
    // 62 >
    0,
    // 63 ?
    0,
    // 64 A
    0,

    // 65
    // A -> 0
    0,
    // B -> V
    'V',
    // C -> X
    'X',
    // D -> S
    'S',
    // E -> W
    'W',
    // F -> D
    'D',
    // G -> F
    'F',

    // H -> G
    'G',
    // I -> U
    'U',
    // J -> H
    'H',
    // K -> J
    'J',
    // L -> K
    'K',
    // M -> N
    'N',
    // N -> B
    'B',

    // O -> I
    'I',
    // P -> O
    'O',
    // Q -> 0
    '\t',
    // R -> E
    'E',
    // S -> A
    'A',
    // T -> R
    'R',

    // U -> Y
    'Y',
    // V -> C
    'C',
    // W -> Q
    'Q',
    // X -> Z
    'Z',
    // Y -> T
    'T',
    // 90 Z -> 0
    0,

    // 91 [ -> P
    'P',
    // 92 '\'
    ']',
    // 93 ]
    '[',
};

// TEST_CASE("example 3-2 WERTYU UVa10082") {
//     int ch = 0;
//     while ((ch = std::getchar()) != EOF) {
//         if (ch == ' ') {
//             std::printf(" ");
//         } else {
//             std::printf("%c", map_table[ch - '\'']);
//         }
//     }
//     std::printf("\n");
// }

char map_table2[] = "`1234567890-=\tQWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";
TEST_CASE("example 3-2 WERTYU UVa10082") {
    int ch = 0;
    while ((ch = std::getchar()) != EOF) {
        if (ch == ' ') {
            std::printf(" ");
        } else {
            char* p = std::strchr(map_table2, ch);
            std::printf("%c", *(p - 1));
        }
    }
    std::printf("\n");
}
