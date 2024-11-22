// 2024/11/22
// zhangzhong

#include <algorithm>
#include <iostream>
#include <vector>

// const int max_block_count = 30;

struct Rectangle {
    int length;
    int width;
    int height;

    friend bool operator<(const Rectangle& lhs, const Rectangle& rhs) {
        if (lhs.length == rhs.length) {
            if (lhs.width == rhs.width) {
                return lhs.height < rhs.height;
            } else {
                return lhs.width < rhs.width;
            }
        } else {
            return lhs.length < rhs.length;
        }
    }
};

int GetMaximumHeight(const std::vector<Rectangle>& rectangles) {

    // 我们设定高度是一个大的负数吧
    int MIN = -(1 << 20);

    std::vector<int> max_height(rectangles.size(), MIN);
    max_height.back() = rectangles.back().height;

    for (int idx = rectangles.size() - 2; idx >= 0; idx--) {
        const Rectangle& rectangle = rectangles[idx];
        int height = 0;
        // 找到后序所有比我们大的rectangle
        for (int i = 0; i < rectangles.size(); i++) {
            const Rectangle& big_rectangle = rectangles[i];
            if (big_rectangle.length > rectangle.length &&
                big_rectangle.width > rectangle.width) {
                height = std::max(height, max_height[i]);
            }
        }
        max_height[idx] = rectangle.height + height;
    }

    // [[BUG]]
    // 我知道哪里不对了，最高的不一定是最小的块在最上面
    // 我们需要遍历一遍这个数组找最大值
    // 所以实际上我们是不需要排序的? 不行 貌似还是需要排序
    int height = max_height[0];
    for (int h : max_height) {
        height = std::max(height, h);
    }
    return height;
}

void SwapXYZ(int& x, int& y, int& z) {
    if (x > y) {
        std::swap(x, y);
    }
    // x <= y
    if (x > z) {
        std::swap(x, z);
    }
    // x <= z
    if (y > z) {
        std::swap(y, z);
    }
    // x <= y <= z
}

int main() {

    for (int case_id = 1;; case_id++) {
        int block_count = 0;
        std::cin >> block_count;
        if (block_count == 0) {
            break;
        }

        std::vector<Rectangle> rectangles;
        for (int b = 0; b < block_count; b++) {

            int x = 0;
            int y = 0;
            int z = 0;
            std::cin >> x >> y >> z;
            // make x <= y <= z
            SwapXYZ(x, y, z);
            rectangles.push_back(Rectangle{z, y, x});
            rectangles.push_back(Rectangle{z, x, y});
            rectangles.push_back(Rectangle{y, x, z});
        }

        std::sort(rectangles.begin(), rectangles.end());

        int maximum_height = GetMaximumHeight(rectangles);
        std::cout << "Case " << case_id
                  << ": maximum height = " << maximum_height << "\n";
    }
}