// 2024/10/19
// zhangzhong

#include <cstdint>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

// hash need operator== and hash<T>
struct Triplet {
    int row;
    int col;
    char dir;

    // friend could not be static and const
    friend bool operator==(const Triplet& lhs, const Triplet& rhs) noexcept {
        return lhs.row == rhs.row && lhs.col == rhs.col && lhs.dir == rhs.dir;
    }
};

// template <>
// struct _LIBCPP_TEMPLATE_VIS hash<int> : public __unary_function<int, size_t>
// {
//   _LIBCPP_HIDE_FROM_ABI size_t operator()(int __v) const _NOEXCEPT { return
//   static_cast<size_t>(__v); }
// };
namespace std {
template <> struct hash<Triplet> {
    uint64_t operator()(const Triplet& triplet) const noexcept {
        return std::hash<int>{}(triplet.row) ^ std::hash<int>{}(triplet.col) ^
               std::hash<char>{}(triplet.dir);
    }
};
} // namespace std

// TIPS: 所有dir没有意义的triplet中，dir统一位0
class ArrowMaze {

  public:
    ArrowMaze() { ReadMaze(); }

    std::vector<Triplet> WalkThrough() {
        // 还有一种可能，如果起点就是终点呢?
        // [[BUG]] 在这种带方向的迷宫中这是不可能的
        // 因为我们有方向，我们不可能在起点指向自己
        // if (this->MeetGoal(this->entrance_)) {
        //     return {this->entrance_};
        // }

        // first visit entrance
        this->Visit(this->entrance_, Triplet{-1, -1, 0});

        // auto is_found = bool{false};
        bool is_found = false;
        while (!this->queue_.empty()) {
            const Triplet triplet = this->queue_.front();
            this->queue_.pop();

            // check where we should go
            Triplet next_step = this->Step(triplet);
            // first we should check that if we meet the goal
            if (this->MeetGoal(next_step)) {
                // TODO: we find a path !
                // 找到了goal之后，我们需要添加一个特殊的节点到visited中
                this->Visit(next_step, triplet);
                is_found = true;
                break;
            }
            // then we should check the next proper dir according to the map

            Triplet key = Triplet{next_step.row, next_step.col, triplet.dir};
            auto iter = this->maze_.find(key);
            // 我们找到了一个无法继续向前的path 我们应该跳出吗
            // 应该继续吧，因为接下来队列中可能还有其他路可以走啊
            if (iter == this->maze_.end()) {
                // we could not find the proper path
                // just return {}
                continue;
            }

            // then we check what direction we could go
            // for each direction, if we do not visited it, push it in the queue
            for (const char turn : iter->second) {
                // cause this direction is L F R
                // we should convert it into N S E W
                // the current direction is triplet.dir
                next_step.dir = this->TurnDirection(triplet.dir, turn);
                // TODO: next step should be able to visit
                // if we go to wrong, 我们可能走向一个不存在的迷宫节点
                // 这个也是应该检测的！
                if (this->HasVisited(next_step)) {
                    continue;
                }

                this->Visit(next_step, triplet);
                // 我们还要做一件事情，当我们visit一个节点的时候，我们必然需要知道他的parent节点
                // 这个也可以在visit里面做
            }
        }

        if (!is_found) {
            return {};
        }

        // from the goal 一直到entrance
        return this->GetPath();
    }

  private:
    std::vector<Triplet> GetPath() {
        auto path = std::vector<Triplet>{};

        Triplet triplet = this->goal_;
        path.push_back(triplet);
        while (!this->MeetEntrance(triplet)) {
            // get the parent
            triplet = this->visited_.at(triplet);
            path.push_back(triplet);
        }

        return {path.rbegin(), path.rend()};
    }

    void Visit(const Triplet& triplet, const Triplet& parent) {
        // first mark this triplet as visited
        this->visited_.insert({triplet, parent});
        // and send this one in the queue
        this->queue_.push(triplet);
    }

    char TurnDirection(char direction, char turn) {

        // 我就知道 std::pair<char, char> 没有实现 hash
        // 那么我们换成 std::string 吧
        static auto converter = std::unordered_map<std::string, char>{
            {"NL", 'W'}, {"NF", 'N'}, {"NR", 'E'},

            {"SL", 'E'}, {"SF", 'S'}, {"SR", 'W'},

            {"EL", 'N'}, {"EF", 'E'}, {"ER", 'S'},

            {"WL", 'S'}, {"WF", 'W'}, {"WR", 'N'},
        };
        return converter[std::string{direction, turn}];
    }

    Triplet Step(const Triplet& triplet) {
        switch (triplet.dir) {
        case 'N':
            return Triplet{triplet.row - 1, triplet.col, 0};
        case 'S':
            return Triplet{triplet.row + 1, triplet.col, 0};
        case 'E':
            return Triplet{triplet.row, triplet.col + 1, 0};
        case 'W':
            return Triplet{triplet.row, triplet.col - 1, 0};
        default:
            return Triplet{};
        };
    }

    bool HasVisited(const Triplet& triplet) const {
        return this->visited_.find(triplet) != this->visited_.end();
    }

    bool MeetGoal(const Triplet& triplet) const {
        return (triplet.row == this->goal_.row &&
                triplet.col == this->goal_.col);
    }

    // 出来的时候有特定的方向，这一点很关键
    bool MeetEntrance(const Triplet& triplet) const {
        return (triplet.row == this->entrance_.row &&
                triplet.col == this->entrance_.col &&
                triplet.dir == this->entrance_.dir);
    }

    void ReadMaze() {

        // first read the entrance and goal and direction

        int row = 0;
        int col = 0;
        std::string direction;
        std::cin >> row >> col >> direction;
        this->entrance_ = Triplet{row, col, direction[0]};

        // read the goal
        std::cin >> row >> col;
        this->goal_ = Triplet{row, col, 0};

        // then read the whole maze, until the first number is zero
        while (true) {
            std::cin >> row;
            if (row == 0) {
                break;
            }
            std::cin >> col;

            while (true) {
                std::string word;
                std::cin >> word;
                if (word == "*") {
                    break;
                }

                // 可以用三元组的形式直接存储
                // key = Triplet, value = std::string
                maze_.insert({Triplet{row, col, word[0]},
                              std::string{word.begin() + 1, word.end()}});
            }
        }
    }

  private:
    Triplet entrance_;
    Triplet goal_;

    std::unordered_map<Triplet, std::string> maze_;
    std::unordered_map<Triplet, Triplet> visited_;
    std::queue<Triplet> queue_;
};

int main() {

    while (true) {
        auto name = std::string{};
        std::cin >> name;
        if (name == "END") {
            break;
        }

        // actually the maze do not need the name
        auto maze = ArrowMaze{};
        std::vector<Triplet> path = maze.WalkThrough();

        // print the maze name first
        std::cout << name << "\n";
        // then we just print out the path
        if (path.empty()) {
            std::cout << "  No Solution Possible\n";
        } else {
            // [[BUG]]:
            // 这个格式还TM是错的，写一个正确的每行输出10个正确代码这么困难吗？
            for (int i = 0; i < path.size(); i++) {
                if (i % 10 == 0) {
                    std::cout << "  ";
                }
                std::cout << "(" << path[i].row << "," << path[i].col << ")";
                if ((i + 1) % 10 == 0) {
                    std::cout << "\n";
                } else {
                    if (i != path.size() - 1) {
                        std::cout << " ";
                    }
                }
                // 但是这里有两个特例
                // 一个是如果我们是最后一个，那么我们不要输出空格
            }
            // 最后我们要输出回车
            // 但是如果我们的size刚好是10的倍数 也不要输出
            // 因为我们上面已经输出过了
            if (path.size() % 10 != 0) {
                std::cout << '\n';
            }
        }
    }
}
