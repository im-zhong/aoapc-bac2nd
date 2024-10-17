// 2024/10/17
// zhangzhong

#include <ios>
#include <iostream>
#include <string>

// 突然发现，我们可以实现一个函数，用来计算某一棵树的black pixels数量啊
int construct_tree(const std::string& quadtree, int& index, int depth) {
    char node = quadtree[index];

    if (node == 'f') {
        return 1024 / (1 << 2 * depth);
    }

    if (node == 'e') {
        return 0;
    }

    if (node == 'p') {

        // calculate four sub tree and sum it

        int sum = 0;
        for (int i = 0; i < 4; i++) {
            ++index;
            sum += construct_tree(quadtree, index, depth + 1);
        }
        return sum;
    }

    return -1;
}

// 这个函数的index也必须是引用
// 否则我们在调用返回之后 index的值就不对了
int calculate_black_pixels(const std::string& left_quadtree, int& left_index,
                           const std::string& right_quadtree, int& right_index,
                           int depth) {

    char left_node = left_quadtree[left_index];
    char right_node = right_quadtree[right_index];

    // 构建四颗子树

    // // 不对，只有当我们是p的时候才需要构建子树
    // if (left_node == 'p') {
    //     return construct_tree(left_quadtree, left_index, depth);
    // }
    // if (right_node == 'p') {
    //     return construct_tree(right_quadtree, right_index, depth + 1);
    // }

    if (left_node == 'f' || right_node == 'f') {
        // 这样我们根本就不用考虑其他的pixels
        // 直接返回depth对应的pixel数量即可

        int left_count = construct_tree(left_quadtree, left_index, depth);
        int right_count = construct_tree(right_quadtree, right_index, depth);
        if (left_node == 'f') {
            return left_count;
        } else {
            return right_count;
        }
    }

    // 如果有一个是白的，那么pixels数量数量就是另外一个的
    // if (left_node == 'e') {
    //     // return right_node
    //     return construct_tree(right_quadtree, right_index, depth);
    // }
    // if (right_node == 'e') {
    //     // return left_node black pixel count
    //     return construct_tree(left_quadtree, left_index, depth);
    // }

    if (left_node == 'e' || right_node == 'e') {
        int left_count = construct_tree(left_quadtree, left_index, depth);
        int right_count = construct_tree(right_quadtree, right_index, depth);
        if (left_node == 'e') {
            return right_count;
        } else {
            return left_count;
        }
    }

    // 两个都是 p

    // 无论如何，我们这个函数的作用就是返回两颗子树的和
    // 如果这两个节点都是gray的
    // 那么和就是四个子树的分别的和
    int sum = 0;
    for (int i = 0; i < 4; i++) {
        ++left_index;
        ++right_index;
        sum += calculate_black_pixels(left_quadtree, left_index, right_quadtree,
                                      right_index, depth + 1);
    }
    return sum;
}

int main() {
    int case_count = 0;
    std::cin >> case_count;
    // read the last \n
    std::string buffer;
    std::getline(std::cin, buffer);

    for (int i = 0; i < case_count; i++) {
        std::string left_quadtree;
        std::getline(std::cin, left_quadtree);

        std::string right_quadtree;
        std::getline(std::cin, right_quadtree);

        int left_index = 0;
        int right_index = 0;
        int count = calculate_black_pixels(left_quadtree, left_index,
                                           right_quadtree, right_index, 0);
        std::cout << "There are " << count << " black pixels.\n";
    }
}