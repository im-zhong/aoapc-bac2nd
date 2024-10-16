// 2024/10/16
// zhangzhong

#include <iostream>

class FullyBinaryTree {
  public:
    FullyBinaryTree(size_t depth) : _depth(depth) {}

    size_t drop_balls(size_t ball_count) {
        size_t node = 1;
        for (int i = 0; i < _depth - 1; i++) {
            if (ball_count % 2 != 0) {
                node = this->left_child(node);
                ball_count = (ball_count + 1) / 2;
            } else {
                node = this->right_child(node);
                ball_count = ball_count / 2;
            }
        }
        return node;
    }

    size_t left_child(size_t node) { return node * 2; }
    size_t right_child(size_t node) { return left_child(node) + 1; }
    size_t parent(size_t node) { return node / 2; }

  private:
    size_t min_leaf_node() const { return 1 << (this->_depth - 1); }
    size_t max_leaf_node() const { return (1 << this->_depth) - 1; }

    bool is_leaf(size_t node) {
        return node >= this->min_leaf_node() && node <= this->max_leaf_node();
    }

    size_t _depth;
    // std::vector<bool> _tree;
};

int main() {

    int case_count = 0;
    std::cin >> case_count;

    for (int i = 0; i < case_count; i++) {
        size_t depth = 0;
        size_t ball_count = 0;
        std::cin >> depth >> ball_count;

        auto fbt = FullyBinaryTree{depth};
        std::cout << fbt.drop_balls(ball_count) << "\n";
    }
}