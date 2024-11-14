// 2024/11/14
// zhangzhong

#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
    int case_count = 0;

    std::cin >> case_count;

    for (int c = 0; c < case_count; c++) {
        if (c != 0) {
            std::cout << "\n";
        }

        // 数字比较大 需要使用int64_t

        int number_count = 0;
        std::cin >> number_count;
        // 我们有四个集合 A B C D
        std::vector<int64_t> A;
        std::vector<int64_t> B;
        std::vector<int64_t> C;
        std::vector<int64_t> D;
        A.reserve(number_count);
        B.reserve(number_count);
        C.reserve(number_count);
        D.reserve(number_count);

        for (int _ = 0; _ < number_count; _++) {
            int a = 0;
            int b = 0;
            int c = 0;
            int d = 0;
            std::cin >> a >> b >> c >> d;
            A.push_back(a);
            B.push_back(b);
            C.push_back(c);
            D.push_back(d);
        }

        // 遍历AB 并且建立哈希表
        // 哈希表的元素就是 {a, b}
        // 没有 我们只需要输出有多少组 不需要输出具体的组 所以不用保存了
        // 只需要保存个数就行了
        // std::unordered_map<int64_t,
        //                    std::forward_list<std::pair<int64_t, int64_t>>>
        //     ab;

        std::unordered_map<int64_t, int> ab;

        for (int a : A) {
            for (int b : B) {
                // 我们就保存 a + b 吧
                // 但是问题是 我们的 a + b 可能有重复的
                // 所以需要使用 multimap
                // 但是我还真忘了这个multimap怎么使了
                ab[a + b]++;
            }
        }

        int count = 0;
        for (int c : C) {
            for (int d : D) {

                auto iter = ab.find(0 - c - d);
                if (iter == ab.end()) {
                    continue;
                }

                count += iter->second;
            }
        }

        // 最后一个只有一个空格
        // 所以
        std::cout << count << "\n";
    }

    // 突然意识到我可以用 unordered_map + forward_list 来达成我的目的。。。
    // return 0;
}

// int main() {
//     std::multimap<int, std::string> m;

//     m.insert({1, "a"});
//     m.insert({1, "b"});

//     auto it = m.find(1);
//     // 只会输出a 也就是还不能用。。。
//     std::cout << it->second << std::endl;
// }