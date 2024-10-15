// 2024/10/15
// zhangzhong

#include <iostream>
#include <stack>

void read_block(int train_count) {
    while (true) {
        // read one line
        // int min = 100000;
        // int max = 0;
        int train_id = 0;
        int yes_or_no = 0;

        int current_train_id = 1;

        auto s = std::stack<int>{};
        for (int i = 0; i < train_count; ++i) {
            std::cin >> train_id;
            if (train_id == 0) {
                // this block is end, we move to the next block
                return;
            }

            if (yes_or_no != 0) {
                continue;
            }

            // when we read a number
            // we should check the top of the stack
            // there is three situation
            // small equal high

            // if the stack is empty
            // just push a new train into the stack until the top train id match
            // the read train id
            // current_train_id++;
            // s.push(current_train_id);

            if (s.empty()) {
                for (; current_train_id <= train_id; current_train_id++) {
                    s.push(current_train_id);
                }
                s.pop();
            } else {

                int top = s.top();
                if (train_id == top) {
                    // pop the train and continue
                    s.pop();
                    continue;
                } else if (train_id < top) {
                    // then we hit the no situation
                    yes_or_no = -1;
                    std::cout << "No\n";
                    continue;
                } else {
                    // train_id > top
                    // continue push to the stack until we hit the train id
                    for (; current_train_id <= train_id; current_train_id++) {
                        s.push(current_train_id);
                    }
                    s.pop();
                }
            }
        }

        if (yes_or_no == 0) {
            std::cout << "Yes\n";
        }
    }
}

int main() {
    int train_count = 0;

    int case_count = 0;

    while (std::cin >> train_count) {
        if (train_count == 0) {
            break;
        }

        // if (case_count != 0) {
        //     // 最后一个block不能输出回车
        //     // 但是代码无法知道是不是最后一个block啊
        //     std::cout << "\n";
        // }

        // next read several numbers until we read a zero

        read_block(train_count);

        // vj这诡异的格式要求啊，真是变幻莫测
        std::cout << "\n";

        case_count++;
    }
}