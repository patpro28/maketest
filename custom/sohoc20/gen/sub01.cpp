#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const long long N = 1e6;
const int K = 1e6;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    long long n = gen.uniform<long long>(1, N);
    int k = 1;
    
    cout << n << ' ' << k << '\n';
    return 0;
}
