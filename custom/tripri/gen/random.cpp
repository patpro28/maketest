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
    for (int i = 0; i < t - 3; i++) {
        long long n = gen.uniform<long long>(1, N_MAX);
        if (n & 1) n++;
        printf("%lld\n", n);
    }
    printf("12\n22\n27\n");

    return 0;
}
