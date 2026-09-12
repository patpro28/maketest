#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(3, 6);
    int k = gen.uniform(1, 4);
    k = min(k, n);
    vector<int> perm = gen.perm<int>(n);
    cout << n << ' ' << k << '\n';
    vector<bool> used(n + 1, false);
    for (int i = 0; i < k; ++i) {
        int u = gen.uniform(1, n);
        while (used[u]) {
            u = gen.uniform(1, n);
        }
        used[u] = true;
        int v = perm[u - 1] + 1;
        cout << u << ' ' << v << '\n';
    }
    return 0;
}
