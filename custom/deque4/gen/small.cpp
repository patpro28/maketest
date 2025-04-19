#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(1, N_MIN);
    int k = gen.uniform<int>(1, n);
    printf("%d %d\n", n, k);
    for (int i = 0; i < n; i++) {
        printf("%d%c", gen.uniform<int>(1, 100), " \n"[i == n - 1]);
    }
    return 0;
}
