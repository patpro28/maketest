#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 200000);
    int m = gen.uniform(1, 200000);
    printf("%d %d\n", n, m);
    for (int i = 0; i < n; i++) {
        printf("%lld ", gen.uniform(0LL, A_AND_B_MAX));
    }
    return 0;
}
