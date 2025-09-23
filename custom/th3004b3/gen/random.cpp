#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    cout << gen.uniform<long long>(1, 10000000000ll) << '\n';
    return 0;
}
