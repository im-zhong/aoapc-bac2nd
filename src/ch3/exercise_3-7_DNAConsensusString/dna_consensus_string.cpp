// 2024/7/29
// zhangzhong

#include <algorithm>
#include <cstdio>
#include <new>
#include <unordered_map>
#include <vector>
using namespace std;

struct GenePair {
    char gene;
    int count;

    friend bool operator<(const GenePair& lhs, const GenePair& rhs) {
        if (lhs.count > rhs.count) {
            return true;
        } else if (lhs.count == rhs.count) {
            return lhs.gene < rhs.gene;
        } else {
            return false;
        }
    }
};

char dnas[50][1001] = {};

std::unordered_map<char, int> genes = {{'A', 0}, {'C', 0}, {'G', 0}, {'T', 0}};
char consensus_dna[1024] = "";

int main() {
    int test_case_count = 0;
    scanf("%d", &test_case_count);

    for (int _ = 0; _ < test_case_count; _++) {
        int m = 0, n = 0;
        scanf("%d%d", &m, &n);

        // read the dnas
        for (int r = 0; r < m; r++) {
            scanf("%s", dnas[r]);
        }

        // char current_max_gene = '\0';
        // char current_max_count = 0;
        // int A = 0, C = 0, G = 0, T = 0;

        int hamming_distance = 0;
        char* p = consensus_dna;
        for (int c = 0; c < n; c++) {

            genes['A'] = 0;
            genes['C'] = 0;
            genes['G'] = 0;
            genes['T'] = 0;
            for (int r = 0; r < m; r++) {
                genes[dnas[r][c]]++;
            }

            // check who is the largets
            // if all is one gene, then hamming distance remain the same
            // if there is one diff, then hamming distance + 1

            // 现在我们拿到了四个元祖
            // (A, 10), (C, 11), ...
            // 我们需要写一个排序函数，给这个东西排序
            // 排序的规则就是首先排count 越大越靠前
            // 如果count一样，那么字母越小越靠前
            vector<GenePair> gene_pairs;
            for (const auto pair : genes) {
                auto gene_pair = GenePair{pair.first, pair.second};
                gene_pairs.push_back(gene_pair);
            }
            sort(gene_pairs.begin(), gene_pairs.end());

            // get the first gene
            auto gene_pair = gene_pairs.front();
            // if (gene_pair.count < m) {
            //     hamming_distance;
            // }
            // 注意这个距离是所有距离的总和
            hamming_distance += m - gene_pair.count;

            *p++ = gene_pair.gene;
        }
        *p = '\0';

        printf("%s\n%d\n", consensus_dna, hamming_distance);
    }
}