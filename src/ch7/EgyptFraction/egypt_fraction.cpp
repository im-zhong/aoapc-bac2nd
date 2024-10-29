// 2024/10/29
// zhangzhong

// 迭代深度 + 回溯
// for + dfs

#include <cstdint>
#include <iostream>

static const int MAX_DEPTH = 100;
static const int MIN_DEPTH = 1;

uint64_t gcd(uint64_t a, uint64_t b) { return b == 0 ? a : gcd(b, a % b); }

class EgyptFraction {
  public:
    EgyptFraction(uint64_t a, uint64_t b) : numerator_{a}, denominator_{b} {

        for (int i = 0; i < MAX_DEPTH; i++) {
            // 其实不用非得是-1， 0也是可以的
            this->answer_[i] = -1;
            this->solution_[i] = -1;
        }
    }

    void Solve() {

        // 在这里就是写一个循环
        // 最开始最大的深度应该从1开始，因为我们有的情况下 深度1就有解
        // 1/3 = 1/3
        // 不是的！
        // 后面的加式不能和前面的分数一样，哪怕分子是1
        // 所以最少最少也得有两个分数
        // 所以maxd 最小应该是2

        // 因为深度不会特别大，所以使用int就ok
        // 但是参与计算的数字是有可能溢出的 所以全部使用 64 bit

        bool ok = false;
        for (int depth = MIN_DEPTH; depth <= MAX_DEPTH; depth += 1) {

            // 每次迭代都去算那个解就行了

            // 一旦在某一个深度找到解，就不再继续寻找了
            if (dfs(depth, 0, this->solution_,
                    this->GetClosestDenominator(this->numerator_,
                                                this->denominator_),
                    this->numerator_, this->denominator_)) {
                ok = true;
                break;
            }
        }

        this->has_solved_ = ok;
        // return ok;
    }

    uint64_t GetClosestDenominator(const uint64_t numerator,
                                   const uint64_t denominator) {
        return (denominator / numerator) + 1;
    }

    bool dfs(const int max_depth, const int current_depth,
             uint64_t* const solution, const uint64_t min_denominator,
             const uint64_t numerator, const uint64_t denominator) {

        // [[TIPS]]
        // 我知道为什么这一题的递归结束会和之前的回溯法不一样了
        // 这是由于数字的性质导致的
        // 一般我们用回溯法，到这里的时候，solution里面已经有完整的解
        // 但是在本题中，solution的最后一个解要在这个分支里面继续计算出来
        // 所以maxdepth 要从1开始算
        // 但是在用的时候要当2来算 也就是 max_depth + 1
        // 为的就是解的最后一个分数要在结束分支这里面计算
        // 否则下面算gcd的时候会有零参与, 确认一下
        // 好像gcd是可以处理分子是零的情况的
        // 所以知道到这里的时候分子是零，就表示我们的solution中是正确的

        if (current_depth == max_depth) {
            // 回溯递归边界

            // 一般来说，我们在这里是找到了解
            // 那么我们就得有一个保存解的地方

            // 在每次递归中，我们找到的都是可行解 solution
            // 但是不一定是最优解 answer

            // 在 solution[0:max_depth] 中保存着我们一个可行解
            //
            // 我们需要对比可行解和我们的最优解
            // 如果可行解比最优解还要好 那么就更新answer

            // 不管是answer还是solution
            // 假设在初始化时都会全部初始化为-1

            // [[TIPS]]
            // 虽然深度是 max depth
            // 但是我们不一定直到此深度才能找到解吧？
            // 不是的，因为深度是一点一点的增加的
            // 在探索下一个深度之前，之前的深度一定都探索结束了
            // 所以解一定会在到达当前最大允许深度的时候找到
            // 而找到解，程序就结束了，
            // 综上所述，解一定会在当前最大深度被找到！

            // 如果此时还没有最优解
            // 就是answer[i] = -1 ! 原来如此
            // 如果此时已经有了最优解，只需要比较我们的solution的分母是否更小(意味着分子更大)

            // 不对啊！！！我们这是递归的算法
            // solution是一点一点填充起来的
            // 对的对的，对吗？

            // 不对的，我们的剪枝策略非常简单，哪怕我们枚举到这个深度，我们的答案也不一定是对的
            // 此时solution数组里面已经有了

            // if (numerator != 0) {
            //     // 说明当前的枚举不对
            //     return false;
            // }

            // 还是要把对最后一个数字的处理放到这里来，写起来才比较舒服
            // 那个剩下的分数就是 numerator / denominator
            // 因为我们在进来之前肯定经历过gcd
            // 所以如果能进行化简的话 numerator 一定是1
            // 否则就不对
            if (numerator != 1) {
                return false;
            }

            // 否则的话，就说明我们成功的进行化简了
            this->solution_[current_depth] = denominator;
            // 现在current depth 和max depth = answer lenght - 1
            this->answer_length_ = current_depth + 1;

            // 到了这里，我们的solution一定不可能有-1
            // answer时第一次，否则也不可能是-1
            if (this->answer_[0] == -1) {
                for (int i = 0; i < this->answer_length_; i++) {
                    this->answer_[i] = solution[i];
                }

                // } else {
                //     // answer和solution一定一样长
                //     // 在这种情况下，我们怎么说明solution比answer好呢？
                //     // 就是和式中最小的分数更大
                //     // 不论如何，和式中最小的分数出现在最后一个
                //     // 我们只需要比较最后一个分数即可
                //     if () {
                //         for (int i = 0; i < this->answer_length_; i++) {
                //             this->answer_[i] = solution[i];
                //         }
                //         this->answer_length_ = current_depth + 1;
                //     }
                return true;
            }

            for (int i = current_depth; i >= 0; i--) {
                if (solution[i] != this->answer_[i]) {
                    if (solution[i] < this->answer_[i]) {
                        // 是只要发现有小的就替换吗
                        // 也不是
                        // 是首先找到不相同的位
                        for (int i = 0; i < this->answer_length_; i++) {
                            this->answer_[i] = solution[i];
                        }
                    }

                    // 只要找到了第一个不同的就退出就行了
                    break;
                }
            }

            // 找到了解之后，返回true
            // 因为我们一旦找到解
            // 就不会在继续加大深度来搜索了
            return true;
        }

        // 现在需要继续迭代
        // 我们从哪里开始枚举呢
        // 从参数中给出的数字开始枚举（这是一个较大的分数）
        // 一只枚举到 在最乐观的情况下，max_depth - current_depth
        // 个分子加起来都达不到要求的分数时 就停止

        // 而对于每个每个枚举出来的分数
        // 计算 a/b-1/c=a/b
        // 然后深度加+1, 新的分母+1, 继续dfs
        // 知道找到解

        // 因为我们不能倒退，我们找到的cloest denominator可能比参数传入的
        // min_denominator要小
        // 如果我们真的从我们计算出来的closeest开始枚举的话，就可能发生重复枚举
        // 同时如果我们算出来的cloest要大，那么从参数传入的min_denominator开始枚举就会产生一写无效的枚举
        // 所以我们要从两者的最大值开始枚举

        bool ok = false;
        // [[TIPS]]
        // 不对啊
        // 我这样做确实是不对的
        // 如果是1/2, 那么在这种情况下，我们算出来的就是1/2
        // 如果我们此时只剩下一个空来填
        // 那么就应该填1/2
        // 但是如果我们有多余两个空
        // 那么就不能填
        // 这就导致写起来非常困难
        // 最后一个数字的判断有他额外的逻辑
        // 在这种情况下，确实把这些逻辑放到上面的递归结束分支里要更好
        for (uint64_t i =
                 std::max(min_denominator,
                          this->GetClosestDenominator(numerator, denominator));
             ; i++) {

            // 我们不知道i的边界，只知道枚举结束的条件
            // 等于是可以的，如果刚好是解，等号就会成立
            // 所以等号不应该在判断条件里面
            // 上面的讨论在我们换了写法之后就不再成立了
            // 等号绝对不能成立，因为我们不允许加数是相同的！
            if ((max_depth + 1 - current_depth) * denominator <=
                numerator * i) {
                break;
            }

            // 如果有可能，那么将答案放在solution数组里面
            solution[current_depth] = i;

            // 然后继续搜索
            // 哦
            // 还要计算出新的分数, 不对，应该叫做剩余的分数
            // a/b - 1/c = a'/b'
            uint64_t remain_numerator = numerator * i - denominator;
            uint64_t remain_denominator = denominator * i;
            // 将a'/b'进行化简
            uint64_t g = gcd(remain_numerator, remain_denominator);

            // bool ok = ;
            // 只要有一个ok的，整个函数的返回值就得是ok的
            // 卧槽我擦！！！
            // 这里的bug
            // [[BUG]]
            // 短路！！！！由于短路特性 导致后面的dfs根本不会执行
            // 只要找到了一个解 后面的dfs就都不会执行了
            // 太傻逼了，怎么会烦这种低级错误！！！
            // 以后不要写短路代码！！
            // 用等价的条件语句写就行
            bool result = dfs(max_depth, current_depth + 1, solution, i + 1,
                              remain_numerator / g, remain_denominator / g);
            ok = ok || result;
        }
        return ok;
    }

    void PrintSolution() {
        if (this->has_solved_) {

            std::cout << this->numerator_ << "/" << this->denominator_ << "=";
            for (int i = 0; i < this->answer_length_; i++) {
                if (i != 0) {
                    std::cout << "+";
                }

                std::cout << "1/" << this->answer_[i];
            }

        } else {
            std::cout << "No solution.";
        }
    }

  private:
    int answer_length_ = 0;
    bool has_solved_ = false;
    uint64_t answer_[MAX_DEPTH] = {};
    uint64_t solution_[MAX_DEPTH] = {};
    uint64_t numerator_ = 0;
    uint64_t denominator_ = 0;
};

int main() {

    uint64_t a = 0;
    uint64_t b = 0;

    int test_case_id = 1;
    while (std::cin >> a >> b) {

        //
        EgyptFraction ef{a, b};

        ef.Solve();

        // [[TODO]]
        // 这样写不好，因为输出的整体逻辑被拆分了
        // 一部分在主函数，另一部分在类里面
        // 最好的情况就是要么都在类里面，要么都在主函数里面
        // 比较简单的写法是把所有逻辑都迁移到类里面
        // 也就是类需要一个额外的参数，test case id
        // 如果所有的输出逻辑都在外面
        // 那么类必然要多写一些getter setter来返回一些内部私有的东西
        // 这样就比较麻烦
        //
        // 用类的好处是什么？
        // 不用声明全局变量
        // 每个test case都有自己的实例，不会发生两个test
        // case之间忘了reset变量的情况
        std::cout << "Case " << test_case_id << ": ";
        ef.PrintSolution();
        std::cout << std::endl;

        test_case_id += 1;
    }
}