// 2024/11/25
// zhangzhong

#include <iostream>

const int max_row = 10;
const int max_col = 100;

void print_array(int* array, int row, int col) {
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {

            std::cout << array[r * max_col + c] << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

int main() {

    const int INF = 1 << 20;

    int row = 0;
    int col = 0;
    // 当结束的时候是EOF的时候 只有这么写才是对的
    while (std::cin >> row >> col) {
        // 因为是二维数组 所以用array更加合适
        int map[max_row][max_col];
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < col; c++) {
                int weight = 0;
                std::cin >> weight;
                map[r][c] = weight;
            }
        }

        // recording the minimal weight
        int minimal_weight[max_row][max_col];
        // for the last col, setting the minimal weight to the weight of its own
        int last_col = col - 1;
        for (int r = 0; r < row; r++) {
            minimal_weight[r][last_col] = map[r][last_col];
        }

        // recording the path
        int next[max_row][max_col];
        // for the last col, set next to -1, means path is end
        for (int r = 0; r < row; r++) {
            next[r][last_col] = -1;
        }

        // start calculating the minimal weight, from the second to last col
        for (int c = col - 2; c >= 0; c--) {
            for (int r = 0; r < row; r++) {

                // min of minimal_weight[r-1 or r or r+1][c+1]
                // but r - 1 could out of range
                // 0 - 1 % row = ? 好像是对的！！！
                // row - 1 + 1 % row = 0
                // r

                // 不对哦，这样无法记录next ，，，还是得从小往大了进行一个比较
                // minimal_weight[r][c] =
                //     map[r][c] +
                //     std::min(minimal_weight[(r + 1) % row][c + 1],
                //              std::min(minimal_weight[(r - 1) % row][c + 1],
                //                       minimal_weight[r][c + 1]));
                // minimal_weight[r][c] = map[r][c];

                int& mw = minimal_weight[r][c];
                mw = INF;
                int& nr = next[r][c];
                nr = INF;

                // [[TIP]]
                // 这里有一个非常重要的trick
                // 当我们想要按照词典序输出时，我们保证严格顺序 就可以
                // 那是因为我们是按照顺序遍历的
                // 但是在这里 因为上下循环的存在 我们不一定按照字典序遍历
                // 所以就不能用严格顺序
                // 只要等于 我们就得看看下标是否更小或者更大
                // r-1, c+1
                // n + 5*k
                // [[BUG]] 这里不对，因为-1 % 5 = -1, 但是 + 5 在取余就对了
                // 因为额外加上的5取余之后不会对结果产生影响
                int next_row = (r + row - 1) % row;
                // [[BUG]]
                // 这里的逻辑全部都不对
                // map[r][c]应该在最后加在mw上才是对的
                if (minimal_weight[next_row][c + 1] <= mw) {
                    if (minimal_weight[next_row][c + 1] < mw) {
                        nr = next_row;
                    } else {
                        nr = std::min(nr, next_row);
                    }
                    mw = minimal_weight[next_row][c + 1];
                    // nr = std::min(nr, next_row);
                }
                next_row = r;
                // [[BUG]]
                // 卧槽，这里不对
                // 这里的逻辑不对，要实现正确更新mw和nr 必须是严格顺序才对
                // 因为我们进到分支内部之后，第一条语句是对的
                // 但是第二条不对
                // 如果我们是严格小于 那么一定要更新
                // 如果不是严格小于，才是比较大小
                // 而且这个nr的更新必须放到更新mw前面 否则mw被修改了
                // 我们的判断就不对了
                if (minimal_weight[next_row][c + 1] <= mw) {
                    if (minimal_weight[next_row][c + 1] < mw) {
                        nr = next_row;
                    } else {
                        nr = std::min(nr, next_row);
                    }
                    mw = minimal_weight[next_row][c + 1];
                }
                next_row = (r + 1) % row;
                if (minimal_weight[next_row][c + 1] <= mw) {
                    if (minimal_weight[next_row][c + 1] < mw) {
                        nr = next_row;
                    } else {
                        nr = std::min(nr, next_row);
                    }
                    mw = minimal_weight[next_row][c + 1];
                    // nr = std::min(nr, next_row);
                }
                mw += map[r][c];
            }
        }

        // 遍历第一行 找到数值最小的行
        int min_row = 0;
        int min_wei = INF;
        for (int r = 0; r < row; r++) {
            if (minimal_weight[r][0] < min_wei) {
                min_wei = minimal_weight[r][0];
                min_row = r;
            }
        }

        // 然后从min_row 开始向后输出即可
        std::cout << min_row + 1;
        int r = min_row;
        for (int c = 0; c < col - 1; c++) {
            std::cout << " " << next[r][c] + 1;
            r = next[r][c];
        }
        std::cout << "\n" << minimal_weight[min_row][0] << "\n";
    }
}