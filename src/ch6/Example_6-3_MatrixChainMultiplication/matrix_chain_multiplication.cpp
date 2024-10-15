// 2024/10/15
// zhangzhong

#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

struct Matrix {
    int row;
    int col;
};

static int temp_variable_id = 0;

int eval_parentheses(std::unordered_map<std::string, Matrix>& symbol_table,
                     std::stack<std::string>& expr_stack) {

    // pop two symbols and calculate it
    // 不对 我们这里是有可能pop不出来的 这个表达式不一定是正确构造的
    if (expr_stack.empty()) {
        return -1;
    }
    auto right = expr_stack.top();
    expr_stack.pop();

    if (expr_stack.empty()) {
        return -1;
    }
    auto left = expr_stack.top();
    expr_stack.pop();

    // 拿到两个符号之后，前一个符合也必须是(
    if (expr_stack.empty()) {
        return -1;
    }
    if (expr_stack.top() != "(") {
        return -1;
    }
    expr_stack.pop();

    // 然后查看两个矩阵是否可以相乘
    // 根据两个符号到符号表中进行查表
    auto left_matrix = symbol_table.find(left);
    if (left_matrix == symbol_table.end()) {
        return -1;
    }
    auto right_matrix = symbol_table.find(right);
    if (right_matrix == symbol_table.end()) {
        return -1;
    }

    if (left_matrix->second.col != right_matrix->second.row) {
        return -1;
    }

    auto multiplications = left_matrix->second.row * left_matrix->second.col *
                           right_matrix->second.col;
    auto temp = Matrix{left_matrix->second.row, right_matrix->second.col};
    // insert this new temp variable back to symbol table
    // but only in the temp symbol
    // 有一个非常简单的方法，我们把参数提供的符号表复制一下，这样查找起来就简单了
    // 而且每个表达式求值结束之后就会自动销毁
    // 而且也不会影响传入的参数，这样实现最简单
    // 这些个表达式可能非常长，所以只用一个char作为key其实非常的不保险，所以我们还是用string作为key把
    temp_variable_id++;
    symbol_table.insert({std::to_string(temp_variable_id), temp});
    expr_stack.push(std::to_string(temp_variable_id));
    return multiplications;
}

int eval(const std::string& expr,
         const std::unordered_map<std::string, Matrix>& symbol_table) {

    int multiplications = 0;
    auto expr_stack = std::stack<std::string>{};
    auto local_symbol_table = symbol_table;

    // 应该又一些边界情况没有考虑调
    // 比如 只有一个矩阵，最后剩下两个矩阵等情况
    // 实际上是对的，因为不会出现剩下两个矩阵的情况，ebnf规定了的
    // 如果只有一个矩阵，这个循环就不会做什么计算，最后的结果是零 也是对的
    for (const auto& ch : expr) {
        if (ch != ')') {
            expr_stack.push(std::string{ch});
            continue;
        }

        int r = eval_parentheses(local_symbol_table, expr_stack);
        if (r == -1) {
            return -1;
        }
        multiplications += r;
    }

    return multiplications;
}

int main() {

    int expr_count = 0;
    std::cin >> expr_count;

    auto symbol_table = std::unordered_map<std::string, Matrix>{};

    std::string symbol;
    int row = 0;
    int col = 0;
    for (int i = 0; i < expr_count; i++) {
        std::cin >> symbol >> row >> col;
        // create a matrix
        auto matrix = Matrix{row, col};
        symbol_table.insert({symbol, matrix});
    }

    // start read expr
    std::string expr;
    while (std::cin >> expr) {
        int result = eval(expr, symbol_table);
        if (result == -1) {
            std::cout << "error\n";
        } else {
            std::cout << result << "\n";
        }
    }
}