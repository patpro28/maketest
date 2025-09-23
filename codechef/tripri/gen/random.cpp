#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 500;
    printf("%d\n", t);
    for (int i = 1; i < t; i++) {
        long long n = gen.uniform<long long>(1, 1e10 / 2);
        printf("%lld\n", n * 2);
    }
    printf("%d\n", 0);

    return 0;
}
