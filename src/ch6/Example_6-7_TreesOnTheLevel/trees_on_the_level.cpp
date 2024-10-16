// 2024/10/16
// zhangzhong

#include <iostream>
#include <sstream>
#include <vector>

class BinaryTree {

  public:
    // [[BUG]]
    // 256个节点并不是说只有256个，实际上最深会有2^256层，我们这里是因为tree太小了
    // 导致数组溢出
    BinaryTree() : _size{0}, _tree(1 << 20, -1) { this->_tree[0] = 0; }

    bool insert(const std::string& path, int value) {
        size_t node = 1;
        for (const auto& direction : path) {
            if (direction == 'L') {
                node = this->left_child(node);
            } else {
                node = this->right_child(node);
            }
        }

        if (this->_tree[node] != -1) {
            return false;
        }
        this->_tree[node] = value;
        ++this->_size;
        return true;
    }

    void print_in_level_order() {
        if (this->_size == 0) {
            return;
        }

        size_t print_out_count = 0;
        for (size_t i = 1; i < this->_tree.size(); i++) {
            if (this->_tree[i] != -1) {
                std::cout << this->_tree[i];
                ++print_out_count;
                if (print_out_count < this->_size) {
                    std::cout << " ";
                }
            }
        }
        std::cout << "\n";
    }

    bool check_is_completely_specified() {
        // 0 这个位置不用刚好可以用来判断是否停止，不用用int类型了，nice
        // 因为我们的跟节点在1上，而且我们的0不用，所以下面这条判断语句对跟节点是错误的
        // 一个简单的方法是让跟节点不等于-1
        for (size_t i = _tree.size() - 1; i > 0; i--) {
            if (this->_tree[i] != -1 && _tree[this->parent(i)] == -1) {
                return false;
            }
        }
        return true;
    }

  private:
    size_t left_child(size_t node) { return node * 2; }
    size_t right_child(size_t node) { return left_child(node) + 1; }
    size_t parent(size_t node) { return node / 2; }

  private:
    size_t _size;
    std::vector<int> _tree;
};

int main() {
    std::string path;

    while (std::cin) {
        int value = 0;
        std::string buffer;

        auto bt = BinaryTree{};

        bool is_complete = true;
        while (std::cin >> buffer) {
            if (buffer == "()") {
                // next test case
                break;
            }
            // std::scanf("(%d,%s)"); how to read like this in cpp?
            std::stringstream ssr{buffer};

            char temp;
            std::string path;
            ssr >> temp >> value >> temp >> path;
            // pop back the last )
            path.pop_back();

            if (!bt.insert(path, value)) {
                is_complete = false;
                // [[BUG]] 不对的，到这里我们可能没有读完这整棵树啊
                // 我们可能只是中途发现错了
                // 所以我们必须在这里读完整棵树 也就是一直读 知道读到 ()
                while (std::cin >> buffer) {
                    if (buffer == "()") {
                        break;
                    }
                }
                std::cout << "not complete\n";
                break;
            }
        }

        if (is_complete) {
            // [[BUG!]] 如果我们是因为意外跳出的
            // 那么我们就不应该再走下面的这段逻辑了

            if (!bt.check_is_completely_specified()) {
                std::cout << "not complete\n";
            } else {
                bt.print_in_level_order();
            }
        }
    }
}