#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 200000);
    int q = gen.uniform(1, 200000);
    printf("%d %d\n", n, q);
    for (int i = 0; i < q; i++) {
        int l = gen.uniform(1, n);
        int r = gen.uniform(l, n);
        int x = gen.uniform(-10000, 10000);
        int y = gen.uniform(-10000, 10000);
        printf("%d %d %d %d\n", l, r, x, y);
    }

    return 0;
}
