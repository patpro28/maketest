#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    long long mod = gen.uniform<long long>(1e12, 1e18);
    long long x = gen.uniform<long long>(1e12, 1e18);
    long long n = gen.uniform<long long>(1e12, 1e18);
    cout << x << ' ' << n << ' ' << mod << '\n';

    return 0;
}
