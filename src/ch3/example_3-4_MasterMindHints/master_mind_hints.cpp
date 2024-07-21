// 2024/7/21
// zhangzhong

#include <cstdio>
#include <cstring>

const int digit_count = 10;
int answer_digits[digit_count] = {};
int answer_digits_copy[digit_count] = {};

// bool guess_digits[digit_count] = {};
// bool right_position_digits[digit_count] = {};
// bool show_both_digits[digit_count] = {};

char answer[64] = "\0";
char answer_copy[64] = "\0";
char guess[64] = "\0";

int main(int argc, char* argv[]) {
    int current_game_round = 0;

    int seq_len = 0;
    int num = 0;
    while (std::scanf("%d", &seq_len) != 0 && seq_len != 0) {
        // if (seq_len == 0) {
        //     break;
        // }

        // new game round begin
        current_game_round += 1;
        std::printf("Game %d:\n", current_game_round);
        std::fflush(stdout);

        std::memset(answer_digits, 0, sizeof(answer_digits));
        // get the answer sequence
        char* p_answer = answer;
        for (int i = 0; i < seq_len; i++) {
            std::scanf("%d", &num);
            // insert into answer digits
            answer_digits[num] += 1;
            // push the number to the end of the answer string
            *p_answer++ = '0' + num;
        }

        // get the guess sequence
        while (true) {
            // copy the answer digits
            for (int i = 0; i < digit_count; i++) {
                answer_digits_copy[i] = answer_digits[i];
            }
            std::memcpy(answer_copy, answer, seq_len + 1);

            // std::memset(guess_digits, 0, digit_count);
            char* p_guess = guess;
            for (int i = 0; i < seq_len; i++) {
                std::scanf("%d", &num);
                // guess_digits[num] = true;
                *p_guess++ = '0' + num;
            }

            // check if this game round is end
            // if only 0 in the guess digits
            int sum = 0;
            for (int i = 0; i < seq_len; i++) {
                sum += (guess[i] - '0');
            }
            if (sum == 0) {
                // the current game round is end
                break;
            }

            // statistic there are how many number that the position is right
            // also we should get the right position digits
            // std::memset(right_position_digits, 0, digit_count);
            int A = 0;
            for (int i = 0; i < seq_len; i++) {
                if (answer_copy[i] == guess[i]) {
                    A += 1;
                    // answer_copy[i] = 'x';
                    answer_digits_copy[guess[i] - '0'] -= 1;
                    guess[i] = 'x';
                }
            }

            int B = 0;
            for (int i = 0; i < seq_len; i++) {
                if (guess[i] == 'x') {
                    continue;
                }

                if (answer_digits_copy[guess[i] - '0'] > 0) {
                    answer_digits_copy[guess[i] - '0'] -= 1;
                    B += 1;
                }
            }

            // statitic there are how many number that show both but position is
            // not right
            // first, get the intersection of answer digits and guess digits
            // std::memset(show_both_digits, 0, digit_count);
            // for (int i = 0; i < digit_count; i++) {
            //     if (answer_digits[i] && guess_digits[i]) {
            //         show_both_digits[i] = true;
            //     }
            // }
            // // then, get the difference of show both digits - right position
            // // digits
            // for (int i = 0; i < digit_count; i++) {
            //     if (show_both_digits[i] && right_position_digits[i]) {
            //         show_both_digits[i] = false;
            //     }
            // }

            // int B = 0;
            // for (int i = 0; i < digit_count; i++) {
            //     if (show_both_digits[i]) {
            //         B += 1;
            //     }
            // }

            std::printf("    (%d,%d)\n", A, B);
            std::fflush(stdout);
        }
    }
}