// 2024/10/15
// zhangzhong

#include <iostream>

void read_block(int train_count) {
    while (true) {
        // read one line
        int min = 100000;
        int max = 0;
        int train_id = 0;
        int yes_or_no = 0;
        for (int i = 0; i < train_count; ++i) {
            // 因为是顺序读取的，所以我们是不需要保存的，只需要读取一遍其实就知道对不对了
            std::cin >> train_id;
            if (train_id == 0) {
                // this block is end, we move to the next block
                return;
            }

            if (yes_or_no != 0) {
                continue;
            }

            // 首先做检查
            if (train_id < max) {
                // 如果我们比已经出站的最大的列车小，那么我们必须比min小
                // 也就是所有小于max的数必须以逆序出现！
                if (train_id > min) {
                    yes_or_no = -1;
                    std::cout << "No\n";
                }
            }

            if (max < train_id) {
                max = train_id;
            }
            if (min > train_id) {
                min = train_id;
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

        if (case_count != 0) {
            // 最后一个block不能输出回车
            // 但是代码无法知道是不是最后一个block啊
            std::cout << "\n";
        }

        // next read several numbers until we read a zero

        read_block(train_count);

        case_count++;
    }
}