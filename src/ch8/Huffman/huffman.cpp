// 2024/11/11
// zhangzhong

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <map>
#include <random>
#include <string>

struct TreeNode {

    TreeNode* left;
    TreeNode* right;

    int frequency;
    // 叶子节点是一个字母，非叶子节点是\0 这样可以区分
    // 叶子节点对应着一串字母 0001
    char ch;

    // 提供一个排序函数，这样可以sort
    friend bool operator<(const TreeNode& lhs, const TreeNode& rhs) noexcept {
        return lhs.frequency < rhs.frequency;
    }

    bool IsLeaf() const noexcept { return left == nullptr && right == nullptr; }
};

class HuffmanCoding {

    // 我们假设输入是26个字母吧
    // 然后每个输入代表着一个频率

  public:
    HuffmanCoding(const std::vector<int>& alphabet_frequency)
        : alphabet_frequency_{alphabet_frequency} {}

    // 然后对于每一个字母，返回一个对应的coding
    std::map<char, std::string> MakeCode() {

        // 简单来说，我们先对频率数组进行排序
        // 比较简单的做法就是把树的节点作为数组的元素，同时进行排序
        // 因为我们本来就需要构造这样一棵树，同时放在数组里面进行排序，那就更节省内存了

        std::vector<TreeNode> leaves;
        for (int i = 0; i < this->alphabet_frequency_.size(); i++) {
            leaves.push_back(TreeNode{nullptr, nullptr,
                                      this->alphabet_frequency_[i],
                                      static_cast<char>('a' + i)});
        }
        std::sort(leaves.begin(), leaves.end());

        // 我们需要另外一个数组来保存新产生的节点
        std::vector<TreeNode> not_leaves;
        // 这样写会改变vector的size 怎么只增大capacity来着？
        // reserve只改变capacity, resize会直接改变数组的size
        not_leaves.reserve(256);

        // 现在开始构建树的过程
        // 首先从两个数组中找出最小的frequency最小的两个节点
        int i = 0;
        int j = 0;

        while (true) {
            // 我们需要两个节点
            TreeNode* p_left = nullptr;

            if (i < leaves.size() && j < not_leaves.size()) {
                // 这里不太好写
                if (leaves[i] < not_leaves[j]) {
                    // choose this one
                    p_left = &leaves[i];
                    i++;
                } else {
                    p_left = &not_leaves[j];
                    j++;
                }
            } else if (i < leaves.size()) {
                // 现在我们只能从 leaves 里面取节点
                p_left = &leaves[i];
                i++;
            } else if (j < not_leaves.size()) {
                // 只能从 not leaves中取
                p_left = &not_leaves[j];
                j++;
            } else {
                // 都找不到说明程序结束了
                // not leaves数组中的最后一个节点就是 root
                break;
            }

            TreeNode* p_right = nullptr;
            if (i < leaves.size() && j < not_leaves.size()) {
                // 这里不太好写
                if (leaves[i] < not_leaves[j]) {
                    // choose this one
                    p_right = &leaves[i];
                    i++;
                } else {
                    p_right = &not_leaves[j];
                    j++;
                }
            } else if (i < leaves.size()) {
                // 现在我们只能从 leaves 里面取节点
                p_right = &leaves[i];
                i++;
            } else if (j < not_leaves.size()) {
                // 只能从 not leaves中取
                p_right = &not_leaves[j];
                j++;
            } else {
                // 都找不到说明程序结束了
                // not leaves数组中的最后一个节点就是 root
                break;
            }

            // 拿到节点之后，创建一个新的节点
            // if (p_left->frequency + p_right->frequency == 0) {
            //     std::cout << "why";
            // }
            // 节点的frequency不可能是零
            if (p_left == nullptr || p_right == nullptr) {
                std::cout << "why";
            }
            if (p_left->frequency == 0 || p_right->frequency == 0) {
                std::cout << "why";
            }
            int f = p_left->frequency + p_right->frequency;
            if (f == 75) {
                std::cout << f << std::endl;
            }
            TreeNode node = TreeNode{p_left, p_right, f, '\0'};
            // [[BUG]]
            // 卧槽，这是重大bug，我们不能使用vector中变量的地址作为treenode的地址
            // 因为vector在push back的时候会发生 resize 他会创建新的节点
            // 导致我们之前保存的节点指针指向错误的内存地址，我竟然才意识到这一点。。。
            // 正确的做法是预先分配足够的内存
            not_leaves.push_back(node);
        }

        TreeNode* root = &not_leaves.back();

        // 我直接遍历一下这个 not leaves 数组看一下吧
        std::cout << "not leaves:\n";
        for (const auto& node : not_leaves) {
            std::cout << node.frequency << " l-> " << node.left->frequency
                      << "\n";
            std::cout << node.frequency << " r-> " << node.right->frequency
                      << "\n";
            std::cout << std::endl;
        }

        // 然后一个dfs就可以构造coding
        std::string coding;
        this->dfs(root, coding);

        return this->codings_;
    }

  private:
    // 我们可以统计一下节点数量，看看是不是都访问过了
    void dfs(const TreeNode* root, std::string& current_coding) {
        if (!root) {
            return;
        }

        this->node_count_++;

        // if is leaf
        if (root->IsLeaf()) {
            this->codings_.insert({root->ch, current_coding});
            return;
        }

        if (root->left) {
            std::cout << root->frequency << " l-> " << root->left->frequency
                      << std::endl;
        }
        if (root->right) {
            std::cout << root->frequency << " r-> " << root->right->frequency
                      << std::endl;
        }

        current_coding.push_back('0');
        this->dfs(root->left, current_coding);
        current_coding.pop_back();

        current_coding.push_back('1');
        this->dfs(root->right, current_coding);
        current_coding.pop_back();

        // 能打印出这棵树来就好了
    }

  private:
    std::vector<int> alphabet_frequency_;
    std::map<char, std::string> codings_;
    int node_count_ = 0;
};

int main() {
    std::vector<int> alphabet_frequency;

    // 用随机数填充吧

    // std::default_random_engine e(
    //     std::chrono::system_clock::now().time_since_epoch().count());

    std::default_random_engine e(12345);

    // [0, 1023] both inclusive
    int min = 10;
    int max = 200;
    std::uniform_int_distribution<int> u(min, max);

    for (int i = 0; i < 26; i++) {
        alphabet_frequency.push_back(u(e));
    }

    HuffmanCoding hc{alphabet_frequency};
    std::map<char, std::string> codings = hc.MakeCode();
    for (const auto& pair : codings) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }
}