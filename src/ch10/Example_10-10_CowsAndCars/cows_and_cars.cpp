// 2024/12/15
// zhangzhong

#include <iostream>
int main() {
    double ncows = 0;
    double ncars = 0;
    double nshow = 0;
    while (std::cin >> ncows >> ncars >> nshow) {
        double p = (ncars * (ncars - 1) + ncows * ncars) /
                   ((ncars + ncows) * (ncars + ncows - nshow - 1));
        std::printf("%.5f\n", p);
    }
}