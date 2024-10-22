// 2024/10/22
// zhangzhong

// [[TIPS]] 对于没有提供完整输入输出示例的题目
// 可以自己构造一些最简单的例子，检查一些低级错误

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

std::unordered_map<char, int> hex_to_int{
    {'0', 0},  {'1', 1},  {'2', 2},  {'3', 3},  {'4', 4},  {'5', 5},
    {'6', 6},  {'7', 7},  {'8', 8},  {'9', 9},  {'a', 10}, {'b', 11},
    {'c', 12}, {'d', 13}, {'e', 14}, {'f', 15},
};

std::array<char, 6> to_char{'W', 'A', 'K', 'J', 'S', 'D'};

class HieroglyphParser {

  public:
    void Clear() {
        for (int r = 0; r < max_row; r++) {
            for (int c = 0; c < max_col; c++) {
                // std::fill this->image[r][c] = 0;
                this->buffer[r][c] = white;
                this->image[r][c] = white;
                this->label[r][c] = 0;
                this->white_label[r][c] = 0;
            }
        }

        this->cur_row = 0;
        this->cur_col = 0;
    }

    void SetRowAndCol(int row, int col) {
        this->cur_row = row;
        this->cur_col = col;
    }

    void ReadImage() {
        for (int r = 0; r < this->cur_row; r++) {
            std::string line;
            std::getline(std::cin, line);
            for (int i = 0; i < line.size(); i++) {
                int c = 4 * i;
                // 一共只有0 - f个字符
                // 打个表吧
                // 那么值的类型是什么呢
                // 最好是一个int型的数组
                // 这样刚好我们可以遍历来填充数组
                char ch = line[i];
                // hex to integer
                // 我记得cpp是有办法的
                // std::stringstream ssr;
                // ssr << std::ios::hex << ch;
                // unsigned int n = 0;
                // ssr >> n;
                // 最简单的方法就是直接打一个表 char -> int
                int n = hex_to_int[ch];

                // 把n的后四位转成int 一次赋值i = 0; i < 4; i++)
                for (int j = 3; j >= 0; j--) {
                    unsigned int bit = n & 1U;
                    n = n >> 1;
                    this->image[r][c + j] = bit;
                }
            }
        }
    }

    // 传递数组指针有点麻烦了
    void dfs(int row, int col, int id, int color, int* image, int* label) {

        // index check

        for (int r = row - 1; r <= row + 1; r++) {
            // 不行 必须在这里进行检查，否则我们直接访问时可能导致越界的
            if (r < 0 || r >= this->cur_row) {
                continue;
            }
            for (int c = col - 1; c <= col + 1; c++) {
                if (c < 0 || c >= this->cur_col) {
                    continue;
                }

                // 那么这里也不对了
                // 因为我们在特定的时候希望看buffer而不是image
                if (image[r * max_col + c] == color &&
                    label[r * max_col + c] == 0) {
                    // label[r][c] = id;
                    label[r * max_col + c] = id;
                    // 操了 这里忘了递归了。。。
                    dfs(r, c, id, color, image, label);
                }
            }
        }
    }

    // 我们需要跑两遍 flood算法 第一遍是找到所有的文字 然后对每个文字打上标签
    // 最终我们返回找到的文字数量，以及一个打上标签的数组
    // 显然这个数组也是需要保存的
    // 还有最后一个问题，就是这个label数组，我们在后序统计白色分量的时候时需要这个label的
    // 但是在统计黑色分量的时候也需要
    // 而且他们不能冲突
    // 所以这个label最好是从外部传入
    int LabelHieroglyphs() {
        int max_id = 0;

        for (int r = 0; r < this->cur_row; r++) {
            for (int c = 0; c < this->cur_col; c++) {
                // 然后对每个位置执行dfs搜索
                if (this->image[r][c] == black && this->label[r][c] == 0) {
                    max_id += 1;
                    dfs(r, c, max_id, black, (int*)this->image,
                        (int*)this->label);
                }
            }
        }

        return max_id;
    }

    int LabelWhite() {
        int max_id = 0;

        for (int r = 0; r < this->cur_row; r++) {
            for (int c = 0; c < this->cur_col; c++) {
                // 然后对每个位置执行dfs搜索
                // [[BUG]] 这里也错啦 应该是buffer才对呀 怎么image呢
                // 我们定义buffer不就是为了在label
                // white的时候用buffer而不是iamge吗
                if (this->buffer[r][c] == white &&
                    this->white_label[r][c] == 0) {
                    max_id += 1;
                    dfs(r, c, max_id, white, (int*)this->buffer,
                        (int*)this->white_label);
                }
            }
        }

        return max_id;
    }

    void CopyCharToBuffer(int id) {
        // clear buffer first
        // 因为我们会给文字加上一圈白色，所以当前的row和col就不对了
        // 以防万一，我们全部涂白
        for (int r = 0; r < max_row; r++) {
            for (int c = 0; c < max_col; c++) {
                this->buffer[r][c] = white;
            }
        }

        // 还有最后一种情况，就是当文字充满整个板子的时候
        // 文字可能把本来连在一起的白色给分开
        // 解决方法也非常简单，我们给文字的四周加上一圈白色就行
        // 同时在LabelWHite的时候也需要做适当的处理
        for (int r = 0; r < this->cur_row; r++) {
            for (int c = 0; c < this->cur_col; c++) {
                // [[BUG]] 这是不是image啊 是label啊
                if (this->label[r][c] == id) {
                    this->buffer[r + 1][c + 1] = black;
                }
            }
        }
    }

    void PrintImage() {
        for (int r = 0; r < this->cur_row; r++) {
            for (int c = 0; c < this->cur_col; c++) {
                std::cout << this->image[r][c] << " ";
            }
            std::cout << std::endl;
        }
    }

    void PrintLabel() {
        for (int r = 0; r < this->cur_row; r++) {
            for (int c = 0; c < this->cur_col; c++) {
                std::cout << this->label[r][c] << " ";
            }
            std::cout << std::endl;
        }
    }

    void PrintWhiteLabel() {
        for (int r = 0; r < this->cur_row; r++) {
            for (int c = 0; c < this->cur_col; c++) {
                std::cout << this->white_label[r][c] << " ";
            }
            std::cout << std::endl;
        }
    }

    void PrintBuffer() {
        for (int r = 0; r < this->cur_row; r++) {
            for (int c = 0; c < this->cur_col; c++) {
                std::cout << this->buffer[r][c] << " ";
            }
            std::cout << std::endl;
        }
    }

    std::string GetString(int max_id) {

        // auto str = std::set<char>{};
        auto str = std::vector<char>{};

        for (int id = 1; id <= max_id; id++) {
            // copy the character of id to the bubffer
            this->CopyCharToBuffer(id);

            // now calcuate the white 联通分量 on the buffer
            // clear white label first
            for (int r = 0; r < max_row; r++) {
                for (int c = 0; c < max_col; c++) {
                    this->white_label[r][c] = 0;
                }
            }
            // label white
            // 因为我们前后都加了两行
            this->cur_row += 2;
            this->cur_col += 2;
            int white_count = this->LabelWhite() - 1;
            // 然后再复原
            this->cur_row -= 2;
            this->cur_col -= 2;

            if (white_count < 0 || white_count >= 6) {
                str.push_back('O');
            } else {
                // 太傻逼了，set是会去重的呀！！！
                // 要不就用一个vector最后排个序好了
                // 或者用multiset
                str.push_back(to_char[white_count]);
            }
        }

        std::sort(str.begin(), str.end());
        return std::string{str.begin(), str.end()};
    }

  private:
    static const int max_row = 256;
    static const int max_col = 256;
    static const int black = 1;
    static const int white = 0;

    // two std::array is not contiguous in memory
    // if you want to use it, you should manaully construct index yourself
    // which is not good
    // std::array<std::array<int, max_col>, max_row> a;
    int image[max_row][max_col];
    int buffer[max_row][max_col];
    int label[max_row][max_col];
    int white_label[max_row][max_col];

    // [[BUG]]
    // 卧槽！！重大BUG
    // 题目中的col和实际上的索引是差4被的
    // 我们所有的函数都写错了！！！TMD
    // 全错了反而好改，我们在set col的时候 * 4就ok了
    int cur_row = 0;
    int cur_col = 0;
};

int main() {

    HieroglyphParser parser = HieroglyphParser{};
    // not used function is optimised out
    // so I could not call it in lldb
    // so I call it in this
    parser.PrintBuffer();
    parser.PrintImage();
    parser.PrintLabel();
    parser.PrintWhiteLabel();

    int row = 0;
    int col = 0;

    for (int case_count = 1;; case_count++) {
        std::cin >> row >> col;
        if (row == 0 || col == 0) {
            break;
        }

        // get the empty line
        std::string line;
        std::getline(std::cin, line);

        // read the whole imagesk
        parser.Clear();
        parser.SetRowAndCol(row, 4 * col);

        parser.ReadImage();

        int char_count = parser.LabelHieroglyphs();

        // for each character, copy it to the buffer
        // and calculate the white 联通分量
        // 根据联通分量的数量
        // 1 -> W
        // 2 -> A
        // 3 -> K
        // 4 -> J
        // 5 -> S
        // 6 -> D
        std::cout << "Case " << case_count << ": "
                  << parser.GetString(char_count) << std::endl;
    }
}
