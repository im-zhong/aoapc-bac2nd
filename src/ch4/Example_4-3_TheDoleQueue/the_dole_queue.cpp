// 2024/7/31
// zhangzhong

#include <cstdio>
#include <cstring>

using namespace std;

int queue[32];

int main() {
    int n = 0, k = 0, m = 0;
    while (scanf("%d%d%d", &n, &k, &m) == 3 && n > 0) {
        memset(queue, 0, sizeof(queue));

        // 0 means the person is not been picked
        // and 1 means the person is already picked
        // Note that the two victims
        // (sorry, trainees) leave the ring simultaneously, so it is possible
        // for one official to count a person already selected by the other
        // official.

        // after the twok officer pick down, then update the queue
        // officer k stand at the first postion, and ki ++
        // officier m stand at the last position and mi --
        int ki = -1;
        int mi = -1;

        int step = 0;
        while (true) {
            if (step != 0) {
                printf(",");
            }
            step++;

            // officier k found the kth person
            for (int _ = 0; _ < k; _++) {
                // get the next unqueueued person
                for (ki = (ki + 1) % n; queue[ki] != 0; ki = (ki + 1) % n)
                    ;
            }

            // officier m found the mth person
            // 这里减一取余非常不方便
            // 我们仍然采取加的方式 然后用总长度减去
            for (int _ = 0; _ < m; _++) {
                for (mi = ((mi + 1) % n); queue[n - mi - 1] != 0;
                     mi = ((mi + 1) % n))
                    ;
            }

            // pick the two person at ki and mi
            // first check if ki == mi
            if (ki == (n - mi - 1)) {
                printf("%3d", ki + 1);
                queue[ki] = 1;
            } else {
                printf("%3d%3d", ki + 1, (n - mi - 1) + 1);
                queue[ki] = 1;
                queue[(n - mi - 1)] = 1;
            }

            // check if all the person is picked out
            bool is_ok = true;
            for (int i = 0; i < n; i++) {
                if (queue[i] == 0) {
                    is_ok = false;
                    break;
                }
            }
            if (is_ok) {
                printf("\n");
                break;
            }
        }
    }
}