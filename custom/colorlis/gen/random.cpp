#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int> (10000, 200000);
    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        printf("%d%c", gen.uniform<int>(1, 1000000000), " \n"[i == n - 1]);
    }
    return 0;
}
