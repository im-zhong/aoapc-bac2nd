// 2024/11/27
// zhangzhong

#include <vector>

int LIS(const std::vector<int>& nums) {

    // 这是一道一维的dp题目
    // 有两种对称的状态定义方法
    // length[i]表示以i开头的最长上升子序列
    // 初始:length[n] = 0
    // 计算顺序：倒着算
    // 转移：length[i] = max{0, 1+ length[j] where j>i, Aj > Ai}
    // 这里题目要求的严格递增的，如果不是严格的 把 > 换成 >= 就行
    // 答案:因为并不一定按照以最后一个结尾的子序列最长，所以需要遍历一遍length，找到最大的数
    // 同理，我们可以对称的给出
    // length[i] 表示以i结尾的最长上升子序列
    // 初始 length[0] = 1
    // 计算顺序，正着算
    // 转移 length[i] = max {1, 1 + length[j] where j < i and Aj < Ai}
    // 答案同样需要遍历一遍length数组
    //
    // 如果我们需要打印出答案，可以想象到在内存循环遍历的时候，我们会找到一个1 +
    // length[j] 或者 1 使用一个next数组保存每次的选择即可,
    // 保存当前索引i或者-1表示起始位置

    // 这里我们按照第二种状态给出代码
    std::vector<int> length(nums.size(), 1);

    for (int i = 0; i < nums.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) {
                length[i] = std::max(length[i], 1 + length[j]);
            }
        }
    }

    return *std::max_element(length.begin(), length.end());
}

int main() {}