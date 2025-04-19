#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int a = gen.uniform<int>(1, 999);
    int b = gen.uniform<int>(1, 999);

    if (a > b) swap(a, b);
    if (a == b) b++;
    printf("%d %d\n", a, b);
    return 0;
}
