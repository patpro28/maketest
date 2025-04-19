#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const long long MOD = 100;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    long long n = gen.uniform(1LL, MOD);
    cout << n << endl;

    return 0;
}
