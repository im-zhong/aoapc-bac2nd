// 2024/7/22
// zhangzhong

#include <algorithm>
#include <cstdio> // good, while iostream not good

// good
using namespace std;

const int MAX_N = 128;
int nums[MAX_N] = {};

int main() {
    int n = 0, q = 0;
    int level = 0;
    while (scanf("%d%d", &n, &q) == 2 && n != 0 && q != 0) {
        level++;
        printf("CASE# %d:\n", level);

        int num = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &num);
            nums[i] = num;
        }

        sort(nums, nums + n);
        // while (q--) {: not good
        for (int i = 0; i < q; i++) { // good
            int question = 0;
            scanf("%d", &question);

            auto r = lower_bound(nums, nums + n, question);
            if (r && *r == question) {
                printf("%d found at %ld\n", question, (r - nums) + 1);
            } else {
                printf("%d not found\n", question);
            }
        }
    }
}
