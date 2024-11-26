// 2024/11/26
// zhangzhong

#include <iostream>
#include <vector>

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
        const int max_stage = 50;
        // stage从0开始
        // 最多有50首歌，每首歌3分钟(180s)，不考虑劲歌金曲（因为一定会在最后选择)
        // 所以最大的时间就是 50 * 180 =
        const int max_time = 50 * 180;
        int max_song_count[max_stage][max_time];
        int max_song_time[max_stage][max_time];

        // 路径要怎么保存呢？
        // 在任何一个节点 我们都只有两个选择
        // 我们只需要记录在任意一个节点 我们选择了那个节点就行了
        // 然后我们就可以从最右下角的节点倒着回去找到完整的路径
        // 我尝试的好几种做法都是错的 只有这样才是对的

        // 关键是要如何表示
        // 因为我们的状态转换总是从stage到下一个stage
        // 只有行会变化 所以我们只需要记录行就行了
        int prev_row[max_stage][max_time];

        int mst2 = 0;

        for (int stage = 0; stage < song_count; stage++) {
            // max_time = remain_time - 1
            for (int time = 0; time < remain_time; time++) {

                // 不对呀，到底应该是什么？
                // 如果值考虑唱的长度，那么
                // 不对啊，我么应该一块考虑！
                // 也就是我们需要准备两个数组
                // 在更新的时候同时更新着两个状态数组
                // 然后剩下的逻辑都是一样的
                // 唯一的不同就是，本来我们的实现里不是有一个比较吗
                // 就是当前的max和新的max的比较
                // 那个比较函数就变成一个自定义的比较函数，用来按照两个约束条件进行比较
                // 1. 先比较曲目数量，如果曲目数量更多，显然更好
                // 2. 如果曲目数量相同，再比较唱的时间，越长越好
                // 吼！尝试一下

                if (stage == 0) {
                    max_song_count[stage][time] = 0;
                    max_song_time[stage][time] = 0;
                } else {
                    max_song_count[stage][time] =
                        max_song_count[stage - 1][time];

                    prev_row[stage][time] = time;

                    max_song_time[stage][time] = max_song_time[stage - 1][time];
                }

                // 拿到引用
                int& msc = max_song_count[stage][time];
                int& mst = max_song_time[stage][time];

                // 如果当前的时间允许我们唱这首歌
                if (song_times[stage] <= time) {
                    // 咱们先不想别的了，咱们就分别把两个约束条件都独立的求出来

                    // 那是不是说，只有我们更新了，下面的唱歌时间才能更新呢？
                    // [[BUG]]
                    // 我简直是天才
                    // 哪怕唱的曲目的数量相同，时间也可能更长，所以这里是>=我们就要进行更新
                    if (1 + max_song_count[stage - 1]
                                          [time - song_times[stage]] >
                        msc) {
                        msc =
                            1 +
                            max_song_count[stage - 1][time - song_times[stage]];

                        choose_song[stage] = true;

                        prev_row[stage][time] = time - song_times[stage];

                        // 还有一个方法就是我们只记录我们选择的路径上的权
                        // 问题来了，在背包问题中，我们怎么知道我们选择了哪些歌呢？
                        //
                        // 只要到了这里 应该就是选了这首歌了吧

                        // 关键是这么更新对吗？
                        // 如果只考虑一个解的话 这里累积就行了
                        mst = std::max(
                            mst, song_times[stage] +
                                     max_song_time[stage - 1]
                                                  [time - song_times[stage]]);
                    } else if (1 + max_song_count[stage - 1]
                                                 [time - song_times[stage]] ==
                               msc) {

                        if (song_times[stage] +
                                max_song_time[stage - 1]
                                             [time - song_times[stage]] >
                            mst) {

                            mst = song_times[stage] +
                                  max_song_time[stage - 1]
                                               [time - song_times[stage]];

                            prev_row[stage][time] = time - song_times[stage];
                        }
                    }
                    // msc = std::max(
                    //     msc, 1 + max_song_count[stage - 1]
                    //                            [time - song_times[stage]]);

                    // 现在最关键的问题就是，这两个东西求出来的可能不是一个东西
                    // 第二个东西的求解收到第一个条件的限制
                }
            }
        }

        // 我懂了，应该就是遍历一遍所有stage的最大的时间
        // 如果变化了，说明这首歌就被选了
        int last = 0;
        int mst3 = 0;
        // 不对，这样遍历是不对的
        // 应该从最后倒着开始遍历，然后减去对应的时间，搜寻路径
        // 关键的问题是，我们怎么知道它在这里有没有选这首歌呢？
        for (int stage = 0; stage < song_count; stage++) {
            if (max_song_count[stage][remain_time - 1] > last) {
                mst3 += song_times[stage];
            }
            last = max_song_count[stage][remain_time - 1];
        }

        // 还是不对
        int mst4 = 0;
        for (int stage = 0; stage < song_count; stage++) {
            if (choose_song[stage]) {
                mst4 += song_times[stage];
            }
        }

        // 用这些方法都不对
        // 打印路径大概还是要在算法途中保存路径才行

        int mst5 = 0;
        int time = remain_time - 1;
        for (int stage = song_count - 1; stage >= 0; stage--) {
            int pr = prev_row[stage][time];
            if (pr == time) {
                // 如果剩余的时间没变，说明我们没有选这首歌

            } else {
                // 说明我们选了这首歌
                mst5 += song_times[stage];
            }

            time = pr;
        }

        int mst = max_song_time[song_count - 1][remain_time - 1] + 11 * 60 + 18;
        // int mst = remain_time - 1 + 11 * 60 + 18;
        int msc = max_song_count[song_count - 1][remain_time - 1] + 1;

        std::cout << "Case " << c << ": " << msc << " " << mst5 + 11 * 60 + 18
                  << "\n";
    }
}