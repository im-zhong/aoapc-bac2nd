// 2024/8/6
// zhangzhong

#include <array>
#include <cstdio>
#include <deque>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

auto team_queue = std::deque<std::queue<int>>{};

// 我们还需要保存所有的队列
// auto teams = std::vector<std::vector<int>>{};

// 我们还需要知道某个team的成员所在的位置
// 这里其实还有一个方法，我们除了拿team_index
// 还可以拿指针/引用，但是应该尽量避免使用他们，所以这里就不用了
auto team_table = std::vector<int>{};
auto id_table = std::unordered_map<int, int>{};

auto buffer = std::array<char, 16>{};

void enqueue(int id) {
    // first check if the team_index of member id is in the queue
    auto team_index = id_table[id];

    auto queue_index = team_table[team_index];
    if (queue_index == -1) {
        // 表示id所在的队列没有任何人在队列中
        // 那么我们就直接插到最后就ok啦
        // TIP: queue的初始化，不能直接提供元素，但是可以提供一个序列，及{1,2,3}
        team_queue.push_back(std::queue<int>{{id}});
        // 同时更新team table
        team_table[team_index] = team_queue.size() - 1;
    } else {
        // id所处的team在队列中，我们就直接一个插队
        // BUG: 这里错了。team_index是队伍的索引，不是当前team在queue中的索引
        // 还是这个问题！！！看来queue和index确实不和，应该寻找更好的
        team_queue[team_table[team_index]].push(id);
    }
}

auto dequeue() -> int {
    // 出队相当简单了
    // 我们直接找到第一个队列的第一人 出队就ok了

    auto id = team_queue.front().front();
    team_queue.front().pop();

    // 如果出完对之后，这个队列空了，那么整体的队列出去一个
    // 然后还要更新响应的team table
    // BUG: 这里错了！！！
    // 因为我们出队的时候，所有目前在队列中的队伍的index都要减去一
    // 所以记录队列的index然后利用这个信息是非常容易发生bug的
    // 应该有更好的方法TODO
    if (team_queue.front().empty()) {
        team_queue.pop_front();

        auto team_index = id_table[id];
        team_table[team_index] = -1;
        for (auto& team_index : team_table) {
            if (team_index != -1) {
                team_index--;
            }
        }
    }
    return id;
}

void run_team_queue(int team_count) {
    // 在每个测试开始时，清空状态
    team_queue.clear();
    // teams.clear();
    team_table.clear();
    id_table.clear();

    // TIP
    // 这样的坏处就是会修改team_count的值，有可能带来意想不到的bug
    for (int team_index = 0; team_index < team_count; team_index++) {
        // auto team = std::vector<int>{};

        int member_count = 0;
        std::scanf("%d", &member_count);
        while (member_count--) {
            int id = 0;
            std::scanf("%d", &id);
            // team.push_back(id);
            id_table.insert({id, team_index});
        }

        // teams.push_back(team);
        // -1 表示当前队列中没有该team的成员在排队
        team_table.push_back(-1);
    }

    // 然后开始读取动作并执行动作
    // 因为动作里面直接提供的是id 为了防止每次都遍历队列搜索
    // 我们需要建立一个id到队列index的映射
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
            // printf("ENQUEUE %d\n", id);
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