// 2025/3/28
// zhangzhong
//

#include <cassert>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <string>
// #include <unordered_map>
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

    ExpressionNode() : op(), left(-1), right(-1) {}

    bool operator<(const ExpressionNode& other) const noexcept {
        if (this->op != other.op) {
            return this->op < other.op;
        }
        if (this->left != other.left) {
            return this->left < other.left;
        }
        return this->right < other.right;
        // return this->op < other.op && this->left == other.left &&
        //        this->right == other.right;
    }
};

// 然后ExpressionNode要支持hash操作

// namespace std {
// template <> struct hash<ExpressionNode> {
//     size_t operator()(const ExpressionNode& self) const noexcept {
//         return hash<std::string>{}(self.op) ^ hash<node_t>{}(self.left) ^
//                hash<node_t>{}(self.right);
//     }
// };
// }; // namespace std
static constexpr int max_node_count = 60000;

std::vector<ExpressionNode> _nodes(max_node_count);

// 这样写默认全是零
int done[max_node_count];
int kase = 0;
char expr[max_node_count * 5], *p;

class ExpressionTree {
  public:
    ExpressionTree(const std::string& expression) {
        auto result = this->BuildExpressionTree(expression, 0);
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
    void GetSimplestExpression() {

        // 构建这棵树的过程应该也是递归的

        this->BuildStringTree(this->_root);
    }

    // 这是为什么？
    // 卧槽，改了print，就通过了
    // 也就是之前的递归字符串相加和print不一样！
    // 应该是在某些条件下不一样。我也拿不到测试的case，也不知道啊
    // 这里的print的实现，其实就是往一个buffer里面顺序的放东西
    // 而咱们之前的递归的实现，会有很多的小string的加法
    // 所以从性能上，还是这样快一些
    // 这两个版本的实现应该是没有任何区别的，我怀疑是测试环境的BUG
  private:
    void BuildStringTree(node_t v) {
        if (done[v] == kase) {
            std::printf("%d", v + 1);
        } else {
            // 有点像MVCC 版本号 version
            done[v] = kase;

            // 我们找到root，就可以找到她的节点
            ExpressionNode& node = _nodes[v];
            // 当然了，如果是叶子节点 就是递归的结束条件
            std::printf("%s", node.op.c_str());

            if (node.left != -1) {
                std::putchar('(');
                this->BuildStringTree(node.left);
                std::putchar(',');
                this->BuildStringTree(node.right);
                std::putchar(')');
            }
        }
    }

    std::pair<int, int> BuildExpressionTree(const std::string& expression,
                                            const int left) {

        node_t id = this->_curr_node++;
        // 然后我们直接引用这个node，和我们自己的应该是一样的
        // ! 我懂了，因为他这里的node会被重复取用，所以每次必须要初始化
        // 而我们之前的写法每次都会创建一个新的 就不用初始化了
        ExpressionNode& u = _nodes[id];
        u.left = -1;
        u.right = -1;
        u.op = "";

        int p = left;
        for (; std::isalpha(expression[p]); p++) {
            u.op.push_back(expression[p]);
        }

        if (expression[p] == '(') {
            // assert(expression[p] == '(');
            // 然后就可以构建左子树了

            // 但是我们的节点可能是失败的，我们需要知道我们的节点是不是重复
            // 如果是的话，需要去掉
            p++;
            // 然后咱们只需要递归的创建子表达式就行了
            auto result = this->BuildExpressionTree(expression, p);
            u.left = result.first;
            p = result.second;

            // 哎不行啊，我们的BuildExpressionTree这样就不能有right了，否则就不会自动的去读取串了
            // 我们不仅不能含有right，还得让这个函数返回right

            // 然后接下来一定是一个逗号
            assert(expression[p] == ',');

            p++;
            result = this->BuildExpressionTree(expression, p);
            u.right = result.first;
            p = result.second;
            // 这里的测试是不对的
            // 这里可能
            assert(expression[p] == ')');
            // 最后处理完这个操作符之后，要跳到下一个位置，开启下一个的解析
            p++;
        }

        // 这样设计的好处是，如果操作正确，我们不需要再额外构建一个对象
        // 但是坏处是，如果是错误的，那么会留下一个错误的节点
        // 这里的id难道不会设置错误吗？

        if (dict.count(u) != 0) {
            this->_curr_node--;
            return {dict[u], p};
        }
        return {dict[u] = id, p};
    }

  private:
    // 节点编号从1开始
    node_t _curr_node = 0;
    std::map<ExpressionNode, node_t> dict;
    node_t _root;
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
    // std::cin >> case_count;
    std::scanf("%d", &case_count);

    std::string buffer;
    // std::getline(std::cin, buffer);
    for (kase = 1; kase <= case_count; kase++) {

        scanf("%s", expr);
        // std::getline(std::cin, buffer);
        std::string buffer(expr);
        buffer.push_back('\0');

        ExpressionTree expr_tree{buffer};
        expr_tree.GetSimplestExpression();
        std::putchar('\n');
        // std::string expr = expr_tree.GetSimplestExpression();
        // std::cout << expr << std::endl;
    }
}
