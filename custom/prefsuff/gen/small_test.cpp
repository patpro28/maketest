#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 20;
    printf("%d\n", t);
    int limit = MAXN / t;
    for (int i = 0; i < t; i++) {
        int n = gen.uniform(1, limit);
        if (!(n & 1)) n++;
        printf("%d\n", n);
    }

    return 0;
}
