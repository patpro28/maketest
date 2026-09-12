#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int MAX_X = 1e6;
const int MAX_C = 1e6;
const int MAX_P = 1e6;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int x = gen.uniform(1, MAX_X);
    int c = gen.uniform(1, x + 10000); // c can be greater than x
    int p = gen.uniform(1, MAX_P);
    printf("%d %d %d\n", x, c, p);
    return 0;
}
