// 2024/10/16
// zhangzhong

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <vector>

struct TreeNode {
    TreeNode* left;
    TreeNode* right;
    int value;
};

std::vector<int> read_line() {
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ssr{line};
    std::vector<int> values{};
    int value = 0;
    while (ssr >> value) {
        values.push_back(value);
    }
    return values;
}

TreeNode* construct_tree(const std::vector<int>::iterator inorder_begin,
                         const std::vector<int>::iterator inorder_end,
                         const std::vector<int>::iterator postorder_begin,
                         const std::vector<int>::iterator postorder_end) {

    if (inorder_begin >= inorder_end) {
        return nullptr;
    }

    // 因为我们构建的方式是递归的 所以这个函数应该也是递归的
    // TreeNode* root = nullptr;

    auto value = *(postorder_end - 1);
    // find this root in f
    auto it_in = std::find(inorder_begin, inorder_end, value);
    // this is the root
    auto root = new TreeNode{nullptr, nullptr, value};

    // inorder.begin(), it_in 是左子树
    // it_in + 1, inorder.end() 是右子树

    // 关键问题是怎么找到子树的根，通过后序来找
    // 后序同样可以分成左子树 右子树 根
    // 那么我们就需要找到后序里面的左子树和右子树的分界
    // 我们显然可以根据数量来进行分界
    // 所以 postorder.begin(), pb + n 就是左子树
    // pb + n + 1, postorder.end() 就是右子树
    // 这样就可以递归了
    // 那么递归结束的条件是什么？
    // 就是左子树和右子树都没了
    // ，说明我们是叶子节点，就可以返回我们自己的叶子节点了
    int n = it_in - inorder_begin;

    root->left = construct_tree(inorder_begin, it_in, postorder_begin,
                                postorder_begin + n);
    root->right = construct_tree(it_in + 1, inorder_end, postorder_begin + n,
                                 postorder_end - 1);
    return root;
}

void print_preorder(TreeNode* root) {
    if (root) {
        std::cout << root->value << ", ";
        print_preorder(root->left);
        print_preorder(root->right);
    }
}

size_t global_sum = 99999999;
size_t leaf_value = 99999999;

void find_min_path(TreeNode* root, size_t sum) {

    if (root == nullptr) {
        return;
    }

    sum += root->value;

    if (root->left == nullptr && root->right == nullptr) {
        // leaf node
        if (sum < global_sum) {
            global_sum = sum;
            leaf_value = root->value;
        } else if (sum == global_sum) {
            if (root->value < leaf_value) {
                leaf_value = root->value;
            }
        }
    } else {
        find_min_path(root->left, sum);
        find_min_path(root->right, sum);
    }
}

int main() {
    while (std::cin) {
        auto inorder = read_line();
        auto postorder = read_line();

        // use this two sequence to construct a new tree
        auto tree = construct_tree(inorder.begin(), inorder.end(),
                                   postorder.begin(), postorder.end());

        // print_preorder(tree);
        // std::cout << "\n";
        if (tree) {
            global_sum = 99999999;
            leaf_value = 99999999;
            find_min_path(tree, 0);
            std::cout << leaf_value << std::endl;
        }
    }
}