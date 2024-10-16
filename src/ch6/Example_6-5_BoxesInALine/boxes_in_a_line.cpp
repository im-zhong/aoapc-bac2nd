// 2024/10/15
// zhangzhong

// case 2 contain bug
// 我猜测大概就是op4之后再进行其他的操作可能回不对，但是没想到程序直接卡住了，明天调试一下吧

#include <cstdint>
#include <iostream>
#include <vector>

struct ListNode {
    struct ListNode* prev;
    struct ListNode* next;
    int box_id;
};

void insert_between(ListNode* prev, ListNode* node, ListNode* next) {
    prev->next = node;
    node->prev = prev;

    node->next = next;
    next->prev = node;
}

void insert_after(ListNode* prev, ListNode* node) {
    insert_between(prev, node, prev->next);
}

void insert_before(ListNode* node, ListNode* next) {
    insert_between(next->prev, node, next);
}

void erase_between(ListNode* prev, ListNode* next) {
    prev->next = next;
    next->prev = prev;
}

void erase(ListNode* node) { erase_between(node->prev, node->next); }

void swap_adjacent(ListNode* prev, ListNode* next) {
    auto prev_prev = prev->prev;
    auto next_next = next->next;

    prev_prev->next = next;
    next->prev = prev_prev;

    next_next->prev = prev;
    prev->next = next_next;

    next->next = prev;
    prev->prev = next;
}

void swap(ListNode* node1, ListNode* node2) {

    // node1 和 node2 必须没有任何直接相连的关系？

    if (node1->next == node2) {
        swap_adjacent(node1, node2);
    } else if (node2->next == node1) {
        swap_adjacent(node2, node1);
    } else {
        // node1 node2 do not adjacent

        auto node1_prev = node1->prev;
        auto node2_prev = node2->prev;

        erase(node1);
        erase(node2);

        insert_after(node1_prev, node2);
        insert_after(node2_prev, node1);
    }
}

void print(ListNode* head, ListNode* tail) {
    for (auto work = head->next; work != tail; work = work->next) {
        std::cout << work->box_id << ", ";
    }
    // use call fun(...) in lldb
    // if you want to see your output, must flush by std::flush or std::endl
    std::cout << std::endl;
}

void print_reverse(ListNode* head, ListNode* tail) {
    for (auto work = tail->prev; work != head; work = work->prev) {
        std::cout << work->box_id << ", ";
    }
    std::cout << std::endl;
}

int main() {
    auto head = ListNode{nullptr, nullptr, 0};
    auto tail = ListNode{nullptr, nullptr, 0};
    head.prev = head.next = &tail;
    tail.prev = tail.next = &head;

    int case_id = 0;
    while (true) {
        // init the list
        head.prev = head.next = &tail;
        tail.prev = tail.next = &head;
        bool is_reversed = false;
        int boxes_count = 0;
        int commands_count = 0;

        if (!(std::cin >> boxes_count >> commands_count)) {
            return 0;
        }

        case_id++;

        // 实例化一个链表 contain 1 -> boxes_count
        // auto boxes = std::list<int>{};
        // create an array to store the pointer to each node

        auto boxes_indicies = std::vector<ListNode*>{};
        for (int i = 1; i <= boxes_count; i++) {
            // create a new node
            // and insert into the list
            auto node = new ListNode{nullptr, nullptr, i};
            insert_before(node, &tail);
            boxes_indicies.push_back(node);
        }

        for (int i = 0; i < commands_count; i++) {
            int op = 0;
            int x = 0;
            int y = 0;

            std::cin >> op;
            if (op != 4) {
                std::cin >> x >> y;
            }

            if (is_reversed) {
                if (op == 1) {
                    op = 2;
                } else if (op == 2) {
                    op = 1;
                }
            }

            auto x_it = boxes_indicies[x - 1];
            auto y_it = boxes_indicies[y - 1];

            // then we implement the op
            switch (op) {
            case 1: {
                if (x_it->next == y_it) {
                    break;
                }

                // std::list
                // 果然实现不了，它需要把这个节点提取出来，然后在插入到对应的地方
                // 我们需要自己实现list的操作

                // first erase x from the list
                erase(x_it);

                // then insert this node before the y
                insert_before(x_it, y_it);

                break;
            }
            case 2: {
                if (y_it->next == x_it) {
                    break;
                }

                // first erase x from the list
                erase(x_it);
                // then insert after the y
                insert_after(y_it, x_it);

                break;
            }
            case 3: {
                // how to swap two nodes?
                swap(x_it, y_it);

                break;
            }
            case 4: {
                is_reversed = !is_reversed;

                break;
            }
            }
        }

        // traverse the list
        // count the odd number and sum its box_id
        int i = 1;
        // [[TIPS]] 整数和容易溢出，数据类型整大一点
        uint64_t sum = 0;
        if (is_reversed) {
            for (auto work = tail.prev; work != &head; work = work->prev) {

                if (i % 2 != 0) {
                    sum += work->box_id;
                }
                i++;
            }
        } else {
            for (auto work = head.next; work != &tail; work = work->next) {
                if (i % 2 != 0) {
                    sum += work->box_id;
                }
                i++;
            }
        }

        std::cout << "Case " << case_id << ": " << sum << std::endl;
    }
}