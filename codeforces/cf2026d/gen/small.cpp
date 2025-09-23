#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    long long n = gen.uniform<int>(3, 1000);
    printf("%lld\n", n);
    for (int i = 0; i < n; i++) {
        printf("%lld ", gen.uniform<long long>(-5, 5));
    }
    printf("\n");
    int q = gen.uniform<int>(1000, 300000);
    printf("%d\n", q);
    n = n * (n + 1) / 2;
    for (int i = 0; i < q; i++) {
        long long l = gen.uniform<long long>(1, n);
        long long r = gen.uniform<long long>(l, n);
        printf("%lld %lld\n", l, r);
    }

    return 0;
}
