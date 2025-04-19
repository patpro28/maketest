#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;
using ll = long long;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 200000);
    long long k = gen.uniform(1LL, ll(1e18));
    cout << n << ' ' << k << '\n';
    auto perm = gen.perm<int>(n);
    for (int i = 0; i < n; i++) {
        cout << perm[i] + 1 << " \n"[i == n - 1];
    }
    return 0;
}
