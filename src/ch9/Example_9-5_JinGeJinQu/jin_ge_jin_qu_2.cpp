// 2024/11/26
// zhangzhong

#include <cassert>
#include <iostream>
#include <ostream>
#include <vector>

// 定义一个结构体
// 这道题目应该就是普通的01背包加上多约束条件
// 多约束条件就是用结构体

struct node {
    int song_count;
    int sing_time;

    node() : song_count(0), sing_time(0) {}

    node(int m, int n) : song_count(m), sing_time(n) {}

    // 关键是定义比较函数
    // friend bool operator<(const node& lhs, const node& rhs) {
    //     return lhs.song_count < rhs.song_count ||
    //            (lhs.song_count == rhs.song_count &&
    //             lhs.sing_time < rhs.sing_time);
    // }
    friend bool operator>(const node& lhs, const node& rhs) {
        return lhs.song_count > rhs.song_count ||
               (lhs.song_count == rhs.song_count &&
                lhs.sing_time > rhs.sing_time);
    }

    friend std::ostream& operator<<(std::ostream& out, const node& n) {

        out << n.song_count << ", " << n.sing_time;
        return out;
    }
};

int main() {
    int case_count = 0;

    std::cin >> case_count;

    for (int c = 1; c <= case_count; c++) {
        int song_count = 0;
        int remain_time = 0;

        std::cin >> song_count >> remain_time;

        std::vector<int> song_times(song_count, 0);
        for (int s = 0; s < song_count; s++) {
            std::cin >> song_times[s];
        }

        std::vector<bool> choose_song(song_count, false);

        // print maximum number of songs
        // and the total lenghts of songs
        // all including Jin Ge Jin Qu

        // int max_song_count = 0;
        // int max_sing_time = 0;

        // 我们需要同时维护两个约束条件
        // 一个是曲目的数量 这个是首位的约束条件
        // 然后是唱的时间

        // 主要约束条件作为状态
        // 01背包
        // max_song_count[stage][time]
        // 表示已经超过了(stage-1)首歌，还剩time的时间，在这种情况下，我们最多还能唱几首歌
        // 那么答案就是max_song_count[song_count][max_time]
        // 因为我们必须要给劲歌金曲留出至少1s时间，所以max_time = remain_time-1
        // 同时考虑这个数组的界，因为最多有n=50首歌
        const int max_stage = 50 + 10;
        // stage从0开始
        // 最多有50首歌，每首歌3分钟(180s)，不考虑劲歌金曲（因为一定会在最后选择)
        // 所以最大的时间就是 50 * 180 =
        // [[BUG]]
        // 我TM的终于知道是为什么了 怎么会有这么奇怪的bug
        // 原来是这个数组不够长！！！
        const int max_time = 50 * 180 + 11 * 60 + 18 + 10;
        // int max_song_count[max_stage][max_time];
        // int max_song_time[max_stage][max_time];

        // 有更快的解法，就是变成一维的 滚动数组
        // 我这里写成二维的也可能超时
        node dp[max_stage][max_time];

        // 路径要怎么保存呢？
        // 在任何一个节点 我们都只有两个选择
        // 我们只需要记录在任意一个节点 我们选择了那个节点就行了
        // 然后我们就可以从最右下角的节点倒着回去找到完整的路径
        // 我尝试的好几种做法都是错的 只有这样才是对的

        // 关键是要如何表示
        // 因为我们的状态转换总是从stage到下一个stage
        // 只有行会变化 所以我们只需要记录行就行了
        // int prev_row[max_stage][max_time];

        // int mst2 = 0;

        for (int stage = 0; stage < song_count; stage++) {
            // max_time = remain_time - 1
            for (int time = 0; time < remain_time; time++) {

                // 拿到引用
                // int& msc = max_song_count[stage][time];
                // int& mst = max_song_time[stage][time];

                if (stage == 0) {
                    dp[stage][time] = node{};
                } else {
                    dp[stage][time] = dp[stage - 1][time];
                }

                // 如果当前的时间允许我们唱这首歌
                if (song_times[stage] <= time) {

                    // dp[stage - 1][time - song_times[stage]].song_count + 1;
                    // dp[stage - 1][time - song_times[stage]].sing_time +
                    //     song_times[stage];

                    // [[BUG]]
                    // 这里当stage时零的时候，我们不应该访问stage-1
                    if (stage == 0) {

                        // 其实和第一列全是零的效果一样
                        dp[stage][time] = node{1, song_times[stage]};

                    } else {
                        // node tmp{};
                        // tmp.song_count =
                        //     dp[stage - 1][time -
                        //     song_times[stage]].song_count + 1;
                        // tmp.sing_time =
                        //     dp[stage - 1][time - song_times[stage]].sing_time
                        //     + song_times[stage];
                        node tmp = dp[stage - 1][time - song_times[stage]];

                        bool ok = tmp.song_count == 1;
                        tmp.song_count += 1;
                        tmp.sing_time += song_times[stage];

                        if (ok && tmp.song_count == 3) {
                            std::cout << "bug?\n";
                        }
                        assert(tmp.song_count <= stage + 1);
                        if (tmp > dp[stage][time]) {

                            // 在这里输出一下吧 受不了了 数值太大 没法debug

                            // 不对 我们设置一个if就可以debug了呀
                            if (stage == 1 && tmp.song_count == 3) {
                                std::cout << "wft\n";
                            }

                            dp[stage][time] = tmp;
                        }
                    }
                }

                // 肯定是在某个循环之后我们不小心把dp给改了
                // 我们在这里对dp进行验证
                // for (int s = 0; s < stage; s++) {
                //     for (int t = 0; t < remain_time; t++) {
                //         assert(dp[s][t].song_count <= s + 1);
                //     }
                // }
            }
        }

        int msc = dp[song_count - 1][remain_time - 1].song_count + 1;
        int mst = dp[song_count - 1][remain_time - 1].sing_time + 11 * 60 + 18;

        std::cout << "Case " << c << ": " << msc << " " << mst << "\n";
    }
}