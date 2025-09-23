#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;
using ll = long long;
const int N_MAX = 1e9;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    cout << gen.uniform<ll>(1, N_MAX) << '\n';
    return 0;
}
