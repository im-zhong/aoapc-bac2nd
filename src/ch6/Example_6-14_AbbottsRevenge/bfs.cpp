// 2024/10/19
// zhangzhong
// 先写一个简单的bfs感受一下，不过为什么这个和djstra的最短路算法不一样呢?

#include <iostream>
#include <queue>

const int map_row = 6;
const int map_col = 5;

// 或许从文件中读入会更好些
int map[map_row][map_col] = {
    {
        1,
        1,
        0,
        1,
        1,
    },
    {
        1,
        0,
        1,
        1,
        1,
    },
    {
        1,
        0,
        1,
        0,
        0,
    },
    {
        1,
        0,
        1,
        1,
        1,
    },
    {
        1,
        1,
        1,
        0,
        1,
    },
    {
        1,
        1,
        1,
        1,
        1,
    },
};

bool flag[map_row][map_col] = {};

// 图中的每一个节点都可以用一对坐标来表示
// 每一个节点都有自己的parent
// 我们只需要保存这个信息就足够了
//
// 同时，我们还需要有一个机制来保证我们不会重复访问节点
// 显然我们可以采取跟dfs相同的思路，设置一个flag，如果我们已经访问过一个节点了（也就是这个节点入队过了），那么之后就不会再次被入队了
struct Node {
    int row;
    int col;
    // 我们仍然可以借助graphviz来画图，辅助我们学习
    // Node parent;
};

Node parents[map_row][map_col] = {};

bool in_range(int row, int col) {
    return row >= 0 && row < map_row && col >= 0 && col < map_col;
}

void check_dir(Node node, int row, int col, std::queue<Node>& queue) {
    // in range
    if (in_range(row, col)) {
        // is legal to visit && not visited
        if (!flag[row][col] && map[row][col] == 1) {
            // visit node
            queue.push(Node{row, col});
            flag[row][col] = true;
            // set parent
            parents[row][col] = node;
        }
    }
}

void bfs() {

    // 初始化 flag 和 parents
    for (int r = 0; r < map_row; r++) {
        for (int c = 0; c < map_col; c++) {
            flag[r][c] = false;
            parents[r][c] = Node{-1, -1};
        }
    }

    auto start = Node{0, 0};

    // 把start 放到队列中
    // 或许这两个可以包装成一个函数 叫做 Visit
    // 这样不容易出错
    auto queue = std::queue<Node>{};
    queue.push(start);
    // 不要忘记把00标记为已经访问过了
    flag[0][0] = true;

    while (!queue.empty()) {
        auto node = queue.front();
        queue.pop();

        // find the adjance of the queue
        // 我想起来了，算法书上是有bfs的代码的
        // 我们先自己尝试些一下，然后查看一下算法书

        // 迷宫只有四格方向
        // 上下左右
        // up
        check_dir(node, node.row - 1, node.col, queue);
        check_dir(node, node.row + 1, node.col, queue);
        check_dir(node, node.row, node.col - 1, queue);
        check_dir(node, node.row, node.col + 1, queue);
    }
}

int main() {

    // 假设我们的输入就是一个bitmap
    // 我们的任务就是从一个点找到到其他点的最短路
    bfs();

    // 现在这个结果就基本是对的
    for (int r = 0; r < map_row; r++) {
        for (int c = 0; c < map_col; c++) {

            std::cout << "(" << parents[r][c].row << "," << parents[r][c].col
                      << ") ";
        }
        std::cout << std::endl;
    }
}
