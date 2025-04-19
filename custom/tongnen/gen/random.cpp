#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int a = gen.uniform<int>(1, 100);
    int b = gen.uniform<int>(10000000, 1000000000);
    
    printf("%d %d\n", a, b);
    return 0;
}
