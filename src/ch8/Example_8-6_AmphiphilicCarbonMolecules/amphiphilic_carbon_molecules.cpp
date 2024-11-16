// 2024/11/16
// zhangzhong

// 刷题上的目标就是 书上的例题都完成，leetcode top150
// 完成，三本算法书上的东西都看完，就ok了
// 大概会分成三个项目，本项目，leetcode项目，算法项目
// 追加可视化内容和完美注释！
// 只用C++刷

#include <iostream>
#include <vector>

// 这两个单词也太相似了，反而容易写错
// 咱们就改成TYPE_A, TYEP_B ?
// 或者 TYPE_0, TYPE_1
enum ParticalType {
    TYPE_0 = 0,
    TYPE_1 = 1,
};

// 隔板上的点可以看作在任意一侧！
// 目标是让：隔板一侧的白色点 加上 另一侧的黑色点 + 隔板上的所有点 最大即可
// ok 我已经完全懂了
// 咱们先写一个O(N^3)的算法

struct Partical {
    int x;
    int y;
    int type;
};

struct Vector {
    int64_t x;
    int64_t y;

    int64_t DotProduct(const Vector& other) const noexcept {
        return this->x * other.x + this->y * other.y;
    }

    int64_t CrossProduct(const Vector& other) const noexcept {
        return this->x * other.y - this->y * other.x;
    }
};

// 还可以写一个函数
Vector MakeVector(const Partical& from, const Partical& to) {
    return Vector{
        to.x - from.x,
        to.y - from.y,
    };
}

int GetMaximumParticalCount(const std::vector<Partical>& particals) {

    int maximum_count = -1000000;
    // 最简单的方法来枚举两个不同的点
    for (int i = 0; i < particals.size(); i++) {
        for (int j = i + 1; j < particals.size(); j++) {

            // v1 = i -> j

            // v2 = i -> other point

            //
            Vector v1 = MakeVector(particals[i], particals[j]);

            // 然后我们就要遍历所有以i为起点，以其他所有点为终点(不含j)的向量与v1的位置关系
            // 不过其实我觉得也不用排除
            // 我们直接指定三个集合
            // 上侧 CrossProduct > 0
            // 共线 CrossProduct = 0
            // 下侧 CrossProduct < 0
            // 同时，这些在上侧和下侧的点 我们还要区分两种类型 type 0 type 1,
            // 所以需要使用两个计数器

            int above_type0 = 0;
            int above_type1 = 0;
            int online = 0;
            int below_type0 = 0;
            int below_type1 = 0;

            // 遍历所有点的同时，也会遍历原点，而与零向量的叉积是零 所以是ok的
            for (const Partical& partical : particals) {
                Vector v2 = MakeVector(particals[i], partical);

                int64_t cp = v1.CrossProduct(v2);
                if (cp > 0) {
                    if (partical.type == 0) {
                        above_type0++;
                    } else {
                        above_type1++;
                    }
                } else if (cp < 0) {
                    if (partical.type == 0) {
                        below_type0++;
                    } else {
                        below_type1++;
                    }
                } else {
                    // cp == 0
                    online++;
                }
            }

            // 现在我们拿到了以 i ,j 两个点为分隔的点的分布情况
            // 只需要统计一下两侧的点的数量即可
            // 考虑两种对称的情况
            int count = above_type0 + below_type1 + online;
            if (count > maximum_count) {
                maximum_count = count;
            }

            count = above_type1 + below_type0 + online;
            if (count > maximum_count) {
                maximum_count = count;
            }
        }
    }

    return maximum_count;
}

int main() {
    int partical_count = 0;

    while (std::cin >> partical_count) {
        if (partical_count == 0) {
            break;
        }

        // 我们使用一个vector来保存所有的点
        std::vector<Partical> particals;

        // x, y 代表的是坐标
        int x = 0;
        int y = 0;
        // r 代表的是类型 0 or 1
        // 我们使用一个枚举吧
        int r = 0;

        for (int i = 0; i < partical_count; i++) {
            std::cin >> x >> y >> r;
            particals.push_back(Partical{x, y, r});
        }

        int count = GetMaximumParticalCount(particals);
        std::cout << count << "\n";
    }
}