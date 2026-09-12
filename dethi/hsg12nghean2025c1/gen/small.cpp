#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int a = gen.uniform<int>(2, 100);
    int b = gen.uniform<int>(2, 100);
    long long N = gen.uniform<long long>(2, 1e6);
    
    cout << a << ' ' << b << ' ' << N << "\n";
    return 0;
}
