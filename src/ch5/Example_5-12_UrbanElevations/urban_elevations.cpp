// 2025/4/3
// zhangzhong

#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_set>
#include <vector>

struct Building {
    double x;
    double y;
    double width;
    double depth;
    double height;
    int id;

    bool operator<(const Building& other) const noexcept {
        if (this->x == other.x) {
            return this->y < other.y;
        }
        return this->x < other.x;
    }
};

// struct Range {
//     double left;
//     double right;

//     double GetMiddle() const noexcept { return (left + right) / 2; }
// };

class Solution {
  public:
    Solution(const std::vector<Building>& buildings) : _buildings(buildings) {
        // std::sort(this->_buildings.begin(), this->_buildings.end());
    }

    // ordered south-to-north，west-to-east
    // 按照左下角x的坐标从小到大排序，如果x 相同，则按照y坐标从小到大排序
    std::vector<Building> GetVisibleBuildings() {

        // 首先收集所有的building的左边x和右边x的坐标
        std::vector<double> corrs;
        for (const Building& building : this->_buildings) {
            corrs.push_back(building.x);
            corrs.push_back(building.x + building.width);
        }

        // 排序 去重
        std::sort(corrs.begin(), corrs.end());
        auto it = std::unique(corrs.begin(), corrs.end());
        corrs.resize(it - corrs.begin());

        // 验证所有building的x和x+width都在这里面
        // for (const Building& building : this->_buildings) {
        //     assert(std::find(corrs.begin(), corrs.end(), building.x) !=
        //            corrs.end());
        //     assert(std::find(corrs.begin(), corrs.end(),
        //                      building.x + building.width) != corrs.end());
        // }

        // 然后这个vector会形成一系列的区间，对于每个区间
        // 我们只需要取中点，就可以判断这条线上的所有building的可见性
        // 对于区间的遍历，我们可以再写一个iterator
        // 或者suanle

        // 我们可以使用一个index来表示building
        // 我们在这里存储的也是这个index, 需要注意的是，这个index并不是id
        // id代表的是输入顺序
        std::vector<std::vector<int>> range_to_building_index(corrs.size() - 1);
        for (int building_index = 0; building_index < this->_buildings.size();
             building_index++) {
            const Building& building = this->_buildings[building_index];
            // 你tm search不返回对应的index?

            // binary_search -> bool
            // lower_bound -> iter
            // upper_bound -> iter + 1
            auto it_left =
                std::lower_bound(corrs.begin(), corrs.end(), building.x);
            assert(it_left != corrs.end());
            auto it_right = std::lower_bound(corrs.begin(), corrs.end(),
                                             building.x + building.width);
            assert(it_right != corrs.end());

            // 获得迭代器位置的索引，只需要
            int range_left_index = it_left - corrs.begin();
            int range_right_index = it_right - corrs.begin();
            for (int range_index = range_left_index;
                 range_index < range_right_index; range_index++) {
                range_to_building_index[range_index].push_back(building_index);
            }
        }
        // 错啦！
        // 就算我们在最开始把building进行排序
        // 但是在根据range 拆分的时候，拆分完成之后也不一定是按照y从小到达排序的
        // 所以我们需要在这里对每个range内部的building根据y从小到达排序
        // 那么，这是否意味着，我们的building一开始就没有必要排序？
        for (std::vector<int>& building_indicies : range_to_building_index) {
            std::sort(building_indicies.begin(), building_indicies.end(),
                      [this](const int left_building_index,
                             const int right_building_index) {
                          return this->_buildings[left_building_index].y <
                                 this->_buildings[right_building_index].y;
                      });
        }

        // 或者使用一个set
        std::unordered_set<int> visible_building_indicies;
        for (int range_index = 0; range_index < corrs.size() - 1;
             range_index++) {
            // Range range{corrs[range_index], corrs[range_index + 1]};
            // double middle = range.GetMiddle();

            // 然后找到经过这条线的所有building
            // 然后找能看见的！因为哪怕buildg在这个区间看不见，也可能在别的区间看见
            // 但是只要能在一个区间看见，就能看见

            // 找经过某条线的building也有几种方法
            // 当然目前看起来最简单的事遍历，building的数量并不多，或许这个方法可以过

            // 有没有更好的办法？或许可以提前遍历一次building，
            // 然后对于每个building，可以用二分查找range
            // 因为range中的坐标来自building的坐标，所以一定找得到
            // 二分查找得到的范围，就是building存在的范围
            // 可以使用一个额外的vector，或者map，来存储出现在某个range中的building
            // 可以就用vector就行
            // 然后对这些building根据y来排序

            // 还有没有其他方法？
            // 如果一开始building就是根据x，y进行排序的呢？
            // 这样我们遍历之后插入的顺序，天然就是根据y来排序的！
            const std::vector<int>& building_indicies_in_range =
                range_to_building_index[range_index];

            // 现在这些building是按照y从小到大排序的
            // 我们从南向北遍历这些building
            // 并记录目前看到的最高的建筑
            // 只要当前的建筑的高度 > 当前最高的高度，那么这个建筑就是可见的！
            double current_height = -1;
            for (const int building_index : building_indicies_in_range) {
                const Building& building = this->_buildings[building_index];
                if (building.height > current_height) {
                    visible_building_indicies.insert(building_index);
                    current_height = building.height;
                }
            }
        }
        // 有些building可能在多个range可见，需要去重

        // 最终的visible_building_indicies需要转换成 input id
        // 我们的visible building index需要转换成Buildings再重新排序
        // 因为我们根据range从西向东遍历出来的可见的顺序 并不是输入的顺序
        std::vector<Building> visible_buildings;
        for (const int building_index : visible_building_indicies) {
            visible_buildings.push_back(this->_buildings[building_index]);
        }
        std::sort(visible_buildings.begin(), visible_buildings.end());

        return visible_buildings;
    }

  private:
    std::vector<Building> _buildings;
};

int main(int argc, char* argv[]) {
    // Input for your program consists of the numeric description of maps of
    // several cities

    // [0, 100]
    int building_count;

    // The first line of
    // each map contains the number of buildings in the city
    for (int kase = 1; std::cin >> building_count; kase++) {
        if (building_count == 0) {
            break;
        }

        // One blank line must separate output from consecutive input records
        if (kase > 1) {
            std::cout << "\n";
        }

        // Each subsequent line of a map contains data for a single building
        // 5 real numbers
        // Buildings are numbered according to where their data lines appear in
        // the map’s input data， building需要按照输入顺序进行标号，从1开始
        std::vector<Building> buildings;
        for (int i = 0; i < building_count; i++) {
            Building building;
            std::cin >> building.x >> building.y >> building.width >>
                building.depth >> building.height;
            building.id = i + 1;
            buildings.push_back(building);
        }

        Solution solution{std::move(buildings)};

        // output:
        std::cout << "For map #" << kase
                  << ", the visible buildings are numbered as follows:\n";
        std::vector<Building> visible_buildings =
            solution.GetVisibleBuildings();
        std::cout << visible_buildings[0].id;
        for (int i = 1; i < visible_buildings.size(); i++) {
            std::cout << " " << visible_buildings[i].id;
        }
        std::cout << "\n";
    }
}