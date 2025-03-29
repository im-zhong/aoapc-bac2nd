// 2025/3/28
// zhangzhong
//

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>

// 我们当前的版本应该是对的，只不过我们是在某个节点创建完成之后才分配节点，这样实现应该是更简单的
// 但是按照题目的要求，应该是在第一次碰到这个节点的时候就为其分配节点
// 咱们copy一份代码，试着实现一下

using node_t = int;

struct ExpressionNode {
    std::string op;
    node_t left;
    node_t right;

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

class ExpressionTree {
  public:
    ExpressionTree(const std::string& expression) : _expression(expression) {
        // 0号节点是一个空的节点，我们push一个空的进去
        this->_nodes.push_back(ExpressionNode{", 0, 0"});
        this->_is_visited.push_back(true);
        // ok，现在我们的表达式的样子是对了，但是节点的顺序不对，说实话，我实在是不知道她的节点的顺序是指的什么。。。
        this->_root =
            this->BuildExpressionTree(expression, 0, expression.size() - 1);
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

        if (this->_is_visited[root]) {
            return std::to_string(root);
        }

        this->_is_visited[root] = true;

        // 我们找到root，就可以找到她的节点
        ExpressionNode node = this->_nodes[root];
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

    node_t CreateNode(const std::string& op, node_t left, node_t right) {
        // 构建一个ExpressionNode
        const ExpressionNode node{op, left, right};
        // 然后在map中寻找
        auto it = this->dict.find(node);
        if (it == this->dict.end()) {
            // 没有找到，那么就插入这个node，
            node_t curr_node = ++this->_curr_node;
            this->dict.insert({node, curr_node});
            this->_nodes.push_back(node);
            this->_is_visited.push_back(false);
            return curr_node;
        } else {
            // 相反，如果这个节点已经存在，那么我们就不需要在建立一个新的节点，直接返回一个旧的已经存在的几点就行了
            return it->second;
        }
    }

    int BuildExpressionTree(const std::string& expression, const int left,
                            const int right) {

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
        if (expression.substr(left, right - left + 1).find('(') ==
            std::string::npos) {
            // 叶子节点

            return this->CreateNode(expression.substr(left, right - left + 1),
                                    0, 0);
        }

        int op_left = -1;
        int op_right = -1;
        int op1_left = -1;
        int op1_right = -1;
        int op2_left = -1;
        int op2_right = -1;

        op_left = left;
        int bracket_depth = 0;
        for (int i = left; i <= right; i++) {
            // 下面这个只能处理非叶子节点
            // 如果想要处理叶子节点
            switch (expression[i]) {
                // 还没有这么简单，因为我们会遇到很多层的括号
                //
            case '(': {
                // 进入操作符模式
                bracket_depth++;

                // 只有第一个括号开始的时候，才开始记录第一个操作数
                if (bracket_depth == 1) {
                    op_right = i - 1;
                    op1_left = i + 1;
                }
                break;
            }

            case ')': {
                if (bracket_depth == 1) {
                    op2_right = i - 1;
                }

                // 退出操作符模式
                bracket_depth--;
                // 只有当当前的括号是1的时候，才是操作数的结束

                break;
            }

            case ',': {
                // 切换操作数
                // 只有当只有一层括号的时候，才切换操作数
                if (bracket_depth == 1) {
                    // 记录第一个操作数
                    op1_right = i - 1;
                    // 开始记录下一个操作数
                    op2_left = i + 1;
                }
            }
            }
        }

        // 最终我们一定可以找到所有的操作数
        // 也就是所有的op left right 都不能是-1
        assert(op_left != -1);
        assert(op_right != -1);
        assert(op1_left != -1);
        assert(op1_right != -1);
        assert(op2_left != -1);
        assert(op2_right != -1);

        // 哎，不对呀，我们这里如果返回的不是node_t
        // 就是这棵子树的字符串，是不是一趟就可以写出来了？
        // 感觉还是不太行。

        // 然后咱们只需要递归的创建子表达式就行了
        node_t left_tree =
            this->BuildExpressionTree(expression, op1_left, op1_right);
        node_t right_tree =
            this->BuildExpressionTree(expression, op2_left, op2_right);

        // 然后和上面创建叶子节点一样的逻辑
        // 这个函数可以提取出来
        return this->CreateNode(
            expression.substr(op_left, op_right - op_left + 1), left_tree,
            right_tree);
    }

  private:
    // 节点编号从1开始
    node_t _curr_node = 0;
    std::unordered_map<ExpressionNode, node_t> dict;
    node_t _root;
    std::string _expression;
    std::vector<ExpressionNode> _nodes;
    std::vector<bool> _is_visited;
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

    int case_count = 0;
    std::cin >> case_count;

    std::string buffer;
    std::getline(std::cin, buffer);

    while (std::getline(std::cin, buffer)) {
        ExpressionTree expr_tree{buffer};
        std::string expr = expr_tree.GetSimplestExpression();
        std::cout << expr << std::endl;
    }
}
