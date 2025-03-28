// 2025/3/28
// zhangzhong
// 二叉树可以表示 表达式树
// example： a+b*(c-d)-e/f
// 其中每个非叶子节点表示一个操作符，叶子节点表示操作数
// 求值也非常简单，只需要一个符号表，将符号映射成数字，然后从根节点开始求值即可

// 我们确实可以变成表达式树
// 但是我们要怎么测试呢？
// 比较好的方法是测试的结果就是表达式的值
// 那这样输入就是
// 首先是符号的数量 n, 0 表示结束
// 然后是符号表 a 10
// 然后是一个表达式，这个表达式是一个字符串，是没有空格的，因为我们的识别算法也是比较特殊的，
// 无法处理空格和换行，可能经过改造可以支持空格和换行，不过我这里就不考虑了
// 而且符号也只能使用一个小写字母，运算符只支持 + - * / ()
// ok

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>

using SymbolTable = std::unordered_map<char, double>;
using node_t = int;

class ExpressionTree {

  public:
    ExpressionTree(const std::string& expression) : _expression(expression) {
        std::fill(left_childs.begin(), left_childs.end(), -1);
        std::fill(right_childs.begin(), right_childs.end(), -1);
        std::fill(nodes.begin(), nodes.end(), '\0');

        this->_root = this->_ConstructExpressionTree(expression, 0,
                                                     expression.size() - 1);
    }

    double Eval(const SymbolTable& symbol_table) const {
        return this->_EvalImpl(this->_root, symbol_table);
    }

    void Print() const {
        for (int i = 0; i <= this->current_node; i++) {
            // 输出这个节点的op 左节点和右节点
            std::cout << this->nodes[i] << ": " << this->left_childs[i] << " "
                      << this->right_childs[i] << std::endl;
        }
    }

  private:
    double _EvalImpl(const node_t root, const SymbolTable& symbol_table) const {
        // 检查本节点是操作符还是字母
        if (symbol_table.find(this->nodes[root]) == symbol_table.end()) {
            // 是操作符
            switch (this->nodes[root]) {
            case '+':
                return this->_EvalImpl(this->left_childs[root], symbol_table) +
                       this->_EvalImpl(this->right_childs[root], symbol_table);
            case '-':
                return this->_EvalImpl(this->left_childs[root], symbol_table) -
                       this->_EvalImpl(this->right_childs[root], symbol_table);
            case '*':
                return this->_EvalImpl(this->left_childs[root], symbol_table) *
                       this->_EvalImpl(this->right_childs[root], symbol_table);
            case '/':
                return this->_EvalImpl(this->left_childs[root], symbol_table) /
                       this->_EvalImpl(this->right_childs[root], symbol_table);
            default:
                assert(false);
            }
        } else {
            // 是字母，直接查表返回值就行了
            const char symbol = this->nodes[root];
            return symbol_table.at(symbol);
        }
    }

    node_t _ConstructExpressionTree(const std::string& expression,
                                    const int left, const int right) {

        // 递归结束条件
        if (left > right) {
            return -1;
        }

        // 怎么保存这棵树呢
        // 比较传统的方法是使用节点来保存
        // 但是这种的性能一般都不如直接使用数组来保存的性能好？
        // 但是直接用节点表示，实现起来比较清晰
        // 为了和书上一样，这里也使用数组来保存树吧

        // 使用一个区间表示目前正在处理的范围 [left, right] 左闭右闭

        // 简单的说，就是从左向右扫描当前的字符串
        // 找到应该最后被计算的符号
        // 创建一个新的节点,
        // 然后递归的处理左侧的字符串和右侧的字符串，然后挂在这个新的节点的左右两侧
        // 就ok了
        // 虽然 + - * / 都是左结合性的，但是拥有结合律，先算左边的还是先算右边的
        // 都是一样的

        // 我们需要两个变量来记录找到的最右边的运算符
        int rightmost_mul_div_op_index = -1;
        int rightmost_add_sub_op_index = -1;
        int bracket_stack = 0;
        for (int i = left; i <= right; i++) {
            switch (expression[i]) {
            case '+':
            case '-': {
                if (bracket_stack == 0) {
                    rightmost_add_sub_op_index = i;
                }
                break;
            }

            case '*':
            case '/': {
                if (bracket_stack == 0) {
                    rightmost_mul_div_op_index = i;
                }
                break;
            }

            // 使用一个变量表示括号的栈
            // 只有当栈是空的，我们才记录符号，因为括号内的符号肯定不是最后计算的
            case '(': {
                bracket_stack++;
                break;
            }
            case ')': {
                bracket_stack--;
                break;
            }

            default: {

                //
                break;
            }
            }
        }

        // 最终我们找到了两个符号
        // 最后计算的肯定是加减，只要它存在
        int rightmost_op_index = rightmost_mul_div_op_index;
        if (rightmost_add_sub_op_index != -1) {
            rightmost_op_index = rightmost_add_sub_op_index;
        }

        // 如果我们没有找到合适的符号
        // 只有一种可能，整个表达式被一个括号括起来了
        // 或者是空的
        if (rightmost_op_index == -1) {
            // 但是返回值给谁呢？
            // 应该是直接返回
            // （）不需要创建新的节点
            // 这里有两种可能，一种是
            // left == right
            // 那么这就只有一个结点
            // 我们创建这个叶子节点返回就行了
            if (left == right) {
                int curr_node = ++this->current_node;
                this->nodes[curr_node] = expression[left];
                return curr_node;
            }
            return this->_ConstructExpressionTree(expression, left + 1,
                                                  right - 1);
        }

        // 此时需要创建一个新的节点
        int curr_node = ++this->current_node;
        this->nodes[curr_node] = expression[rightmost_op_index];
        this->left_childs[curr_node] = this->_ConstructExpressionTree(
            expression, left, rightmost_op_index - 1);
        this->right_childs[curr_node] = this->_ConstructExpressionTree(
            expression, rightmost_op_index + 1, right);
        return curr_node;
    }

  private:
    static constexpr int max_node_count = 1024;
    int current_node = -1;
    node_t _root = -1;
    std::array<node_t, max_node_count> left_childs{-1};
    std::array<node_t, max_node_count> right_childs{-1};
    std::array<char, max_node_count> nodes{'\0'};
    std::string _expression;
};

int main(int argc, char* argv[]) {
    int symbol_count = 0;

    while (std::cin >> symbol_count) {
        if (symbol_count == 0) {
            break;
        }

        // read in the symbol table
        // just use a map
        SymbolTable symbol_table;
        for (int i = 0; i < symbol_count; i++) {
            char symbol = 0;
            double value = 0;
            std::cin >> symbol >> value;
            symbol_table[symbol] = value;
        }

        // read in the expression
        std::string expression;
        std::getline(std::cin, expression); // read in the useless newline
        std::getline(std::cin, expression);

        // 首先我们要解析这个表达式，把它变成表达式树
        ExpressionTree expr_tree(expression);

        // expr_tree.Print();

        // 然后对表达式树求值
        double answer = expr_tree.Eval(symbol_table);
        std::cout << answer << std::endl;
    }
}
