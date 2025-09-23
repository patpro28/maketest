#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

using ll = long long;
const int L_MAX = 1e3;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    ll l = gen.uniform<ll>(1, L_MAX);
    ll r = l + gen.uniform<ll>(l + 1e9, 1e18);
    cout << l << ' ' << r << '\n';

    return 0;
}
