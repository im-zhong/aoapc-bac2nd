// 2024/12/2
// zhangzhong

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

constexpr int max_n = 256;

void dfs(int root, int* dpu, int* dps, bool* uniu, bool* unis,
         const std::vector<std::vector<int>>& adjs, int n) {

    // 两种情况
    // 叶子
    if (adjs[root].empty()) {
        // 叶子
        dpu[root] = 0;
        // 不论如何，不论我们选或者不选叶子，名单都是唯一的
        uniu[root] = true;
        dps[root] = 1;
        unis[root] = true;
        return;
    }

    // 下面这整个三个循环都可以写到一起

    for (int employee : adjs[root]) {
        dfs(employee, dpu, dps, uniu, unis, adjs, n);
    }

    // 关键就是这里，我们怎么知道名单是不是唯一的呢？

    // 所有child都弄完了
    // 那么我们来计算 dpu[root] and dps[root]
    // dpu = sum of childs max{u, s}
    dpu[root] = 0;
    uniu[root] = true;
    for (int employee : adjs[root]) {
        dpu[root] += std::max(dpu[employee], dps[employee]);

        if (dpu[employee] > dps[employee]) {
            uniu[root] &= uniu[employee];
        } else if (dps[employee] > dpu[employee]) {
            uniu[root] &= unis[employee];
        } else {
            uniu[root] &= false;
        }
    }

    // dps = sum of childs dpu, 因为我们选了自己 child就都不能选了
    dps[root] = 1;
    unis[root] = true;
    for (int employee : adjs[root]) {
        dps[root] += dpu[employee];

        unis[root] &= uniu[employee];
    }
}

std::pair<int, bool> MIS(const std::vector<std::vector<int>>& adjs, int n) {

    // 咱们先不管uniquely这个 先找出MIS
    int dpu[max_n];
    int dps[max_n];
    bool uniu[max_n];
    bool unis[max_n];

    dfs(0, dpu, dps, uniu, unis, adjs, n);
    // 因为root是0
    //
    if (dpu[0] > dps[0]) {
        return {dpu[0], uniu[0]};
    } else if (dps[0] > dpu[0]) {
        return {dps[0], unis[0]};
    } else {
        return {dpu[0], false};
    }

    // return {std::max(dpu[0], dps[0]), dpu[0] != dps[0]};
}

// 我们插入一个名字之后，还会返回他的索引
// 这样我们正好可以建立adjs 邻接链表
int InsertName(const std::string& name,
               std::unordered_map<std::string, int>& name_to_index,
               std::vector<std::string>& names) {

    auto iter = name_to_index.find(name);
    if (iter != name_to_index.end()) {
        return iter->second;
    }

    names.push_back(name);
    int index = names.size() - 1;
    name_to_index[name] = index;
    return index;
}

int main() {
    // 我们做的第一步就是把string转成index
    // 使用一个哈希表即可

    int n = 0;
    while (std::cin >> n) {
        if (n == 0) {
            break;
        }

        // reset the environment
        // name_to_index.clear();
        // names.clear();
        std::unordered_map<std::string, int> name_to_index;
        std::vector<std::string> names;

        // get big boss name
        std::string name;
        std::cin >> name;
        InsertName(name, name_to_index, names);

        std::vector<std::vector<int>> adjs(n);
        // get the employee name
        for (int i = 0; i < n - 1; i++) {
            std::string employee_name;
            std::string boss_name;

            std::cin >> employee_name >> boss_name;

            // 首先检查某个名字是否没有出现过
            // 这一段显然可以写成一个函数
            int boss_index = InsertName(boss_name, name_to_index, names);
            int employee_index =
                InsertName(employee_name, name_to_index, names);
            adjs[boss_index].push_back(employee_index);
        }

        std::pair<int, bool> result = MIS(adjs, n);
        std::cout << result.first << " ";
        if (result.second) {
            std::cout << "Yes\n";
        } else {
            std::cout << "No\n";
        }
    }
}