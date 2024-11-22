// 2024/11/21
// zhangzhong
// 卧槽TMD 一遍过！

#include <iostream>
#include <vector>

int main() {

    const int MAX_TIME = 201;
    const int MAX_STATION = 50;

    for (int case_id = 1;; case_id++) {
        int station_count = 0;
        std::cin >> station_count;
        if (station_count == 0) {
            break;
        }

        int appointment_time = 0;
        std::cin >> appointment_time;

        std::vector<int> travel_times(station_count - 1, 0);
        for (int s = 0; s < station_count - 1; s++) {
            int travel_time = 0;
            std::cin >> travel_time;
            travel_times[s] = travel_time;
        }

        // to right train
        int train_count = 0;
        std::cin >> train_count;
        std::vector<int> to_right_trains(train_count, 0);
        for (int t = 0; t < train_count; t++) {
            int depart_time = 0;
            std::cin >> depart_time;
            to_right_trains[t] = depart_time;
        }

        // to left trains
        std::cin >> train_count;
        std::vector<int> to_left_trains(train_count, 0);
        for (int t = 0; t < train_count; t++) {
            int depart_time = 0;
            std::cin >> depart_time;
            to_left_trains[t] = depart_time;
        }

        // 接下来就是计算在任何时刻，是否有向右 或者 向左 的火车

        // std::vector<bool> has_to_right_train(appointment_time + 1, false);
        // 我们怎么知道在某一时刻 那个车站有车呢？
        // 我们就看某一辆车
        // 所有的车都不会在中间车站停车
        // 所以车在第一个车站停留的时间内，不对 我们也不可以上车
        // 某辆车会在某个时刻突然出现在车站上，此时我们是可以上车的
        // 对于第一辆车
        // to_right_trains[0], 对应的时刻，我们就是有向右的车的
        // has_to_right_train[to_right_trains[0]] = true;
        // 然后这辆车每次到站的时候，除了最后一站，我们都是可以向右的
        // 而为了得到这些时间，我们需要遍历traveltime数组
        // int depart_time = to_right_trains[0];
        // has_to_right_train[depart_time] = true;
        // for (int station = 0; station < station_count - 1; station++) {
        //     depart_time += travel_times[station];
        //     // 还要处理越界
        //     if (depart_time >= has_to_right_train.size()) {
        //         break;
        //     }
        //     has_to_right_train[depart_time] = true;
        // }

        // 而对于所有的列车都有同样的逻辑, 所以实际上上面的代码是一个双层循环
        bool has_to_right_train[MAX_TIME][MAX_STATION];
        // 首先将所有位置初始化为false
        for (int time = 0; time <= appointment_time; time++) {
            for (int station = 0; station < station_count; station++) {
                has_to_right_train[time][station] = false;
            }
        }

        for (int depart_time : to_right_trains) {
            // int depart_time = to_right_trains[0];
            has_to_right_train[depart_time][0] = true;
            for (int station = 0; station < station_count - 1; station++) {
                depart_time += travel_times[station];
                // 还要处理越界
                if (depart_time > appointment_time) {
                    break;
                }
                has_to_right_train[depart_time][station + 1] = true;
            }
        }

        // 同理，我们需要计算出在每个时刻是否有向左的车
        // std::vector<int> has_to_left_train(appointment_time + 1, false);
        bool has_to_left_train[MAX_TIME][MAX_STATION];
        for (int time = 0; time <= appointment_time; time++) {
            for (int station = 0; station < station_count; station++) {
                has_to_left_train[time][station] = false;
            }
        }

        for (int depart_time : to_left_trains) {
            has_to_left_train[depart_time][station_count - 1] = true;
            // 现在我们需要倒着遍历station了
            for (int station = station_count - 2; station >= 0; station--) {
                depart_time += travel_times[station];
                // 还要处理越界
                if (depart_time > appointment_time) {
                    break;
                }
                has_to_left_train[depart_time][station] = true;
            }
        }

        // 然后我们就开始计算状态了 做dp了
        // 这是一个二维的状态(time, station)
        // 当前的时间，和目前所在的车站

        // [[TIPS]] 不要思考我们是怎么到达当前的时间，和所在的车站的
        // dp的具体状态转移路径并不重要，主要的是状态在一步之内如何转移
        // 以及状态的计算顺序
        //
        // 这是一个二维的dp，对于每一个状态，我们有三种选择
        // 1. 在这个车站等一会
        // 2. 可以向左坐车
        // 3. 可以向右坐车
        // 无论如何，时间都会流逝
        // 可以写出状态转移方程
        // min_waiting_time[time, station] = min(min_wating_time[time+1,
        // station], min_wating_time[time+x, station-1], min_wating_time[time+y,
        // station+1]) 可以很明显的看到 time 依赖于 其他的 更大的time
        // 这就告诉了我们计算的方向，从最大的time开始计算，并且在计算time-1时，time所对应的一行（全部车站）的状态都要计算出来
        // 这就是一个很明显的双层循环的模式
        // 外层循环从大到小循环time
        // 内层循环遍历所有的车站
        //
        // 再次重申，不要去思考某个状态是如何达到的，他可能根本就达不到
        // 这就是我们的INF的trick，我们的INF不可以设定成INT_MAX,
        // !!![[因为我们在编写代码时，假设所有的状态都能达到]]!!!
        // 此时INF就会增加，如果他是int max，就会溢出
        // 正确的做法是设定一个极大的值，但是考虑最长的路径也不会导致溢出
        // 最终如果确实无解，那么dp[0][0]处的值应该 >= INF

        int INF = 1 << 20;

        int min_waiting_time[201][50];
        // 一般而言，dp数组最初始的状态都是直接根据题目推导出来的
        // 在最后的时刻，我们只有停留在最后的车站才是对的，此时的等待时间是零
        // 在所有其他的车站都是错误的状态，应该设置为INF
        for (int station = 0; station < station_count; station++) {
            min_waiting_time[appointment_time][station] = INF;
        }
        min_waiting_time[appointment_time][station_count - 1] = 0;

        for (int time = appointment_time - 1; time >= 0; time--) {
            for (int station = 0; station < station_count; station++) {

                // 这里 取一个引用 代码更直观
                int& mwt = min_waiting_time[time][station];
                // [[BUG]]
                // 注意此时的数组是没有赋值的
                // 我们不能直接进行大小的比较
                // 比较不容易出错的方式是给整个min_waiting_time赋予初始值INF
                // 但是这里有一个trick
                // 就是因为我们有一个选择是在当前车站等上一分钟
                // 这句代码可以充当赋予初始值的效果
                mwt = min_waiting_time[time + 1][station] + 1;

                // 哦，我们上面的数组求错了
                // 应该是一个二维数组的。。。
                if (has_to_left_train[time][station] &&
                    time + travel_times[station - 1] <= appointment_time &&
                    station - 1 >= 0) {
                    // 如果我们在此刻有向左的火车，则我们可以坐上这个火车
                    // 坐上这个火车后可以跳转到下一个状态
                    // 因为火车只有到车站才会停车
                    // 所以时间需要加上从station -> station-1的时间
                    // time + travel_times[station-1]
                    // 如果是向右的火车 就是 time + travel_times[station]
                    // 了，就不需要-1了
                    // [[BUG]]
                    // 这里对 min_wating_time的访问是可能越界的
                    // 需要检查 time + travel_times[station - 1] <=
                    // appointment_time 才行
                    mwt = std::min(
                        mwt, min_waiting_time[time + travel_times[station - 1]]
                                             [station - 1]);
                }
                // 这里不需要else哦 所有的分支都要走
                // 上面的状态转移方程写的很清楚了
                if (has_to_right_train[time][station] &&
                    time + travel_times[station] <= appointment_time &&
                    station + 1 < station_count) {
                    mwt = std::min(
                        mwt, min_waiting_time[time + travel_times[station]]
                                             [station + 1]);
                }
            }
        }

        // 最终我们可以得到输出
        // 是否有效的判断条件就是 min_wating_time[time=0][station=0] >= INF
        // output
        std::cout << "Case Number " << case_id << ": ";
        if (min_waiting_time[0][0] >= INF) {
            std::cout << "impossible\n";
        } else {
            std::cout << min_waiting_time[0][0] << "\n";
        }
    }
}
