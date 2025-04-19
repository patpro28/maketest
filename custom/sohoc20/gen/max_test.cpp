#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const long long N = 1e18;
const int K = 1e6;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    long long n = gen.uniform<long long>(1000000000000000ll, N);
    int k = gen.uniform(900000, K);
    
    cout << n << ' ' << k << '\n';
    return 0;
}
