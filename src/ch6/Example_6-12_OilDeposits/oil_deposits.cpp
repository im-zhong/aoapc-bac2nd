// 2024/10/19
// zhangzhong

#include <iostream>

// 因为row和col是有范围的
// 所以我们分配一块二维数组，直接用更简单

int cur_row = 0;
int cur_col = 0;
char region[128][128];
int region_ids[128][128];

int oil_id = 0;

void detect_adjancent_oil(int row, int col, int id) {
    if (row < 0 || row >= cur_row) {
        return;
    }
    if (col < 0 || col >= cur_col) {
        return;
    }

    // 不对！这里的逻辑错误了
    // 我们应该循环九宫格，然后在内部判断错误的下标要continue
    // 在for这里判断会导致整个for循环不执行，反而导致后续的正确范围内的row无法执行了
    for (int r = row - 1; r <= row + 1; r++) {
        if (r < 0 || r >= cur_row) {
            continue;
        }
        for (int c = col - 1; c <= col + 1; c++) {
            if (c < 0 || c >= cur_col) {
                continue;
            }
            // 判断周围地块是否邻接且没有染色
            if (region[r][c] == '@' && region_ids[r][c] == 0) {
                // [[TIPS]] 这里变量使用的太混乱 优势r 又是 row 又是 cur_row
                // 果然导致了bug
                region_ids[r][c] = id;
                detect_adjancent_oil(r, c, id);
            }
        }
    }
}

void print_region_id() {
    for (int r = 0; r < cur_row; r++) {
        for (int c = 0; c < cur_col; c++) {
            std::cout << region_ids[r][c] << " ";
        }
        std::cout << std::endl;
    }
}

int detect_oil(int row, int col) {
    // read the empty line
    std::string line;
    std::getline(std::cin, line);

    for (int r = 0; r < row; r++) {
        std::string line;
        std::getline(std::cin, line);
        for (int c = 0; c < col; c++) {
            region[r][c] = line[c];
        }
    }

    int oil_count = 0;
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            region_ids[r][c] = 0;
        }
    }
    oil_id = 0;

    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            if (region[r][c] == '@' && region_ids[r][c] == 0) {
                // find a new oil!
                // dfs on this node and put all the adjacent node to the same id
                oil_id++;
                region_ids[r][c] = oil_id;
                detect_adjancent_oil(r, c, oil_id);
            }
        }
    }

    return oil_count;
}

int main() {

    int row = 0;
    int col = 0;
    while (std::cin >> row >> col) {
        cur_row = row;
        cur_col = col;
        if (row == 0 || col == 0) {
            break;
        }

        oil_id = 0;
        detect_oil(row, col);
        std::cout << oil_id << std::endl;
    }
}