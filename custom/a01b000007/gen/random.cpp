#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char *argv[])
{

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    long long n = gen.uniform<long long>(1, 1e18);
    cout << n << '\n';
    return 0;
}
