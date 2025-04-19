#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const long long MAX = 1e18;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 100000;
    cout << n << '\n';
    for (int i = 0; i < n - 1; ++i)
        cout << gen.uniform(0ll, MAX) << ' ';
    cout << MAX << '\n';
    int q = 100000;
    cout << q << '\n';
    while (q--) {
        auto perms = gen.perm<int>(9);
        cout << 0 << ' ';
        for (auto x: perms)
            cout << x + 1 << ' ';
        cout << gen.uniform(0ll, MAX) << '\n';
    }
    return 0;
}
