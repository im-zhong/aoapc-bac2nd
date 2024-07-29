// 2024/7/29
// zhangzhong

#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

int row = 0;
int col = 0;
char puzzle[11][11] = {};
int eligible_number[10][10] = {};

char word[16] = "";

// void print_across_words() {
//     int no = 0;
//     for (int r = 0; r < row; r++) {
//         char* p = puzzle[r];
//         char* end = puzzle[r] + col;

//         while (p < end) {
//             // find first not *
//             // find如果找不到 返回的应该是end
//             // 而end应该刚好就是最后一个指针的位置

//             // find first not *
//             p = find_if_not(p, end, [](char ch) -> bool { return ch == '*';
//             }); if (p == end) {
//                 break;
//             }

//             auto it = find(p, end, '*');

//             // then we just output the
//             // p指向的指针位置就是no的位置
//             // TODO: 所有的 * 全部换成 \0, 同时在puzzle周围两圈全部整成\0
//             // 或者我们应该在最开始初始化的时候，全整成\0
//             // 但是这个对列的输出也没有帮助
//             // 不对，是有帮助的
//             // 不过我们需要额外的空间来保存序号，并且还需要排序
//             // 或许还不如直接实现列的逻辑呢

//             printf("%3d.%s\n", eligible_number[r][p - puzzle[r]], p);
//             p = it + 1;
//         }
//     }
// }

void print_across_words() {
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            if (eligible_number[r][c] == 0) {
                continue;
            }
            // 那么和列对应的
            // 只要我们左边没有格子或者是黑格子 我们就是一个起点
            if (c == 0 || puzzle[r][c - 1] == '*') {
                char* p = word;

                for (int tc = c; tc < col && puzzle[r][tc] != '*'; tc++) {
                    *p++ = puzzle[r][tc];
                }
                *p = '\0';
                printf("%3d.%s\n", eligible_number[r][c], word);
            }
        }
    }
}

void print_down_words() {

    // 不对！
    // 我好像意识到了什么
    // 这道题好像把neligible numbers算出来了其实就已经相当于解完了
    // 因为每一个staring number都会对应至少一个单词
    // 我们实际上只需要遍历所有有数字的地方，然后判断这里是否存在一个单词
    // 然后去puzzle里面取出来就ok啦！

    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            if (eligible_number[r][c] == 0) {
                continue;
            }

            // check if exists a down words
            // down words的条件就是上面是黑的或者没有

            // 反证：如果上面有白的，那么肯定从上面就是一个down words
            // 我们就不是起点
            if (r == 0 || puzzle[r - 1][c] == '*') {
                char* p = word;

                // 向下遍历直到找到下一个*或者触底
                for (int tr = r; tr < row && puzzle[tr][c] != '*'; tr++) {
                    *p++ = puzzle[tr][c];
                }
                *p = '\0';
                printf("%3d.%s\n", eligible_number[r][c], word);
            }
        }
    }
}

void calculate_eligible_numbers() {
    memset(eligible_number, 0, sizeof(eligible_number));

    int no = 0;
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            // first we should not be black
            if (puzzle[r][c] == '*') {
                continue;
            }

            if (r == 0) {
                // if we at the first row, we just put all the number
                ++no;
                eligible_number[r][c] = no;
            } else if (c == 0) {
                // 实际上第一行和第一列都有数字
                ++no;
                eligible_number[r][c] = no;
            } else {
                // if left of ourself is out of edge or is black
                // we add
                if (puzzle[r][c - 1] == '*') {
                    ++no;
                    eligible_number[r][c] = no;
                } else if (puzzle[r - 1][c] == '*') {
                    // if above ourself is black
                    ++no;
                    eligible_number[r][c] = no;
                }
            }
        }
    }
}

int main() {
    int current_test_case = 0;
    while (true) {
        scanf("%d", &row);
        if (row == 0) {
            return 0;
        }

        scanf("%d", &col);

        if (current_test_case != 0) {
            printf("\n");
        }

        for (int r = 0; r < row; r++) {
            // read one line at each time
            scanf("%s", puzzle[r]);
        }

        // calculate the eligible numbers
        calculate_eligible_numbers();

        current_test_case++;
        printf("puzzle #%d:\n", current_test_case);
        // output for Across words
        printf("Across\n");
        print_across_words();

        // output for Down words
        printf("Down\n");
        print_down_words();
    }
}