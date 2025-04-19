#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int> (1, 500000);
    printf("%d\n", n);
    auto edges = gen.tree<int>(n);
    for (auto [a, b] : edges) {
        printf("%d %d\n", a + 1, b + 1);
    }
    int m = gen.uniform<int>(1, 100000);
    printf("%d\n", m);
    for (int i = 0; i < m; ++i)
        printf("%d ", gen.uniform<int>(1, n));
    return 0;
}
