// 2024/7/29
// zhangzhong

#include <cstdio>

using namespace std;

int empty_row = -1;
int empty_col = -1;
char puzzle_frame[5][5] = {};

bool check_position(int i) { return i >= 0 && i < 5; }

bool move_from(char direction) {
    int temp_row = empty_row;
    int temp_col = empty_col;

    switch (direction) {
    case 'A':
        temp_row--;
        break;
    case 'B':
        temp_row++;
        break;
    case 'R':
        temp_col++;
        break;
    case 'L':
        temp_col--;
        break;
    }

    if (!check_position(temp_row) || !check_position(temp_col)) {
        return false;
    }

    // swap two positions
    puzzle_frame[empty_row][empty_col] = puzzle_frame[temp_row][temp_col];

    empty_row = temp_row;
    empty_col = temp_col;
    puzzle_frame[empty_row][empty_col] = ' ';
    return true;
}

int main() {
    // first read the puzzle frame
    int current_test_case = 0;

    while (true) {
        for (int row = 0; row < 5; row++) {
            for (int col = 0; col < 5; col++) {
                int letter = getchar();
                if (letter == 'Z') {
                    return 0;
                }
                if (letter == ' ') {
                    empty_row = row;
                    empty_col = col;
                }
                puzzle_frame[row][col] = static_cast<char>(letter);
            }
            // read the newline
            getchar();
        }

        if (current_test_case != 0) {
            putchar('\n');
        }

        // read the move sequence until we touch the 0
        // if we read newline, just ignore it
        bool has_final_configuration = true;
        while (true) {
            char move = getchar();
            if (move == '\n') {
                continue;
            }
            if (move == '0') {
                // get the new line
                getchar();
                break;
            }

            if (!move_from(move)) {
                has_final_configuration = false;
                // 不对！这里不能直接退出
                // 我们需要把剩下的move全部读完
                // 否则会影响下一个puzzle的读取
                while ((move = getchar()) != '0')
                    ;
                // and also get the newline
                getchar();
                break;
            }
        }

        current_test_case++;
        printf("Puzzle #%d:\n", current_test_case);
        if (!has_final_configuration) {
            printf("This puzzle has no final configuration.\n");
        } else {
            for (int row = 0; row < 5; row++) {
                for (int col = 0; col < 5; col++) {
                    putchar(puzzle_frame[row][col]);
                    if (col != 4) {
                        putchar(' ');
                    }
                }
                putchar('\n');
            }
        }
    }
}