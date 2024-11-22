// 2024/11/22
// zhangzhong

#include <cmath>
#include <iostream>
#include <vector>

const int INF = 1 << 20;

const int max_point_count = 1024;
// 定义一个二维数组
// 题目没有给出n最大有多大
double min_distance[max_point_count][max_point_count];

struct Point {
    int x;
    int y;

    double Distance(const Point& other) const {
        double delta_x = this->x - other.x;
        double delta_y = this->y - other.y;
        return std::sqrt(delta_x * delta_x + delta_y * delta_y);
    }
};

double GetShortestDistance(const std::vector<Point>& points) {

    // 首先对数组进行一个初始化
    int n = points.size() - 1;
    for (int row = 1; row < n; row++) {
        for (int col = 1; col < n; col++) {
            min_distance[row][col] = INF;
        }
    }

    // 设定初始状态，也就是最后一行
    int i = n - 1;
    for (int j = 1; j < i; j++) {
        min_distance[i][j] =
            points[i].Distance(points[n]) + points[j].Distance(points[n]);
    }

    // 然后我们就开始倒着算
    for (int i = n - 2; i >= 2; i--) {
        for (int j = 1; j < i; j++) {

            // (i, j)
            // 1. (i->i+1, j)
            // 2. (i, j->i+1) => (j->i+1, i)
            min_distance[i][j] = std::min(
                points[i].Distance(points[i + 1]) + min_distance[i + 1][j],
                points[j].Distance(points[i + 1]) + min_distance[i + 1][i]);
        }
    }

    return points[1].Distance(points[2]) + min_distance[2][1];
}

int main() {

    int point_count = 0;
    while (std::cin >> point_count) {
        std::vector<Point> points;
        points.push_back(Point{});
        for (int i = 0; i < point_count; i++) {
            Point point;
            std::cin >> point.x >> point.y;
            points.push_back(point);
        }

        double shortest_distance = GetShortestDistance(points);
        std::printf("%.2f\n", shortest_distance);
    }
}