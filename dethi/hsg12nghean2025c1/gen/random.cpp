#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int a = gen.uniform<int>(2, A_AND_B_MAX);
    int b = gen.uniform<int>(2, A_AND_B_MAX);
    long long N = gen.uniform<long long>(1e6, 1e18);
    
    cout << a << ' ' << b << ' ' << N << "\n";
    return 0;
}
