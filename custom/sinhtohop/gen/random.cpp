#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(6, 10);
    int k = gen.uniform(1, n);
    
    printf("%d %d\n", k, n);
    auto a = gen.choice<int>(n, 1, A_AND_B_MAX);
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    return 0;
}
