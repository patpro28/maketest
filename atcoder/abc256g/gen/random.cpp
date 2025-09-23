#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    long long n = gen.uniform<long long>(3, 1e12);
    int d = gen.uniform<int>(1, 1e4);
    cout << n << " " << d << "\n";
    return 0;
}
