// 2024/10/27
// zhanghzong

// 如果假设舔屏从零点开始挂的话，
// 整个天平的宽度就是最大的石头的坐标减去最小的石头的坐标 为了保证精度 我们使用
// double

// 无语了，我们的程序不仅不对 而且很慢。。。

#include <iomanip>
#include <iostream>

static const int max_stone_count = 8;

class MobileComputing {
  public:
    MobileComputing() { ReadAndInit(); }

    void ReadAndInit() {

        double width = 0.0;
        int stone_count = 0;
        std::cin >> width >> stone_count;

        this->room_width_ = width;
        this->stone_count_ = stone_count;

        for (int i = 0; i < stone_count; i++) {
            double weight = 0.0;
            std::cin >> weight;
            this->stone_weights_[i] = weight;
        }
    }

    void Solve() {

        // 现在看起来A数组并没有什么用啊
        // 是不是我们想错了呢？

        // 其实我们仍然可以从左向右来填充A数组

        bool stones[max_stone_count] = {};
        for (int i = 0; i < this->stone_count_; i++) {
            stones[i] = true;
        }
        this->dfs(0.0, stones, this->stone_count_, 0);
    }

    // 为了防止运算出问题，统一使用double吧
    // 其实不用放right_stones
    // 我们需要的是当前可用的石头，和放在左边的石头
    // 通过这两个就可以计算出放在右边的石头，这样就不用填这个参数了
    // 那我请问什么事当前可用的石头？不就是没有visited过的石头吗？
    // could_use_stones表示在本次枚举中，可用的节点
    // left_stones表示枚举到左侧的节点
    // cur表示已经枚举的数量
    // left_stone_count表示需要枚举到左侧的节点
    // 不行，我们不能使用一个整形数组来保存左侧的节点，虽然两者应该都可以实现类似的功能，但是咱们其他地方都用的bool数组，所以这里也用bool数组吧

    // 不对！枚举使用的cur和我们dfs使用的cur是两个变量，应该分别存储
    void EnumerateStones(bool* could_use_stones, int left_stone_count,
                         bool* left_stones, int cur, double middle_point,
                         bool* visited, int dfs_cur) {

        if (cur == left_stone_count) {
            // 如果左边的石头都枚举出来了
            // 那么剩下没有被visited的石头就是放在右边的
            // 我们需要在这里统计一下，天平是否可能是平衡的

            // 但是问题是我们怎么方便的找出被放在左边的石头和被放在右边的石头呢

            // get the right stones sum

            // 我们有的时候并不能使用所有的石头
            // 我们当前可以使用的石头应该都被标注出来
            // 也就是使用一个left_stones
            // right_stones 数组来标注出来

            // 使用一个数组标记出右侧的节点
            // 也就是 could_use_stones - left_stones
            bool right_stones[max_stone_count] = {};
            for (int i = 0; i < max_stone_count; i++) {
                right_stones[i] = false;
            }
            for (int i = 0; i < this->stone_count_; i++) {
                // 如果是不能使用的石头，放弃掉
                if (!could_use_stones[i]) {
                    continue;
                }

                // 如果是已经放在左侧的石头，放弃掉
                if (left_stones[i]) {
                    continue;
                }

                // 放到右边的石头里面
                right_stones[i] = true;
            }

            // 计算左侧和右侧的石头的重量
            double left_stone_weight = 0.0;
            double right_stone_weight = 0.0;
            int right_stone_count = 0;
            for (int stone = 0; stone < stone_count_; stone++) {
                if (right_stones[stone]) {
                    right_stone_weight += this->stone_weights_[stone];
                    right_stone_count += 1;
                }
                if (left_stones[stone]) {
                    left_stone_weight += this->stone_weights_[stone];
                }
            }

            // now we get the left stone weight and right stone weight
            // try to calculate the coordinate
            double left_len =
                left_stone_weight / (left_stone_weight + right_stone_weight);

            // left_len的范围需要在0到1之间
            if (left_len < 1.0 && left_len > 0.0) {
                // 只有在这里，我们可以组成一个天平
                // 左侧使用节点 left_stones
                // 右侧使用节点 right_stones

                // 那这样我们就可以继续递归调用函数来组织天平了

                // 在这里我们是知道stone count的
                dfs(middle_point - left_len, left_stones, left_stone_count,
                    dfs_cur);
                // 大概就是这样的一个逻辑
                dfs(middle_point + (1 - left_len), right_stones,
                    right_stone_count, dfs_cur + left_stone_count);

                // 要不我们在这里做判断吧
                // 因为dfs结束了之后，就表示cur之前的stone的坐标都标注好了
                // 那么在这里，只要 cur + left_stone == this->stone_count - 1
                // 就说明我们有了一次成功的枚举
                if (dfs_cur + left_stone_count == this->stone_count_ - 1) {

                    // 如果所有的石头都用完了
                    // 找出所有石头的最大值和最小值
                    // 宽度就是这个
                    double min = 999999;
                    double max = -999999;
                    for (int s = 0; s < this->stone_count_; s++) {
                        if (this->stone_coordiantes_[s] < min) {
                            min = this->stone_coordiantes_[s];
                        }
                        if (this->stone_coordiantes_[s] > max) {
                            max = this->stone_coordiantes_[s];
                        }
                    }

                    double width = max - min;
                    if (width > this->max_width_ &&
                        width <= this->room_width_) {
                        this->max_width_ = width;
                    }

                    // 我这么写好像也是不对的呀，我们没有办法比较不同的排列呀！！！
                    //
                }
            }

            return;
        }

        for (int i = 0; i < this->stone_count_; i++) {
            // 如果这块石头不能用 跳过
            if (!could_use_stones[i]) {
                continue;
            }
            // 现在的问题就变成了，怎么正确的枚举石头
            // visited不能使用了
            // could use
            // 如果已经枚举过了，跳过
            if (visited[i]) {
                continue;
            }

            // 放到左侧的石头中
            left_stones[i] = true;
            visited[i] = true;
            EnumerateStones(could_use_stones, left_stone_count, left_stones,
                            cur + 1, middle_point, visited, dfs_cur);
            left_stones[i] = false;
            visited[i] = false;
        }
    }

    // 但是问题来了，递归结束条件在那里？
    // 在递归时，我们还要时刻知道当前天平中点
    // 并且我们还需要计算出来天平的宽度，这个要如何计算
    // 要不把这个A给去掉，我们总是用不着这个数组
    void dfs(double middle_point, bool* stones, int stone_count, int dfs_cur) {

        // stones 数组中保存着我们可以使用的石头

        // if (cur == this->stone_count_) {
        //     // 只有当所有的stone都被赋予了正确的
        // }

        if (stone_count == 1) {
            // 如果stonecount只有1的时候，我们就知道，我们该怎么摆了
            int stone = -1;
            for (int s = 0; s < this->stone_count_; s++) {
                if (stones[s]) {
                    stone = s;
                }
            }

            // mark the stones coordiante
            this->stone_coordiantes_[stone] = middle_point;

            // 我们怎么知道
            return;
        }

        // 虽然有两个石头留下的情况也可以编写，但是为了程序更加简单，还是只写只有一个石头留下的时候当作递归结束条件吧
        // } else if (stone_count == 2) {
        //     // 如果stone_count 只有两个，我们也知道该怎么摆
        //     // 但是关键是，我们怎么知道石头都摆完了
        //     // 这个时候可以使用一个 int& 或者一个全局变量
        //     // 我们就知道石头是不是用完了
        // }

        // 这一部分，或许可以移动到Enumeration里面，要正确的使用cur指针!
        // 当只有一个石头的时候，就是递归结束的时候

        // for (int i = 1; i <= stone_count / 2; i++) {
        // 应该还要枚举对称的情况！
        // 现在答案就对了，但是不知道会不会超时
        // 卧槽！这么复杂的程序我TM都能写出来，无敌了！
        for (int i = 1; i <= stone_count - 1; i++) {
            // i 表示在天平的左边放多少个
            // cur - i 就表示在天平的右边放多少个

            // 然后呢，从剩下的石头中选出可以让天平平衡的模式
            // 只要存在一个数是的 x * left_stones = (1-x)*right_stones就ok了

            // 现在开始枚举左边的石头

            // 不对啊，
            // 这里要做的就是从可用的石头中 枚举i个出来

            // 要先枚举，枚举结束之后
            // 枚举i个出来作为当前middle_point的左侧石头，剩下的作为右侧的石头
            EnumerateStonesV2(stones, i, stone_count - i, middle_point,
                              dfs_cur);
        }
    }

    void EnumerateStonesV2(bool* stones, int left_stone_count,
                           int right_stone_count, double middle_point,
                           int dfs_cur) {

        // 这里用循环写吧 不用递归写了 不太容易写出来

        // 要么就枚举本身使用递归写
        // 但是返回到这里的时候
        // 我们已经使用两个数组，分别保存了左侧可以使用的节点和右侧可以使用的节点

        bool left_stones[max_stone_count];
        // 如果在这里加入一个visited 数组来辅助实现相应的枚举功能呢
        // 应该是ok的
        bool visited[max_stone_count] = {};
        for (int i = 0; i < max_stone_count; i++) {
            visited[i] = false;
            left_stones[i] = false;
        }
        EnumerateStones(stones, left_stone_count, left_stones, 0, middle_point,
                        visited, dfs_cur);
        // 不对啊，这样只是一组可用的石头啊，实际上我们会产生多组可用的石头，所以这个函数实际上必须是一个递归函数
        // 在递归结束时，他会获得一组可以放在左边的石头，

        // 我们假设上面这个函数会正确的枚举出left_stone_count个可用的石头
        // 那么剩下的可用的石头就是当前可用的石头减去left_stone
        // int right_stones[max_stone_count];
    }

    void PrintSolution() {
        std::cout << std::setprecision(17) << this->max_width_ << std::endl;
    }

  private:
    double max_width_ = -1;
    double stone_weights_[max_stone_count] = {};
    int stone_count_;
    // 保存在递归过程中 那些石头已经用过了
    // bool visited_[max_stone_count] = {};
    // 保存已经放置的石头的位置
    double stone_coordiantes_[max_stone_count] = {};

    double room_width_ = 0.0;
};

int main() {

    // 现在还剩下两个问题
    // 一个是怎么提高 double的输出精度
    // 题目要求的精度0.00000001 应该是包含在double里面的
    // https://en.cppreference.com/w/cpp/io/manip/setprecision
    // 第二个问题是边界条件的测试，先解决第一个吧
    // [[TPIS]]
    // 想到一个增加单元测试的方法，我们修改一下该测试集中的石头的顺序，其结果不应该发生改变
    // 如果改变了，就说明我们的程序不对
    // 最极端的情况就是顺序完全相反，我们测试一下

    int test_case_count = 0;
    std::cin >> test_case_count;

    for (int i = 0; i < test_case_count; i++) {

        // 接下来就是stone count个石头

        auto mc = MobileComputing();
        mc.Solve();
        mc.PrintSolution();
    }
}