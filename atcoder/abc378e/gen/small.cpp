#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 20);
    int m = gen.uniform(1, 20);
    printf("%d %d\n", n, m);
    for (int i = 0; i < n; i++) {
        printf("%d ", gen.uniform(0, 50));
    }
    return 0;
}
