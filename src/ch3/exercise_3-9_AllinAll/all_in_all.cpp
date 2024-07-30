// 2024/7/30
// zhangzhong

#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

// 这道题目感觉就是一个具体的算法啊
// 就是s是不是t的一个字序列
// 字序列问题，好像是一个动态规划问题

// 我真是服了，题目要求也没说字符范围
// TMD结果需要这么大的存储空间。。。。。
// 真实无语
char s[1024000] = "";
char t[1024000] = "";

int main() {
    while (scanf("%s%s", s, t) == 2) {
        // whether s is a subsequence of t
        char* ps = s;
        char* pt = t;

        bool is_sub = true;
        while (*ps && *pt) {

            // find the first occurence of *ps in t
            char* p = strchr(pt, *ps);
            // if not found, p is nullptr?
            if (p == nullptr) {
                // then s is not a subsequence of t
                // printf("No\n");
                is_sub = false;
                break;
            }

            // if we found, then update pt -> p
            pt = p + 1;
            ps++;
        }

        // 如果ps没有结束，那么我们仍然也不是subsequence
        if (*ps) {
            is_sub = false;
        }

        printf(is_sub ? "Yes\n" : "No\n");

        memset(s, 0, sizeof(s));
        memset(t, 0, sizeof(t));
    }
}