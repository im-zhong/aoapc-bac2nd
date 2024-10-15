// 2024/9/5
// zhangzhong

#include <array>
#include <deque>
// 感觉stdio实在是不太好使，要不就不用了吧
// 还是多用用cin cout吧
// 如果确实速度慢了，有专门的代码可以加快速度
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

enum class StatementType {
    Assignment = 0,
    Output = 1,
    BeginMutualExclusion = 2,
    EndMutualExclusion = 3,
    StopExecution = 4,
};

constexpr int statement_count = 5;

char buffer[256] = "\0";
// 对于所有的变量 还要有一个全局的符号表
auto symbol_table = std::array<int, 26>{};
bool is_locked = false;

// now we need to run all these programs
// we use two queues:
// 1. ready queue
// 2. block queue
auto ready = std::deque<int>{};
auto block = std::queue<int>{};

struct ExecuteResult {
    StatementType statement_type;
    bool is_error;
};

// 指令执行结束之后，应该返回一个状态
// 这样我们的执行器可以根据不同的状态继续执行
// 比如我们的某条指令被lock了 那么我们必须立刻切换
// 这里需要返回两个东西，一个是执行的statementtype 另一个表示是否成功执行
ExecuteResult execute_statement(int program_id, const std::string& statement) {

    auto statement_type = StatementType{};
    auto is_error = false;

    auto op = std::string{};
    // 首先解析是那条命令
    auto ss = std::stringstream{statement};
    auto command_or_variable = std::string{};
    ss >> command_or_variable;
    if (command_or_variable == "print") {
        statement_type = StatementType::Output;
        auto variable = std::string{};
        ss >> variable;
        std::cout << program_id + 1 << ": " << symbol_table[variable[0] - 'a']
                  << "\n";
    } else if (command_or_variable == "lock") {
        statement_type = StatementType::BeginMutualExclusion;
        if (!is_locked) {
            is_locked = true;
        } else {
            // 如果当前指令执行完毕之后需要切换，我们的pc不会往下+1
            // 仍然指向lock
            // 我们需要立刻结束当前程序的执行
            // 我们需要将当前程序放到block队列中
            block.push(program_id);
            is_error = true;
        }
    } else if (command_or_variable == "unlock") {
        statement_type = StatementType::EndMutualExclusion;
        is_locked = false;

        // move top of block stack to the ready queue front
        if (!block.empty()) {
            auto program_id = block.front();
            block.pop();
            ready.push_front(program_id);
        }

    } else if (command_or_variable == "end") {
        statement_type = StatementType::StopExecution;
    } else {
        statement_type = StatementType::Assignment;
        // variable
        auto variable = command_or_variable;
        ss >> op;
        auto value = 0;
        ss >> value;
        symbol_table[variable[0] - 'a'] = value;
    }

    return ExecuteResult{
        statement_type,
        is_error,
    };
}

void simulate_concurrency() {

    // 在最开始初始化所有的状态
    // 全局变量真不是个好东西啊
    // 果然就是这里
    // [[TIPS]] 不同的case之间要注意重置全局的状态啊！
    for (auto& symbol : symbol_table) {
        symbol = 0;
    }
    is_locked = false;
    ready.clear();
    while (!block.empty()) {
        block.pop();
    }

    int program_count = 0;
    std::cin >> program_count;

    auto execution_times = std::array<int, statement_count>{0};

    for (int i = 0; i < statement_count; i++) {
        int execution_time = 0;
        std::cin >> execution_time;
        execution_times[i] = execution_time;
    }

    int quantum = 0;
    // after number, there is a newline, we must read it
    std::cin >> quantum;
    std::cin.ignore(100, '\n');
    // std::scanf("%d\n", &quantum);

    // read all programs
    // we use id -> list of string to represent programs

    // 读完数字时候，之后的回车
    auto programs = std::vector<std::vector<std::string>>{};
    for (int i = 0; i < program_count; i++) {
        programs.push_back({});

        auto statement = std::string{};
        while (true) {
            // std::fgets(buffer, sizeof(buffer), stdin);
            // reads characters until a newline character is found, and the
            // newline character is extracted but not stored in the resulting
            // string.
            std::getline(std::cin, statement);
            programs[i].push_back(statement);
            if (statement == "end") {
                break;
            }
        }
    }

    auto pcs = std::vector<int>{};
    // 对于所有的程序 他们的pc都是从0开始的
    for (int i = 0; i < program_count; i++) {
        pcs.push_back(0);
    }

    ready.clear();
    while (!block.empty()) {
        block.pop();
    }

    // initialize ready qeuue
    for (int i = 0; i < program_count; i++) {
        ready.push_back(i);
    }

    // now run all these queues
    while (!ready.empty()) {

        // 在每个迭代周期，我们做的事情就是从ready队列队首取出一个程序
        // 然后按照顺序执行
        // 我们还需要一个东西来指示所有的程序执行到那条指令了
        // 也就是类似于pc寄存器

        auto program_id = ready.front();
        ready.pop_front();

        // 开始执行直到quantum不够了
        int current_quantum = quantum;
        // 只要quantum》0 我们就要执行执行
        bool blocked = false;
        while (current_quantum > 0) {
            auto pc = pcs[program_id];
            const auto& statements = programs[program_id];
            if (pc >= statements.size()) {
                break;
            }

            const auto& statement = statements[pc];
            // parse this statement and execute it
            // this deserve a function
            auto result = execute_statement(program_id, statement);
            if (result.is_error) {
                blocked = true;
                break;
            }

            // 还需要一个东西，就是当前指令所消耗的quantum time
            // 比较简单的方法是返回那个枚举类型
            // 但是如果如此 我们要如何
            current_quantum -=
                execution_times[static_cast<int>(result.statement_type)];
            pcs[program_id] += 1;
        }

        // 我们在执行结束之后，应该继续排队吧
        // 只要我们的pc没有结束
        // 哪怕我们还可以执行 只要我们在block队列中
        // 我们都不应该再添加到ready队列中了
        if (!blocked) {
            if (pcs[program_id] < programs[program_id].size()) {
                ready.push_back(program_id);
            }
        }
    }
}

int main() {
    int case_count = 0;
    std::cin >> case_count;

    for (int i = 0; i < case_count; i++) {
        simulate_concurrency();
        if (i < case_count - 1) {
            std::cout << "\n";
        }
    }
}
