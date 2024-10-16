// 2024/10/16
// zhangzhong

// very easy, just write a fully binary tree

#include <iostream>
#include <vector>

class FullyBinaryTree {
  public:
    FullyBinaryTree(size_t depth) : _depth(depth), _tree(1 << depth, false) {}

    size_t drop_balls(size_t ball_count) {
        for (int i = 0; i < ball_count - 1; i++) {
            drop_one_ball();
        }
        return drop_one_ball();
    }

    size_t drop_one_ball() {
        // just simulate the drop process
        // and return the tree node index
        // 0 in _tree is not use

        size_t node = 1;
        while (!this->is_leaf(node)) {
            // 不论如何我们都需要切换switch
            // 而且切换switch之后，我们的结果就回反过来
            // 那么我们不如直接反过来实现
            _tree[node] = !_tree[node];

            // check the switch
            if (_tree[node]) {
                // fallen right
                node = this->left_child(node);
            } else {
                node = this->right_child(node);
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
    std::vector<bool> _tree;
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