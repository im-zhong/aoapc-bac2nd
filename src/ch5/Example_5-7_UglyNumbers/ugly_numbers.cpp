// 2024/8/8
// zhangzhong

#include <cstdint>
#include <cstdio>
#include <functional>
#include <queue>
#include <set>

// then for every ugly number
auto factors = std::array<uint64_t, 3>{2, 3, 5};

int main() {

    // default is big-top-heap
    auto pq = std::priority_queue<uint64_t, std::vector<uint64_t>,
                                  std::greater<uint64_t>>{};

    // use a hashmap to store all the ugly numbers
    auto ugly_numbers = std::set<uint64_t>{};

    pq.push(1);
    ugly_numbers.insert(1);

    // BUG
    // 卧槽！！！这里不对，不能在numbers刚好1500个的时候退出
    // 因为我们有可能跳过某些丑书，应该在pq队列一共出队1500次的时候退出
    // 那才是真正的第1500个丑书！！！
    for (int i = 1;; i++) {
        auto number = pq.top();
        pq.pop();
        ugly_numbers.insert(number);
        if (i == 1500) {
            printf("The 1500'th ugly number is %lld.\n", number);
            return 0;
        }
        // std::cout << ugly_numbers.size() << ": " << number << std::endl;

        for (auto factor : factors) {
            auto ugly_number = factor * number;

            // ugly_numbers.count(ugly_number);
            if (ugly_numbers.find(ugly_number) == ugly_numbers.end()) {
                // 必须要及时的插入，否则也也会导致程序运行时间过长
                pq.push(ugly_number);
                ugly_numbers.insert(ugly_number);
            }
        }
    }

    // auto nums = std::vector<uint64_t>{ugly_numbers.begin(),
    // ugly_numbers.end()}; std::sort(nums.begin(), nums.end()); for (int i = 0;
    // i < nums.size(); i++) {
    //     std::printf("%d: %lld\n", i, nums[i]);
    // }
}