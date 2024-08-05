// 2024/8/5
// zhangzhong

#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

char action[16] = "";
char direction[16] = "";

void return_back(vector<vector<int>>& buckets, vector<int>& on_position,
                 int a) {
    // find a on which bucket
    int position = on_position[a];
    auto& blocks = buckets[position];

    int block = 0;
    while ((block = blocks.back()) != a) {
        blocks.pop_back();
        buckets[block].push_back(block);
        on_position[block] = block;
    }
}

// 可以提取出一个更底层的操作
// 就是取出一个vector 在block a 之上
vector<int> pop_blocks_on_top_of(vector<vector<int>>& buckets,
                                 vector<int>& on_position, int a) {
    // find a on which bucket
    int position = on_position[a];
    auto& blocks = buckets[position];

    auto v = vector<int>{};
    int block = 0;
    while ((block = blocks.back()) != a) {
        blocks.pop_back();
        v.push_back(block);
    }

    // and finally, push a onto
    blocks.pop_back();
    v.push_back(a);
    return v;
}

void move(vector<vector<int>>& buckets, vector<int>& on_position, int a, int b,
          char* action) {

    if (on_position[a] == on_position[b]) {
        return;
    }

    return_back(buckets, on_position, a);
    if (strcmp(action, "onto") == 0) {
        return_back(buckets, on_position, b);
    }

    int a_position = on_position[a];
    auto& a_blocks = buckets[a_position];
    // 此时a必然是最后一个
    a_blocks.pop_back();

    int b_position = on_position[b];
    buckets[b_position].push_back(a);
    // 更新a的位置，现在a和b在同一个位置
    on_position[a] = on_position[b];
}

void pile(vector<vector<int>>& buckets, vector<int>& on_position, int a, int b,
          char* action) {
    if (on_position[a] == on_position[b]) {
        return;
    }

    auto blocks = pop_blocks_on_top_of(buckets, on_position, a);
    if (strcmp(action, "onto") == 0) {
        return_back(buckets, on_position, b);
    }

    int b_position = on_position[b];
    for (auto i = blocks.rbegin(); i != blocks.rend(); i++) {
        buckets[b_position].push_back(*i);
        on_position[*i] = on_position[b];
    }
}

int main() {
    int n = 0;
    scanf("%d", &n);

    auto buckets = vector<vector<int>>{};
    auto on_position = vector<int>{};
    for (int i = 0; i < n; i++) {
        buckets.push_back(vector<int>{i});
        on_position.push_back(i);
    }

    while (true) {
        scanf("%s", action);
        if (strcmp(action, "quit") == 0) {

            // 这里要输出所有的结果
            for (int i = 0; i < n; i++) {
                printf("%d:", i);
                for (auto it = buckets[i].begin(); it != buckets[i].end();
                     it++) {
                    printf(" %d", *it);
                }
                printf("\n");
            }

            return 0;
        }

        int a = 0, b = 0;
        scanf("%d%s%d", &a, direction, &b);

        if (strcmp(action, "move") == 0) {
            move(buckets, on_position, a, b, direction);
        } else {
            pile(buckets, on_position, a, b, direction);
        }
    }
}