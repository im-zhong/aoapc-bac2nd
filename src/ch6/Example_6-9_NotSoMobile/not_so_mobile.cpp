// 2024/10/17
// zhangzhong

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/types.h>

struct TreeNode {
    uint64_t left_weight;
    uint64_t left_distance;
    uint64_t right_weight;
    uint64_t right_distance;
    TreeNode* left;
    TreeNode* right;

    bool is_balance() {
        return this->get_left_weight() * this->left_distance ==
               this->get_right_weight() * this->right_distance;
    }

    uint64_t get_left_weight() {
        if (this->left_weight != 0) {
            return this->left_weight;
        } else {
            return this->left->get_weight();
        }
    }

    uint64_t get_right_weight() {
        if (this->right_weight != 0) {
            return this->right_weight;
        } else {
            return this->right->get_weight();
        }
    }

    uint64_t get_weight() {
        return this->get_left_weight() + this->get_right_weight();
    }
};

bool is_balance = true;
void check_balance(TreeNode* tree) {
    if (!tree) {
        return;
    }

    check_balance(tree->left);
    check_balance(tree->right);
    if (!tree->is_balance()) {
        is_balance = false;
    }
}

void print_preorder(TreeNode* tree) {
    if (!tree) {
        return;
    }

    std::cout << tree->left_weight << " " << tree->left_distance << " "
              << tree->right_weight << " " << tree->right_distance << ", ";
    print_preorder(tree->left);
    print_preorder(tree->right);
}

TreeNode* construct_tree() {
    // read a new line
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ssr{line};

    uint64_t left_weight = 0;
    uint64_t left_distance = 0;
    uint64_t right_weight = 0;
    uint64_t right_distance = 0;

    if (!(ssr >> left_weight >> left_distance >> right_weight >>
          right_distance)) {
        return nullptr;
    }

    // 根左右
    auto node = new TreeNode{left_weight,    left_distance, right_weight,
                             right_distance, nullptr,       nullptr};
    if (left_weight == 0) {
        node->left = construct_tree();
    }
    if (right_weight == 0) {
        node->right = construct_tree();
    }

    return node;
}

int main() {
    int case_count = 0;
    std::cin >> case_count;
    std::string buffer;
    std::getline(std::cin, buffer);

    for (int i = 0; i < case_count; i++) {
        // read the blank line
        std::getline(std::cin, buffer);
        TreeNode* tree = construct_tree();
        // print_preorder(tree);
        // std::cout << std::endl;
        is_balance = true;
        check_balance(tree);
        if (is_balance) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
        if (i < case_count - 1) {
            std::cout << std::endl;
        }
    }
}
