#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    long long n = 3e5;
    printf("%lld\n", n);
    for (int i = 0; i < n; i++) {
        printf("%lld ", gen.uniform<long long>(-10, 10));
    }
    printf("\n");
    int q = 3e5;
    printf("%d\n", q);
    n = n * (n + 1) / 2;
    for (int i = 0; i < q; i++) {
        long long l = gen.uniform<long long>(1, n);
        long long r = gen.uniform<long long>(l, n);
        printf("%lld %lld\n", l, r);
    }

    return 0;
}
