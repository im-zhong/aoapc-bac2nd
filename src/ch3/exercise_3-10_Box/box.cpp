// 2024/7/30
// zhangzhong

#include <algorithm>
#include <cstdio>
#include <functional>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

struct Rectange {
    int width;
    int height;

    Rectange(int x, int y) {
        if (x <= y) {
            width = x;
            height = y;
        } else {
            width = y;
            height = x;
        }
    }

    friend bool operator==(const Rectange& lhs, const Rectange& rhs) {
        return lhs.width == rhs.width && lhs.height == rhs.height;
    }

    friend bool operator<(const Rectange& lhs, const Rectange& rhs) {
        if (lhs.width < rhs.width) {
            return true;
        } else if (lhs.width == rhs.width) {
            return lhs.height < rhs.height;
        } else {
            return false;
        }
    }
};

// specialize hash for rectangle
namespace std {
template <> struct hash<Rectange> {
    size_t operator()(const Rectange& rectangle) const {
        return hash<int>()(rectangle.width) ^
               hash<int>()(rectangle.height << 1);
    }
};
} // namespace std

bool is_box(const Rectange& rect1, const Rectange& rect2,
            const Rectange& rect3) {
    // we use rect1 as the query rect
    // we must found two edges in rect2 and rect3

    // 如果rect想要组成长方体
    map<int, int> edges;
    edges[rect1.width]++;
    edges[rect1.height]++;
    edges[rect2.width]++;
    edges[rect2.height]++;
    edges[rect3.width]++;
    edges[rect3.height]++;

    vector<int> numbers;

    // 这里还是有三种情况
    // if (edges.size() > 3) {
    //     return false;
    // }

    // if (edges.size() == 1) {
    //     return true;
    // }

    for (const auto edge : edges) {
        if (edge.second == 2) {
            numbers.push_back(edge.first);
        } else if (edge.second == 4) {
            numbers.push_back(edge.first);
            numbers.push_back(edge.first);
        } else if (edge.second == 6) {
            numbers.push_back(edge.first);
            numbers.push_back(edge.first);
            numbers.push_back(edge.first);
        } else {
            return false;
        }
    }

    if (numbers.size() != 3) {
        return false;
    }

    // 我们用排列组合的方式生成三个长方形
    // 他们需要和输入的长方形完全一样
    // 也就是说 我们需要给长方形定义顺序
    vector<Rectange> temp = {Rectange{numbers[0], numbers[1]},
                             Rectange{numbers[0], numbers[2]},
                             Rectange{numbers[1], numbers[2]}};

    vector<Rectange> temp2 = {rect1, rect2, rect3};

    sort(temp.begin(), temp.end());
    sort(temp2.begin(), temp2.end());
    for (int i = 0; i < 3; i++) {
        if (!(temp[i] == temp2[i])) {
            return false;
        }
    }
    return true;
}

int main() {

    // 我们不妨做一个假设
    // 我们让width <= lenght
    // 这好像会简化问题

    while (true) {
        unordered_map<Rectange, int> rectangles;
        // vector<Rectange> rectangles;

        int x = 0, y = 0;
        for (int i = 0; i < 6; i++) {
            // read the six edge of rectangle
            if (scanf("%d%d", &x, &y) != 2) {
                return 0;
            }

            // 不对！！！
            // 如果我们输入六个完全一样的正方形呢？
            auto rectangle = Rectange{x, y};
            // if we do not have this rectangle, insert it
            // if (find(rectangles.begin(), rectangles.end(), rectangle) ==
            //     rectangles.end()) {
            //     rectangles.push_back(rectangle);
            // }
            // rectangles.push_back(rectangle);

            // if (rectangles.find(rectangle) == rectangles.end()) {
            //     rectangles.insert({rectangle, 0});
            // }
            // [] 操作符会自动 零初始化 或者 默认初始化 不存在的元素
            // 所以上面的if是不需要的
            rectangles[rectangle]++;
        }

        // only when all the count of each class of rectangle is even
        // we could form a 长方体
        // for (const auto& pair : rectangles) {
        //     if (pair.second % 2 != 0) {
        //         printf("IMPOSSIBLE\n");
        //         continue;
        //     }
        // }

        // // 整体的种类绝对不会超过3
        // if (rectangles.size() > 3) {
        //     printf("IMPOSSIBLE\n");
        //     continue;
        // }

        // now we should pair the rectangle
        // 总共分成三种情况
        // 有一种图形
        // if (rectangles.size() == 1) {
        //     // 在此情况下，有且只有一种可能，我们是正方形
        //     auto rect = *rectangles.begin();
        //     if (rect.second == 6 && rect.first.width == rect.first.height) {
        //         printf("POSSIBLE\n");
        //     } else {
        //         printf("IMPOSSIBLE\n");
        //     }
        //     continue;
        // }

        // // 有两种图形
        // if (rectangles.size() == 2) {
        //     //
        // }

        // // 有三种图形

        // // we should have exactly three rectangles
        // if (rectangles.size() != 3) {
        //     printf("IMPOSSIBLE\n");
        //     continue;
        // }

        vector<Rectange> rects;

        for (const auto rect : rectangles) {
            if (rect.second == 2) {
                rects.push_back(rect.first);
            } else if (rect.second == 4) {
                rects.push_back(rect.first);
                rects.push_back(rect.first);
            } else if (rect.second == 6) {
                rects.push_back(rect.first);
                rects.push_back(rect.first);
                rects.push_back(rect.first);
            }
        }

        if (rects.size() != 3) {
            printf("IMPOSSIBLE\n");
            continue;
        }

        if (is_box(rects[0], rects[1], rects[2])) {
            printf("POSSIBLE\n");
        } else {
            printf("IMPOSSIBLE\n");
        }
    }
}