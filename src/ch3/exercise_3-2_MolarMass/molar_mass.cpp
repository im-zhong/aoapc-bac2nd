// 2024/7/28
// zhangzhong

#include <cstdio>
using namespace std;

char chemical[128] = "\0";

double get_atomic_weight(char atomic) {
    switch (atomic) {
    case 'C':
        return 12.01;
    case 'H':
        return 1.008;
    case 'O':
        return 16;
    case 'N':
        return 14.01;
    }
    return 0;
}

int main() {
    int test_case_count = 0;
    scanf("%d\n", &test_case_count);

    // for (int _ = 0; _ < test_case_count; _++) {
    //     double molar_mass = 0;

    //     // 不行，我们让scanf帮我们处理数字
    //     //
    //     char ch = 0;
    //     while ((ch = getchar()) != EOF && ch != '\n') {

    //         double atomic_weight = get_atomic_weight(ch);

    //         // check if the next digit is number
    //         int number = 0;
    //         //
    //         我想知道如果刚好读到行的结尾，会把回车吞掉，然后getchar就读不到回车了吗？
    //         //
    //         ！！！果然如此，scanf会读取结尾的回车，导致getchar读不到回车，循环没有退出！
    //         if (std::scanf("%d", &number) != 1) {
    //             number = 1;
    //         }

    //         molar_mass += atomic_weight * number;
    //     }
    //     printf("%.3f\n", molar_mass);
    // }
    for (int _ = 0; _ < test_case_count; _++) {
        double molar_mass = 0;

        // read one line first
        scanf("%s", chemical);

        // 然后在这里对字符串进行处理就ok了
        for (char* p = chemical; *p;) {
            double atomic_weight = get_atomic_weight(*p);

            int number = 0;
            if (sscanf(p + 1, "%d", &number) != 1) {
                number = 1;
            }

            molar_mass += atomic_weight * number;

            // 然后我们的p要跃过数字
            // 那么在这种情况下，就不太适合在for里面p++
            // 如果没有数字 number=1 刚好我们的p就是+1 p += number
            // 哦 不对 我们得知道是几位数
            // number >= 2, number <= 99
            if (number == 1) {
                p++;
            } else if (number < 10) {
                p += 2;
            } else {
                p += 3;
            }
        }

        printf("%.3f\n", molar_mass);
    }
}