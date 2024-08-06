// 2024/8/6
// zhangzhong

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstring>
#include <iterator>
#include <map>
#include <set>
#include <stack>
#include <utility>
#include <vector>

// 不对，不应该叫container
// C++20给这个东西起了名字 叫做range！
#define range(c) c.begin(), c.end()

using namespace std;

using Set = set<int>;

auto memory = vector<Set>{};
auto addr_table = map<Set, int>{};
// 这里的set Stack就是直接保存地址就ok了
auto set_stack = stack<int>{};

auto buffer = array<char, 16>{};

auto get_addr(const Set& s) -> int {
    auto it = addr_table.find(s);
    if (it != addr_table.end()) {
        return it->second;
    }
    return -1;
}

auto new_set(const Set& s) -> int {
    auto addr = get_addr(s);
    if (addr != -1) {
        return addr;
    }

    memory.push_back(s);
    addr = static_cast<int>(memory.size() - 1);
    // BUG: 这里忘记了登记addr table啊
    addr_table.insert({s, addr});
    return addr;
}

void push() { set_stack.push(new_set(Set{})); }

void dup() { set_stack.push(set_stack.top()); }

auto pop_two_set() -> pair<int, int> {
    auto s1 = set_stack.top();
    set_stack.pop();
    auto s2 = set_stack.top();
    set_stack.pop();

    return make_pair(s1, s2);
}

void do_union() {
    auto sets = pop_two_set();

    // 两个集合的交要如何做？
    auto s1 = memory[sets.first];
    auto s2 = memory[sets.second];
    // 这样可以取出两个集合来
    // 然后这两个集合做交不久ok了吗！！！
    // 原来如此，这样是插入到vector中，需要使用back inserter
    // auto r = vector<int>{};
    // set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(r));

    // 而像这样插入集合中，直接使用insert即可
    auto rs = Set{};
    set_union(range(s1), range(s2), inserter(rs, rs.begin()));

    // now r contains the set ids, and make this to a new set
    // and insert into set stack
    set_stack.push(new_set(rs));
}

void intersect() {
    auto sets = pop_two_set();

    auto s1 = memory[sets.first];
    auto s2 = memory[sets.second];
    // 这样可以取出两个集合来
    // 然后这两个集合做交不久ok了吗！！！
    auto r = vector<int>{};
    set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(),
                     back_inserter(r));

    // now r contains the set ids, and make this to a new set
    // and insert into set stack
    set_stack.push(new_set(Set{r.begin(), r.end()}));
}

void add() {
    auto sets = pop_two_set();

    // add the first set to the second one
    auto first = memory[sets.first];
    auto second = memory[sets.second];

    // 不行啊 我们的内存必须是不能直接修改的
    // 只能copy 也就是这里不能直接insert必须先复制
    // 否则会影响后续的判断

    auto ns = Set{second};
    ns.insert(sets.first);

    // union the two sets
    set_stack.push(new_set(ns));
}

void run_set_stack_computer() {
    int instruction_count = 0;
    scanf("%d", &instruction_count);

    for (int _ = 0; _ < instruction_count; _++) {
        scanf("%s", buffer.data());
        auto instruction = string{buffer.data()};

        if (instruction == "PUSH") {
            push();
        } else if (instruction == "DUP") {
            dup();
        } else if (instruction == "UNION") {
            do_union();
        } else if (instruction == "INTERSECT") {
            intersect();
        } else {
            add();
        }

        // get the top set
        auto top_set_addr = set_stack.top();
        // get the element number of the set
        auto top_set = memory[top_set_addr];
        printf("%ld\n", top_set.size());
    }
    printf("***\n");
}

int main() {
    int test_count = 0;
    scanf("%d", &test_count);

    for (int _ = 0; _ < test_count; _++) {
        run_set_stack_computer();
    }
}