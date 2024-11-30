// 2024/11/30
// zhangzhong

#include <iostream>
#include <string>

constexpr int max_length = 128;
constexpr int inf = 1 << 30;

struct Index {
    int i;
    int j;

    bool IsStop() const noexcept { return i == j || i + 1 == j; }
};

void PrintDP(int dp[max_length][max_length], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << dp[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void AnalyzeRegular(int dp[max_length][max_length],
                    int prev[max_length][max_length], bool* array, int i, int j,
                    int n) {
    if (i >= j) {
        return;
    }

    // 只有单个字符的需要考虑
    if (i + 1 == j) {
        array[i] = true;
        return;
    }

    // stop point

    int k = prev[i][j];
    if (k == -1) {
        i = i + 1;
        j = j - 1;
        AnalyzeRegular(dp, prev, array, i, j, n);
    } else {
        // 需要在递归中保存所有需要修改的下标到一个数组中
        // 然后对这个数组进行排序
        // 用一个bool数组就不用排序了
        // 然后遍历这个数组 逐一考虑输出合适的字符

        // i,k
        AnalyzeRegular(dp, prev, array, i, k, n);
        AnalyzeRegular(dp, prev, array, k, j, n);
    }
}

std::string MakeRegular(const std::string& text) {

    int dp[max_length][max_length] = {};
    // 初始条件
    // dp[i][i] = 0
    // dp[i][i+1] = 1
    // dis: 2 -> n
    int prev[max_length][max_length] = {};

    // 目前dp对了 但是还需要打印方案
    // 把整个dp的转移过程想象成一个DAG
    // 那么从1,n 开始 逐渐转移到边界条件 i,i or i,i+1 即可
    // 我们需要一个prev数组来表示每个节点转向了哪个位置
    // 实际上如果是case1 我们根本不需要记录转移 因为这样一定更优？
    // 也不对 如果是 [][] 此时走case1就不是最优的
    // 因为每次跳转到下一个状态需要保存两个数字 i j
    // 所以实际上prev是一个结构体数组

    int n = text.size();
    for (int i = 0; i + 1 <= n; i++) {
        dp[i][i + 1] = 1;
    }

    // 因为空字符串和单个字符的字符串都是结束条件
    // 所以用一个-1, -1 表示
    // 但是也可以使用下标来判断 所以不用考虑也行

    for (int dis = 2; dis <= n; dis++) {
        for (int i = 0; i + dis <= n; i++) {
            int j = i + dis;
            dp[i][j] = inf;
            int& d = dp[i][j];

            // 接下来只需要记录每次最优的跳转即可

            // case 1: (S) or [S]
            // then transfer to dp[i+1][j-1]
            if ((text[i] == '(' && text[j - 1] == ')') ||
                (text[i] == '[' && text[j - 1] == ']')) {
                if (d > dp[i + 1][j - 1]) {
                    d = dp[i + 1][j - 1];
                    // prev[i][j] = Index{i + 1, j - 1};
                    // 我们用-1表示向中间缩小
                    prev[i][j] = -1;
                }
                // dp[i][j] = std::min(dp[i][j], dp[i + 1][j - 1]);
            }

            // case 2
            // if len[i..=j] j - i + 1 >= 2, which is always true
            // then S = AB
            // 也就是我们用 i < k < j 来判断
            // dp[i][j] = min{ dp[i][k] + dp[k+1][j] }
            for (int k = i + 1; k < j; k++) {
                if (d > dp[i][k] + dp[k][j]) {
                    d = dp[i][k] + dp[k][j];
                    // 不对，其实我们要记录的就是我们需要处理哪个位置的单个字符就行
                    // 所以实际上prev只需要记录一个k
                    prev[i][j] = k;
                }
                // dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
    }

    // 现在prev弄好了，怎么打印呢？
    // 感觉需要递归了呀

    bool a[max_length] = {};

    AnalyzeRegular(dp, prev, a, 0, n, n);

    std::string result;
    for (int i = 0; i < n; i++) {
        if (a[i]) {
            // 说明这个字符需要额外考虑
            if (text[i] == '(' || text[i] == ')') {
                result.append("()");
            } else {
                result.append("[]");
            }
        } else {
            result.push_back(text[i]);
        }
    }

    // return std::to_string(dp[0][n]);
    return result;
}

int main() {

    int case_count = 0;
    // 读数字并不会读入数字之后的会车！
    std::cin >> case_count;
    std::string newline;
    std::getline(std::cin, newline);
    std::getline(std::cin, newline);

    for (int c = 0; c < case_count; c++) {
        // 傻逼格式啊 还好我坚信我的代码没有写错
        if (c != 0) {
            std::cout << "\n";
        }
        std::string line;
        std::getline(std::cin, line);
        std::getline(std::cin, newline);

        std::string regular = MakeRegular(line);
        std::cout << regular << "\n";
    }
}