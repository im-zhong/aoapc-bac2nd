// 2024/11/10
// zhangzhong

#include <iostream>

// 2^k
// 所以k应该是一个参数，而且最小是1，也就是最小是一个 2*2 的表格
// 我们用缺失方块的位置座位三个L型牌的记号
//  *
// **  0
// *
// **  1
// **
//  *  2
// **
// *   3
// 输入是什么呢？，其实就是k，表示期盼有多大，然后给定一个位置，表示那个黑色的方格
// 输出是什么呢？
// 其实准确的说，就是给整个图分类吗
// 我们把0型牌放到某个位置，那么棋盘上的对应位置就写成零就行了呗
// 这样最终可以把出了黑色的位置，其他的位置都填满就行了

const int maxk = 8;

class ChessboardCoverage {
  public:
    ChessboardCoverage(int k, int row, int col)
        : k_{k}, max_row_{1 << k}, max_col_{1 << k}, black_row_{row},
          black_col_{col} {

        // 我们需要初始化整个棋盘
        for (int r = 0; r < this->max_row_; r++) {
            for (int c = 0; c < this->max_col_; c++) {
                this->chessboard_[r][c] = 0;
            }
        }
        this->chessboard_[row][col] = -1;
    }

    int GetType(int k, int start_row, int start_col, int banned_row,
                int banned_col) {

        int max_row = 1 << k;
        int max_col = 1 << k;

        // for (int r = start_row; r < start_row + max_row; r++) {
        //     for (int c = start_col; c < start_col + max_col; c++) {
        //     }
        // }

        if (banned_row < start_row + (max_row / 2)) {
            // 在上侧
            if (banned_col < start_col + (max_col / 2)) {
                // 在左侧
                return 0;
            } else {
                // 在右侧
                return 1;
            }
        } else {
            // 在下
            if (banned_col < start_col + (max_col / 2)) {
                // 在左
                return 2;
            } else {
                // 在下侧
                return 3;
            }
        }
    }

    void PutChess(int start_row, int start_col, int type) {
        int max_row = 2;
        int max_col = 2;
        // 我们根据type来获取不能修改的格子吧
        // 这样的实现是最稳妥的了
        switch (type) {
        case 0: {

            // this->chessboard_[start_row][start_col] = type;
            this->chessboard_[start_row][start_col + 1] = type + 1;
            this->chessboard_[start_row + 1][start_col] = type + 1;
            this->chessboard_[start_row + 1][start_col + 1] = type + 1;

            break;
        }
        case 1: {
            this->chessboard_[start_row][start_col] = type + 1;
            // this->chessboard_[start_row][start_col + 1] = type;
            this->chessboard_[start_row + 1][start_col] = type + 1;
            this->chessboard_[start_row + 1][start_col + 1] = type + 1;
            break;
        }
        case 2: {
            this->chessboard_[start_row][start_col] = type + 1;
            this->chessboard_[start_row][start_col + 1] = type + 1;
            // this->chessboard_[start_row + 1][start_col] = type;
            this->chessboard_[start_row + 1][start_col + 1] = type + 1;
            break;
        }
        case 3: {
            this->chessboard_[start_row][start_col] = type + 1;
            this->chessboard_[start_row][start_col + 1] = type + 1;
            this->chessboard_[start_row + 1][start_col] = type + 1;
            // this->chessboard_[start_row + 1][start_col + 1] = type;
            break;
        }
        }
        // for (int r = start_row; r < start_row + max_row; r++) {
        //     for (int c = start_col; c < start_col + max_col; c++) {
        //         if (this->chessboard_[r][c] == 0) {
        //             this->chessboard_[r][c] = type + 1;
        //         }
        //     }
        // }
    }

    void SolveImpl(int k, int start_row, int start_col, int banned_row,
                   int banned_col) {
        int max_row = 1 << k;
        int max_col = 1 << k;
        // 递归结束条件是 k == 1
        if (k == 1) {
            // 那么我们只需要根据
            // 我们需要一个函数，用来输出banned 位置是那个位置的
            // 这个输出的结果最好和L型的定义是一样的

            int type =
                this->GetType(k, start_row, start_col, banned_row, banned_col);

            // int max_row = 1 << k;
            // int max_col = 1 << k;
            // // 倒也不用，我们只需要遍历一下这个小方块
            // // 然后在没有涂零的地方，途上type对应的数值就行
            // for (int r = start_row; r < start_row + max_row; r++) {
            //     for (int c = start_col; c < start_col + max_col; c++) {
            //         if (this->chessboard_[r][c] != 0) {
            //             this->chessboard_[r][c] = type + 1;
            //         }
            //     }
            // }

            this->PutChess(start_row, start_col, type);

            return;
        }

        // 否则，我们需要根据type，进行递归
        int type =
            this->GetType(k, start_row, start_col, banned_row, banned_col);
        // 无论如何，我们都得拿到中间四个位置的坐标
        int middle_row = start_row + (max_row / 2) - 1;
        int middle_col = start_col + (max_col / 2) - 1;

        // 无论如何，middle row 这个位置需要被赋值成对应的形状
        // 这个函数还挺常用的，所以封装起来吧
        this->PutChess(middle_row, middle_col, type);

        // 四个子棋盘的起始位置都算出来吧，下面都用得到
        int half_row = max_row / 2;
        int half_col = max_col / 2;

        // 0
        int start_row_0 = start_row;
        int start_col_0 = start_col;
        // 1
        int start_row_1 = start_row;
        int start_col_1 = start_col + half_col;
        // 2
        int start_row_2 = start_row + half_row;
        int start_col_2 = start_col;
        // 3
        int start_row_3 = start_row + half_row;
        int start_col_3 = start_col + half_col;

        switch (type) {
        case 0: {
            // 然后在这里需要把上面被错误覆盖的格子复原
            // 这里的问题，我们不一定需要把这个格子复原
            // 只有这个格子以前是零的时候，才需要把它复原
            // 所以PutChess最好不要动这个格子啊
            // this->chessboard_[middle_row][middle_col] = 0;
            // 然后在四个位置上继续递归
            // 0
            this->SolveImpl(k - 1, start_row_0, start_col_0, banned_row,
                            banned_col);
            // 1
            this->SolveImpl(k - 1, start_row_1, start_col_1,
                            start_row_1 + half_row - 1, start_col_1);
            // 2
            this->SolveImpl(k - 1, start_row_2, start_col_2, start_row_2,
                            start_col_2 + half_col - 1);
            // 3
            this->SolveImpl(k - 1, start_row_3, start_col_3, start_row_3,
                            start_col_3);
            break;
        }

        case 1: {
            // this->chessboard_[middle_row][middle_col + 1] = 0;
            // 0
            this->SolveImpl(k - 1, start_row_0, start_col_0,
                            start_row_0 + half_row - 1,
                            start_col_0 + half_col - 1);
            // 1
            this->SolveImpl(k - 1, start_row_1, start_col_1, banned_row,
                            banned_col);
            // 2
            this->SolveImpl(k - 1, start_row_2, start_col_2, start_row_2,
                            start_col_2 + half_col - 1);
            // 3
            this->SolveImpl(k - 1, start_row_3, start_col_3, start_row_3,
                            start_col_3);
            break;
        }

        case 2: {
            // this->chessboard_[middle_row + 1][middle_col] = 0;
            // 0
            this->SolveImpl(k - 1, start_row_0, start_col_0,
                            start_row_0 + half_row - 1,
                            start_col_0 + half_col - 1);
            // 1
            this->SolveImpl(k - 1, start_row_1, start_col_1,
                            start_row_1 + half_row - 1, start_col_1);
            // 2
            this->SolveImpl(k - 1, start_row_2, start_col_2, banned_row,
                            banned_col);
            // 3
            this->SolveImpl(k - 1, start_row_3, start_col_3, start_row_3,
                            start_col_3);
            break;
        }

        case 3: {
            // this->chessboard_[middle_row + 1][middle_col + 1] = 0;
            // 0
            this->SolveImpl(k - 1, start_row_0, start_col_0,
                            start_row_0 + half_row - 1,
                            start_col_0 + half_col - 1);
            // 1
            this->SolveImpl(k - 1, start_row_1, start_col_1,
                            start_row_1 + half_row - 1, start_col_1);
            // 2
            this->SolveImpl(k - 1, start_row_2, start_col_2, start_row_2,
                            start_col_2 + half_col - 1);
            // 3
            this->SolveImpl(k - 1, start_row_3, start_col_3, banned_row,
                            banned_col);
            break;
        }
        }
    }

    void Solve() {

        // 我们要把问题分解成四个小的问题

        // 2^k -> 2^(k-1)
        // 还是有一个问题，我们需要在整个二维数组中定位
        // 这不像在一维数组中那样简单

        this->SolveImpl(this->k_, 0, 0, this->black_row_, this->black_col_);
    }

    void PrintSolution() {
        // 我们就是把棋盘输出一下就行了
        for (int r = 0; r < this->max_row_; r++) {
            for (int c = 0; c < this->max_col_; c++) {
                std::cout << this->chessboard_[r][c] << " ";
            }
            std::cout << "\n";
        }
    }

  private:
    int k_;
    int max_row_;
    int max_col_;
    int black_row_;
    int black_col_;
    int chessboard_[maxk][maxk];
};

int main() {

    // 最方便的测试方法就是读取知道读取结束，这样不用每次添加测试用例都得修改需要读取的测试数量

    int k = 0;
    while (std::cin >> k) {
        if (k == 0) {
            break;
        }

        int banned_row = 0;
        int banned_col = 0;
        std::cin >> banned_row >> banned_col;
        ChessboardCoverage cc{k, banned_row, banned_col};
        cc.Solve();
        cc.PrintSolution();
    }
}