// 2024/7/31
// zhangzhong

#include <cstdio>
#include <unordered_map>

using namespace std;

char puzzle[128] = "";
char answer[128] = "";

int main() {
    int round = 0;
    while (true) {
        scanf("%d", &round);
        if (round == -1) {
            return 0;
        }
        printf("Round %d\n", round);

        scanf("%s%s", puzzle, answer);
        unordered_map<char, int> puzzle_chars;
        // unordered_map<char, int> answer_chars;

        // first collect all the characters in puzzle
        for (char* p = puzzle; *p; p++) {
            puzzle_chars.insert({*p, 0});
        }

        int strokes = 7;
        bool is_win = false;
        for (char* p = answer; *p && strokes > 0; p++) {
            // 关于并发：
            // 为什么不直接使用结构化的语句来组织任务呢？
            // 即然任务存在运行时才知道的约束，为什么不直接使用if语句来告诉调度器
            // 要满足某个条件才能执行某个任务呢？
            // 这才是真正的结构化并发！

            // BUG: 猜对的字幕再去猜也算错
            // *p not in puzzle
            if (puzzle_chars.find(*p) == puzzle_chars.end()) {
                // do not found the
                // then check if we alread guess it
                // if (answer_chars[*p] > 0) {
                //     // then we already guess it, we do not loss stroke
                // } else {
                // we loss the storke
                strokes--;
                // }
            } else {
                // *p in puzzle
                // then we found one word
                // puzzle_chars[*p]++;
                // then we remove the word from puzzle
                puzzle_chars.erase(*p);
                // if all puzzle_chars > 0, then we are win
                // is_win = true;
                // for (const auto pair : puzzle_chars) {
                //     if (pair.second == 0) {
                //         is_win = false;
                //         break;
                //     }
                // }
                // if (is_win) {
                //     break;
                // }
                if (puzzle_chars.empty()) {
                    // then we win
                    is_win = true;
                    break;
                }
            }

            // answer_chars[*p]++;
        }

        if (is_win) {
            printf("You win.\n");
        } else {
            if (strokes > 0) {
                printf("You chickened out.\n");
            } else {
                printf("You lose.\n");
            }
        }
    }
}