// 2025/4/1
// zhangzhong

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

// 咱们用最简单的方法，直接用一个二维数组来模拟一张表格
// 因为题目中给出了表格的最大的范围
// 然后我们直接模型所有的插入删除动作
// 无非就是把表格的内容复制过来复制过去的

// Data in spreadsheets are stored in cells, which are organized in rows (r) and
// columns (c)

// DL 1 3 就是直接删除对应的行或者列
// INSERT 1 3是在对应的行或列的左边或者上边加上新的行或列

// 一共有五种命令
// 咱们每种命令就直接实现一个函数就行了

// 一个cell是有一个坐标的
// Row and column labeling begins with 1
// The maximum number of rows or columns of each spreadsheet is limited to 50
const int MAX_ROWS = 51;
const int MAX_COLS = 51;

struct Cell {
    int row;
    int col;

    Cell() : row(0), col(0) {}
    Cell(int row, int col) : row(row), col(col) {}

    std::string ToString() const {
        return "(" + std::to_string(this->row) + "," +
               std::to_string(this->col) + ")";
    }

    bool operator==(const Cell& other) const noexcept {
        return this->row == other.row && this->col == other.col;
    }
};

class RangeWithDeletation {

  public:
    // 还是左开右闭的原则吧
    RangeWithDeletation(int start, int stop, const std::vector<int>& dels)
        : _stop(stop), _curr(start - 1), _dels(dels) {}

    int Next() {
        ++this->_curr;
        while (this->_curr < _stop) {
            auto iter =
                std::find(this->_dels.begin(), this->_dels.end(), this->_curr);
            if (iter == this->_dels.end()) {
                // 没有被删除，直接返回吧
                return this->_curr;
            } else {
                // 这个点被删除了，需要递归迭代下一个
                ++this->_curr;
            }
        }
        // 到这里说明 curr == stop
        return this->End();
    }

    int End() { return this->_stop; }

  private:
    int _stop;
    int _curr;
    const std::vector<int>& _dels;
};

class Spreadsheet {
  public:
    // 咱们为了方便 直接给所有的Cell都初始化成默认值
    Spreadsheet(int row_count, int col_count)
        : _row_count(row_count), _col_count(col_count) {
        this->ResetCells();
    }

    int GetRowCount() const noexcept { return this->_row_count; }
    int GetColCount() const noexcept { return this->_col_count; }

    void Print() {
        for (int row = 1; row <= this->_row_count; row++) {
            for (int col = 1; col <= this->_col_count; col++) {
                std::cout << this->_cells[row][col].ToString() << " ";
            }
            std::cout << std::endl;
        }
    }

    void Exchange(const Cell& c1, const Cell& c2) {
        std::swap(this->_cells[c1.row][c1.col], this->_cells[c2.row][c2.col]);
    }

    // 在输入中保证了cols一定不是空的
    void DeleteColumns(const std::vector<int>& cols) {
        // 一次性删除，整体只需要复制一次，效率会高一些，但是实现起来就复杂一些
        // std::sort(cols.begin(), cols.end());

        // 索引都是从1开始的，咱们的MAX = 50 + 1 合理
        // 所以0咱就不用了
        int min_col = *std::min_element(cols.begin(), cols.end());

        RangeWithDeletation range{min_col + 1, this->_col_count + 1, cols};

        // min_col 就是要开始复制的列
        // !!! 还有一点要非常注意，就是col和col count的比较都是小于等于
        // 因为索引从1开始
        for (int col = min_col; col <= this->_col_count; col++) {
            // 而且一定是一列一列的进行复制
            // 只不过需要复制的列，是不连续的
            int from_col = range.Next();
            if (from_col >= range.End()) {
                break;
            }

            // 实现一个Move Column的函数
            // 方便这里的实现
            // 我们也像parser 那样，对于这样复杂的迭代器，写一个单独的类会好一些
            this->MoveColumn(from_col, col);
        }

        this->_col_count -= cols.size();
    }

    void DeleteRows(const std::vector<int>& rows) {
        // 这个的实现逻辑和delete rows是一样的
        // 只不过从col换成了row
        // std::sort(rows.begin(), rows.end());
        int min_row = *std::min_element(rows.begin(), rows.end());

        RangeWithDeletation range{min_row + 1, this->_row_count + 1, rows};
        for (int to_row = min_row; to_row <= this->_row_count; to_row++) {
            int from_row = range.Next();
            if (from_row >= range.End()) {
                break;
            }

            this->MoveRow(from_row, to_row);
        }

        this->_row_count -= rows.size();
    }

    void FillEnoughRows(const std::vector<int>& rows) {
        // 卧槽，巨坑！C++的max和min和python不一样
        // 他只能求两个值的最值，你给一个序列，他就会返回指针的大小
        // 怪不得一会大一会小呢。。。
        // 服了
        int max_row = *std::max_element(rows.begin(), rows.end());
        // int max_row = *std::max(rows.begin(), rows.end());
        if (max_row <= this->_row_count) {
            return;
        }

        // 否则我们需要从 this->_row_count + 1 -> max_row
        // 填充空的行
        for (int row = this->_row_count + 1; row <= max_row; row++) {
            this->ResetRow(row);
        }
        this->_row_count = max_row;
    }

    void FillEnoughCols(const std::vector<int>& cols) {
        int max_col = *std::max_element(cols.begin(), cols.end());
        if (max_col <= this->_col_count) {
            return;
        }
        for (int col = this->_col_count + 1; col <= max_col; col++) {
            this->ResetColumn(col);
        }
        this->_col_count = max_col;
    }

    void InsertBeforeColumns(const std::vector<int>& cols) {
        // insert和delete的方向相反
        // 我们需要从表的最右边开始复制
        // 然后开始复制的地方也不在是最小的被删除的位置
        // 而是最大的应该被复制的位置

        // 这里增加一个函数，处理可能不存在的列
        this->FillEnoughCols(cols);

        // std::sort(cols.begin(), cols.end());
        int min_col = *std::min_element(cols.begin(), cols.end());

        // from_col: this->_col_count -> min_col
        // to_col: this->_col_count + cls.size() ->

        int to_col = this->_col_count + cols.size();
        // 所以最开始需要复制到的位置是 this->_col_count
        for (int from_col = this->_col_count; from_col >= min_col; from_col--) {
            // from col从哪里开始？
            // 应该从之前的表格的最右边开始
            // from_col = this->_col_count ->
            this->MoveColumn(from_col, to_col);
            to_col--;
            if (std::find(cols.begin(), cols.end(), from_col) != cols.end()) {
                // 这是一个需要在之前插入空列
                // 我们需要一个函数，将某列置空
                this->ResetColumn(to_col);
                to_col--;
            }
        }

        this->_col_count += cols.size();
    }

    void InsertBeforeRows(const std::vector<int>& rows) {

        this->FillEnoughRows(rows);

        int min_row = *std::min_element(rows.begin(), rows.end());

        int to_row = this->_row_count + rows.size();
        for (int from_row = this->_row_count; from_row >= min_row; from_row--) {
            this->MoveRow(from_row, to_row);
            to_row--;

            if (std::find(rows.begin(), rows.end(), from_row) != rows.end()) {
                this->ResetRow(to_row);
                to_row--;
            }
        }

        this->_row_count += rows.size();
    }

    Cell Query(const Cell& cell) {

        // 我们只需要遍历匹配就行了

        for (int row = 1; row <= this->_row_count; row++) {
            for (int col = 1; col <= this->_col_count; col++) {
                if (this->_cells[row][col] == cell) {
                    return Cell{row, col};
                }
            }
        }

        return Cell{0, 0};
    }

  private:
    void ResetCells() {
        for (int row = 1; row < MAX_ROWS; row++) {
            for (int col = 1; col < MAX_COLS; col++) {
                this->_cells[row][col] = Cell{row, col};
            }
        }
    }

    void MoveColumn(int from_col, int to_col) {
        for (int row = 1; row <= this->_row_count; row++) {
            this->_cells[row][to_col] = this->_cells[row][from_col];
        }
    }

    void MoveRow(int from_row, int to_row) {
        for (int col = 1; col <= this->_col_count; col++) {
            this->_cells[to_row][col] = this->_cells[from_row][col];
        }
    }

    void ResetColumn(int col) {
        for (int row = 1; row <= this->_row_count; row++) {
            this->_cells[row][col] = Cell{};
        }
    }

    void ResetRow(int row) {
        for (int col = 1; col <= this->_col_count; col++) {
            this->_cells[row][col] = Cell{};
        }
    }

  private:
    int _row_count;
    int _col_count;
    Cell _cells[MAX_ROWS][MAX_COLS];
};

int main(int argc, char* argv[]) {
    // input
    // The input consists of a sequence of spreadsheets,
    // operations on those spreadsheets,
    // and queries about them.
    // 包括三部分

    // 1. each spreadsheet definition begins with a pair of integers specifying
    // its initial number of rows(r) and columns (c),
    int rows = 0;
    int cols = 0;
    for (int kase = 1; std::cin >> rows >> cols; kase++) {

        // The end of input is indicated by a row consisting of a pair of zeros
        // for
        // the spreadsheet dimensions.
        if (rows == 0 && cols == 0) {
            break;
        }

        // Separate output from different spreadsheets with a blank line
        if (kase > 1) {
            std::cout << "\n";
        }

        Spreadsheet spreadsheet{rows, cols};
        // spreadsheet.Print();

        // 2. ollowed by an integer specifying the number (n) of spreadsheet
        // operations.
        int op_count = 0;
        std::cin >> op_count;
        // the following n lines specify the desired operations
        for (int i = 0; i < op_count; i++) {
            // 2.1 exchange
            // EX r1 c1 r2 c2
            std::string op;
            std::cin >> op;

            if (op == "EX") {
                Cell c1{};
                Cell c2{};
                std::cin >> c1.row >> c1.col >> c2.row >> c2.col;
                spreadsheet.Exchange(c1, c2);
            } else {
                // delete column
                // <command> A x1 x2 ...xA
                // <command> = DC DR IC IR
                // A positive integer < 10 正数 1..10
                // 这个A就是指定后面有多少个需要操作的label的
                //  x1 = row or col
                // labels to be delete or inserted before
                // labels之间顺序不重要；labels不会重复

                // 因为这里所有的op都是一样的，所以读取的逻辑是不做区分的

                int label_count = 0;
                std::cin >> label_count;

                // 卧槽，我懂了，他没有说输入的列是不是合法的
                // 我们需要检查，并且去掉非法的列
                // 。。。真实无语了
                // 如果用户输入不存在的行或者列，我们需要用空列填充到
                // 然后在执行相应的操作。。。服了呀，
                std::vector<int> labels;
                for (int i = 0; i < label_count; i++) {
                    // 但是问题来了，我们怎么知道现在读的是行还是列
                    // 只能做一个if判断了
                    int label;
                    std::cin >> label;
                    // if (op == "DC") {
                    //     if (label > spreadsheet.GetColCount()) {
                    //         continue;
                    //     }
                    // }
                    // if (op == "DR") {
                    //     if (label > spreadsheet.GetRowCount()) {
                    //         continue;
                    //     }
                    // }
                    // 但是删除操作真得去掉非法的列吧
                    labels.push_back(label);
                }

                if (labels.empty()) {
                    continue;
                }

                if (op == "DC") {
                    spreadsheet.DeleteColumns(labels);
                } else if (op == "DR") {
                    spreadsheet.DeleteRows(labels);
                } else if (op == "IC") {
                    spreadsheet.InsertBeforeColumns(labels);
                } else if (op == "IR") {
                    spreadsheet.InsertBeforeRows(labels);
                } else {
                    assert(false);
                }
            }

            // std::cout << op << "\n";
            // spreadsheet.Print();
        }

        // output:
        // For each spreadsheet, your program must output its sequence number
        // (starting at 1)
        std::cout << "Spreadsheet #" << kase << "\n";

        // 3. The operations are followed by an integer which is the number of
        // queries for the spreadsheet
        int query_count = 0;
        std::cin >> query_count;
        for (int _ = 0; _ < query_count; _++) {
            // in original spreadsheet, 这个original spreadsheet 应该指的就是
            // 在第一部分读取的那个表格吧
            // 所以我们的表格内部的内容应该就是cell，cell里面的内容就是当前的行和列
            // 然后新插入的行或列 我们使用一个空的cell Cell{0, 0} 来表示就行了
            Cell original_cell;
            std::cin >> original_cell.row >> original_cell.col;
            // For each query, your program must determine the current location
            // of the data
            // that was originally in cell (r,c)
            Cell cell = spreadsheet.Query(original_cell);

            // output
            // for each query, output original location
            // and final location or GONE
            if (cell.row == 0 && cell.col == 0) {
                std::cout << "Cell data in " << original_cell.ToString()
                          << " GONE\n";
            } else {
                std::cout << "Cell data in " << original_cell.ToString()
                          << " moved to " << cell.ToString() << "\n";
            }
        }
    }
}
