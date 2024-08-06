// 2024/8/6
// zhangzhong

#include <cstdio>

#include <queue>

// 对于每一个队伍，都有一个自己的队列
auto team_queues = std::vector<std::queue<int>>{};
// 同时我们有一个全局的队伍, 用id来代表队伍
auto global_queue = std::queue<int>{};

auto id_table = std::unordered_map<int, int>{};

auto buffer = std::array<char, 16>{};

void enqueue(int id) {
    int team_index = id_table[id];

    auto& queue = team_queues[team_index];
    // 在push之前，如果我们的queue是空的 那么表示globalqueue中没有当前team
    // 应该push当前的team index
    if (queue.empty()) {
        global_queue.push(team_index);
    }
    queue.push(id);
}

auto dequeue() -> int {
    int front_team_index = global_queue.front();

    auto& queue = team_queues[front_team_index];
    auto id = queue.front();
    queue.pop();

    // 如果我们pop之后，队列空了，那么global queue也要pop
    if (queue.empty()) {
        global_queue.pop();
    }
    return id;
}

void run_team_queue(int team_count) {
    team_queues.clear();
    // 对于每一个team 我们都要安排一个空的队列
    for (int i = 0; i < team_count; i++) {
        team_queues.push_back(std::queue<int>{});
    }

    // queue竟然没有clear操作。。。
    // global_queue.clear();
    while (!global_queue.empty()) {
        global_queue.pop();
    }
    id_table.clear();

    for (int team_index = 0; team_index < team_count; team_index++) {
        int member_count = 0;
        std::scanf("%d", &member_count);
        while (member_count--) {
            int id = 0;
            std::scanf("%d", &id);
            id_table.insert({id, team_index});
        }
    }

    while (true) {
        std::scanf("%s", buffer.data());
        auto action = std::string{buffer.data()};
        if (action == "STOP") {
            break;
        }

        if (action == "ENQUEUE") {
            int id = 0;
            std::scanf("%d", &id);
            enqueue(id);
        } else {
            auto id = dequeue();
            printf("%d\n", id);
        }
    }
}

int main() {

    for (int i = 1;; i++) {

        int team_count = 0;
        std::scanf("%d", &team_count);
        if (team_count == 0) {
            break;
        }

        printf("Scenario #%d\n", i);
        run_team_queue(team_count);
        printf("\n");
    }
}