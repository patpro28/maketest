#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 100000;
    int k = gen.uniform(1, 100 * n);
    printf("%d %d\n", n, k);
    for (int i = 0; i < n; i++)
        printf("%c", gen.uniform('a', 'z'));

    return 0;
}
