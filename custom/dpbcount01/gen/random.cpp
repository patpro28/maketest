#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int N_MAX = 500000;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(100000, N_MAX); 
    int m = gen.uniform<int>(20, 40);
    int q = 500000;

    printf("%d %d %d\n", n, m, q);
    for (int i = 0; i < n; i++) {
        printf("%d ", gen.uniform<int>(1, m));
    }
    printf("\n");
    for (int i = 0; i < q; i++) {
        int l = gen.uniform<int>(1, 1000);
        int r = gen.uniform<int>(100000, n);
        printf("%d %d\n", l, r);
    }
    return 0;
}
