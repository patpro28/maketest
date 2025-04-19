#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 100000;
    int k = gen.uniform<int>(1, n);
    printf("%d %d\n", n, k);
    int j = n / 2;
    for (int i = 0; i < j; ++i)
        printf("%d%c", 1, ' ');
    for (int i = j; i < n; ++i)
        printf("%d%c", 1000000000, " \n"[i == n - 1]);
    return 0;
}
