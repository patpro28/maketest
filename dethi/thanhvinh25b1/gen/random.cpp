#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int a = gen.uniform<int>(1, A_AND_B_MAX - 1);
    int b = gen.uniform<int>(1, A_AND_B_MAX - 1);
    
    printf("%d %d\n", a, b);
    return 0;
}
