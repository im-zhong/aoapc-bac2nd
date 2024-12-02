// 2024/12/2
// zhangzhong

#include <iostream>
#include <queue>
#include <vector>

constexpr int max_n = 102400;

void dfs(int root, int* dp, int employee_count,
         const std::vector<std::vector<int>>& adjs, int percentage) {

    // 有两种情况
    // 第一种 叶子
    if (adjs[root].empty()) {
        // worker
        dp[root] = 1;
        return;
    }

    // recursive
    // 优先队列默认是小根堆还是大根堆来着？
    // default is std::less<T>, the greatest element will on the top
    // using std::greater<T> would cause the smallest element to appear as the
    // top().
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

    for (int employee : adjs[root]) {
        // int boss = root;
        dfs(employee, dp, employee_count, adjs, percentage);
        pq.push(dp[employee]);
    }

    dp[root] = 0;
    // 根据子节点所需工人数量从小到大排序
    int child_count = adjs[root].size();
    int count = 0;
    // fulfill the percentage
    while (count * 100 < child_count * percentage) {
        int worker_count = pq.top();
        count++;
        dp[root] += worker_count;

        pq.pop();
    }
}

int GetMinimumCount(const std::vector<std::vector<int>>& adjs,
                    int employee_count, int percentage) {
    int dp[max_n];
    dfs(0, dp, employee_count, adjs, percentage);
    return dp[0];
}

int main() {

    int employee_count = 0;
    int percentage = 0;

    while (std::cin >> employee_count >> percentage) {
        if (employee_count == 0 && percentage == 0) {
            break;
        }

        // employee_count not include the owner
        // owner is 0, each of the employees is identified by an integer between
        // 1 and N

        // 我们使用一个邻接链表来保存整张图
        std::vector<std::vector<int>> adjs(employee_count + 1);
        for (int e = 1; e <= employee_count; e++) {
            int boss = 0;
            std::cin >> boss;
            adjs[boss].push_back(e);
        }

        int minimum_count = GetMinimumCount(adjs, employee_count, percentage);
        std::cout << minimum_count << "\n";
    }
}
