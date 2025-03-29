// 2025/3/28
// zhangzhong
//

#include <cassert>
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include <map>

// 我们当前的版本应该是对的，只不过我们是在某个节点创建完成之后才分配节点，这样实现应该是更简单的
// 但是按照题目的要求，应该是在第一次碰到这个节点的时候就为其分配节点
// 咱们copy一份代码，试着实现一下

// 咱们的程序是对的 但是超时了。。。

using node_t = int;

struct ExpressionNode {
    std::string op;
    node_t left;
    node_t right;

    ExpressionNode(const std::string& op, node_t left, node_t right)
        : op(op), left(left), right(right) {}

    ExpressionNode() : op(), left(0), right(0) {}

    bool operator==(const ExpressionNode& other) const noexcept {
        return this->op == other.op && this->left == other.left &&
               this->right == other.right;
    }
};

// 然后ExpressionNode要支持hash操作

namespace std {
template <> struct hash<ExpressionNode> {
    size_t operator()(const ExpressionNode& self) const noexcept {
        return hash<std::string>{}(self.op) ^ hash<node_t>{}(self.left) ^
               hash<node_t>{}(self.right);
    }
};
}; // namespace std
static constexpr int max_node_count = 60000;

std::vector<ExpressionNode> _nodes(max_node_count);
std::vector<bool> done(max_node_count);

class ExpressionTree {
  public:
    ExpressionTree(const std::string& expression) : _expression(expression) {

        // std::fill(_is_visited.begin(), _is_visited.end(), false);

        // 0号节点是一个空的节点，我们push一个空的进去
        // _nodes.push_back(ExpressionNode{", 0, 0"});
        // _is_visited.push_back(true);
        // ok，现在我们的表达式的样子是对了，但是节点的顺序不对，说实话，我实在是不知道她的节点的顺序是指的什么。。。
        auto result = this->BuildExpressionTree(expression, 0);
        // assert(result.second == expression.size());
        this->_root = result.first;

        // 有一个bug，就是我们没有memset整个_is_visited 数组
        // 不过这样为什么结果也是正确的呢？
        // 哦，不对，我们在下面创建节点的时候设置了，所以结果是对的
    }

    // 我们需要一个什么？
    // 我们构造结束之后，就可以创建一个表达式树
    // 然后我们需要从root节点开始，把这个DAG给表示出来
    // 这也意味着，我们需要反向查找
    // 应该是没有办法一趟写出来最终的字符串的，还是得先把整棵树给构建出来
    // 然后再进行一个遍历 才能写出来
    std::string GetSimplestExpression() {

        // 构建这棵树的过程应该也是递归的

        return this->BuildStringTree(this->_root);
    }

  private:
    std::string BuildStringTree(node_t root) {

        if (done[root]) {
            // 因为我们的构建顺序应该和出现的顺序是反过来的
            // 所以我们可以改成总的节点数量减去root的序号
            return std::to_string(root);
        }

        done[root] = true;

        // 我们找到root，就可以找到她的节点
        ExpressionNode node = _nodes[root];
        // 当然了，如果是叶子节点 就是递归的结束条件
        if (node.left == 0 && node.right == 0) {
            // 每个节点只有第一次的时候才会返回它自己的字符串形式
            // 否则只返回它的int类型
            // 这里就是ToString

            // 但是我们怎么知道某个节点是不是第一个被展示呢？
            // 就需要一个额外的数组
            return node.op;
        }

        // 然后就可以找到左右子树
        // node.left, node.right
        // 然后递归的构造啊
        return node.op + "(" + this->BuildStringTree(node.left) + "," +
               this->BuildStringTree(node.right) + ")";
    }

    // node_t CreateNode(const std::string& op, node_t left, node_t right) {
    //     // 构建一个ExpressionNode
    //     const ExpressionNode node{op, left, right};
    //     // 然后在map中寻找
    //     auto it = this->_trees.find(node);
    //     if (it == this->_trees.end()) {
    //         // 没有找到，那么就插入这个node，
    //         node_t curr_node = ++this->_curr_node;
    //         this->_trees.insert({node, curr_node});
    //         _nodes.push_back(node);
    //         _is_visited.push_back(false);
    //         return curr_node;
    //     } else {
    //         //
    //         相反，如果这个节点已经存在，那么我们就不需要在建立一个新的节点，直接返回一个旧的已经存在的几点就行了
    //         return it->second;
    //     }
    // }

    std::pair<node_t, bool> TryCreateNode(const std::string& op, node_t left,
                                          node_t right, node_t node_id) {
        // 构建一个ExpressionNode
        ExpressionNode node{op, left, right};
        // 然后在map中寻找
        auto it = this->dict.find(node);
        if (it == this->dict.end()) {
            // 没有找到，那么就插入这个node，
            node_t curr_node = node_id;
            this->dict.insert({node, curr_node});
            // BUG!
            // 这里的push back是不对的，只能直接插入
            // 所以需要保证数组足够长
            // _nodes.push_back(node);
            // _is_visited.push_back(false);
            _nodes[node_id] = node;
            done[node_id] = false;
            return {curr_node, true};
        } else {
            // 相反，如果这个节点已经存在，那么我们就不需要在建立一个新的节点，直接返回一个旧的已经存在的几点就行了
            return {it->second, false};
        }
    }

    std::pair<int, int> BuildExpressionTree(const std::string& expression,
                                            const int left) {

        // 首先我们要解析这棵树
        // 判断这棵树是一个叶子节点还是中间节点

        // 如果是叶子节点 一定包含括号 op(x,y)
        // 如果没有括号，就是叶子节点了

        // 咱们可以写一个函数，专门用来解析这个字符串
        // 并且拆解出四个部分
        // operator
        // op1
        // op2
        // 并且分别给出 字串的位置
        // operator = [left, right]
        // op1 = [op1_left, op1_right]
        // 如果没有发现，那么就直接

        // 而且是不是叶子节点的处理是不一样的
        // 所以还是额外处理吧
        // 这个不仅处理了叶子节点，还是递归的结束条件

        // 因为没有了右侧，什么时候结束就成了个问题
        // if (expression.substr(left, right - left + 1).find('(') ==
        //     std::string::npos) {
        //     // 叶子节点
        //     // 立即为其分配一个节点
        //     //
        //     node_t curr_node = ++this->_curr_node;
        //     auto result = this->TryCreateNode(
        //         expression.substr(left, right - left + 1), 0, 0, curr_node);
        //     if (!result.second) {
        //         this->_curr_node = curr_node - 1;
        //     }
        //     return result.first;
        // }

        // int op_left = -1;
        // int op_right = -1;
        // int op1_left = -1;
        // int op1_right = -1;
        // int op2_left = -1;
        // int op2_right = -1;

        // op_left = left;
        // int bracket_depth = 0;
        // 我知道了，还有一个改进的点！
        // 就是这里不是每次都找到遍历全部的串，找到需要构建的地方在去构建
        // 而是直接在串上进行构建！
        // 这样应该就可以大幅的缩短这里的遍历的次数！
        // for (int i = left; i <= right; i++) {
        //     // 下面这个只能处理非叶子节点
        //     // 如果想要处理叶子节点
        //     switch (expression[i]) {
        //         // 还没有这么简单，因为我们会遇到很多层的括号
        //         //
        //     case '(': {
        //         // 进入操作符模式
        //         bracket_depth++;

        //         // 只有第一个括号开始的时候，才开始记录第一个操作数
        //         if (bracket_depth == 1) {
        //             op_right = i - 1;
        //             op1_left = i + 1;
        //         }
        //         break;
        //     }

        //     case ')': {
        //         if (bracket_depth == 1) {
        //             op2_right = i - 1;
        //         }

        //         // 退出操作符模式
        //         bracket_depth--;
        //         // 只有当当前的括号是1的时候，才是操作数的结束

        //         break;
        //     }

        //     case ',': {
        //         // 切换操作数
        //         // 只有当只有一层括号的时候，才切换操作数
        //         if (bracket_depth == 1) {
        //             // 记录第一个操作数
        //             op1_right = i - 1;
        //             // 开始记录下一个操作数
        //             op2_left = i + 1;
        //         }
        //     }
        //     }
        // }

        // 最终我们一定可以找到所有的操作数
        // 也就是所有的op left right 都不能是-1
        // assert(op_left != -1);
        // assert(op_right != -1);
        // assert(op1_left != -1);
        // assert(op1_right != -1);
        // assert(op2_left != -1);
        // assert(op2_right != -1);

        // 哎，不对呀，我们这里如果返回的不是node_t
        // 就是这棵子树的字符串，是不是一趟就可以写出来了？
        // 感觉还是不太行。

        // 在最开始就要创建节点
        node_t curr_node = ++this->_curr_node;
        // 那这里就和solution里面一样了
        // 一开始设置一个初始值
        // 然后op的收集部分也是一样的
        int left_tree = 0;
        int right_tree = 0;

        // 我们立即为当前的节点分配一个新的节点

        // 我们首先找到第一个(
        // 其实是不是叶子，就看这里第一个碰到的是不是括号
        // 因为每个符号一定在四个符号以内
        // 我们不能直接找 我们可能碰到的特殊符号有 , ( ) END
        // 只要不是碰到 ( 就说明是叶子节点
        // bool is_leaf = true;
        // op_left = left;
        // op_right = -1;
        // bool found_delimiter = false;
        // for (int i = 0;
        //      !found_delimiter && i < 5 && (left + i) < expression.size();
        //      i++) {
        //     switch (expression[left + i]) {
        //     case '(': {
        //         is_leaf = false;
        //         op_right = left + i - 1;
        //         // 卧槽，这里TMD的应该跳出这个循环，而不是跳出这个switch！
        //         found_delimiter = true;
        //         break;
        //     }
        //     case ',':
        //     case ')': {
        //         // is leaf
        //         found_delimiter = true;
        //         op_right = left + i - 1;
        //         break;
        //     }
        //     }
        // }

        std::string op;

        // 咱们按照答案的语义来写
        int p = left;
        for (; std::isalpha(expression[p]); p++) {
            op.push_back(expression[p]);
        }

        // i 不是一个字母 可能是 ( , )
        // 也可能是 \0
        // if (expression[i] == '(') { // f(x, y)

        // } else {
        //     // leaf
        // }

        // is_leaf = (expression[i] != '(');
        // op_right = i - 1;

        // 现在的逻辑可以handle这一部分了
        // if (is_leaf) {
        //     // 卧槽，我们也可能只有一个字符啊
        //     // 这里真正想要判断的是 op_right
        //     if (op_right == -1) {
        //         op_right = expression.size() - 1;
        //     }
        //     // 叶子节点
        //     // 立即为其分配一个节点
        //     //
        // }

        // int curr_node = ++this->_curr_node;
        // op_right = expression.find_first_of('(', left) - 1;

        if (expression[p] == '(') {
            // assert(expression[p] == '(');
            // 然后就可以构建左子树了

            // 但是我们的节点可能是失败的，我们需要知道我们的节点是不是重复
            // 如果是的话，需要去掉
            p++;
            // 然后咱们只需要递归的创建子表达式就行了
            auto result = this->BuildExpressionTree(expression, p);
            left_tree = result.first;
            p = result.second;

            // 哎不行啊，我们的BuildExpressionTree这样就不能有right了，否则就不会自动的去读取串了
            // 我们不仅不能含有right，还得让这个函数返回right

            // 然后接下来一定是一个逗号
            assert(expression[p] == ',');

            p++;
            result = this->BuildExpressionTree(expression, p);
            right_tree = result.first;
            p = result.second;
            // 这里的测试是不对的
            // 这里可能
            assert(expression[p] == ')');
            // 最后处理完这个操作符之后，要跳到下一个位置，开启下一个的解析
            p++;
        }

        // 不管是不是叶子节点，都应该创建节点
        // 不同的就是，他们的左子树叶右子树是不是0 可以设置一个默认值啊

        // 可以看到，下面创建节点的部分是一样的，唯一不同的就是，返回的位置不一样
        // auto result = this->TryCreateNode(
        //     expression.substr(op_left, op_right - op_left + 1), left_tree,
        //     right_tree, curr_node);
        // if (!result.second) {
        //     this->_curr_node = curr_node - 1;
        // }

        // return {result.first, op_right + 1};

        // 然后和上面创建叶子节点一样的逻辑
        // 这个函数可以提取出来
        // auto result = this->TryCreateNode(op, left_tree, right_tree,
        // curr_node); if (!result.second) {
        //     // 如果没有分配成功，应该返回之前的状态
        //     // this->_curr_node = curr_node - 1;
        //     this->_curr_node--;
        // }

        // 构建一个ExpressionNode
        ExpressionNode node{op, left_tree, right_tree};
        // 然后在map中寻找
        auto it = this->dict.find(node);
        if (it == this->dict.end()) {
            // 没有找到，那么就插入这个node，
            // node_t curr_node = node_id;
            this->dict.insert({node, curr_node});
            // BUG!
            // 这里的push back是不对的，只能直接插入
            // 所以需要保证数组足够长
            // _nodes.push_back(node);
            // _is_visited.push_back(false);
            _nodes[curr_node] = node;
            done[curr_node] = false;
            return {curr_node, p};
        } else {
            this->_curr_node--;
            // 相反，如果这个节点已经存在，那么我们就不需要在建立一个新的节点，直接返回一个旧的已经存在的几点就行了
            return {it->second, p};
        }

        // return {result.first, p};
    }

  private:
    // 节点编号从1开始
    node_t _curr_node = 0;
    std::unordered_map<ExpressionNode, node_t> dict;
    node_t _root;
    std::string _expression;
};

int main(int argc, char* argv[]) {
    // 首先创建表达式树
    // 实际上在建树的过程中就可以寻找公共表达式
    // 我们使用一个特殊的符号表示一棵树
    // (root, left, right)
    // 比如 (a, 0, 0) 表示一个符号为a的叶子节点
    // 这需要一个map来保存

    // 建树当然是递归的
    // 我们用和之前一样的方法，使用一个字符串expression，left，right的方式表示当前需要创建的树
    // 然后返回的就是新创建的树的id
    // 如果这棵树没有被创建过，那么就创建一个新的，放到map中，否则就返回map中已经存在的树的id即可

    // 要不把这个数组变成全局的吧，好像有点太话费时间了

    int case_count = 0;
    std::cin >> case_count;

    std::string buffer;
    std::getline(std::cin, buffer);

    while (std::getline(std::cin, buffer)) {
        // 模拟c语言字符串
        buffer.push_back('\0');
        ExpressionTree expr_tree{buffer};
        std::string expr = expr_tree.GetSimplestExpression();
        std::cout << expr << std::endl;
    }
}
