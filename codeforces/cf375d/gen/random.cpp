#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(2, 100000);
    int m = gen.uniform(1, 100000);
    cout << n << ' ' << m << '\n';
    for (int i = 0; i < n; ++i)
        cout << gen.uniform(1, 100) << ' ';
    cout << '\n';
    auto edges = gen.tree<int>(n, true);
    for (auto [u, v] : edges) cout << u << ' ' << v << '\n';
    while (m--) {
        int u = gen.uniform(1, n);
        int k = gen.uniform(1, 100);
        cout << u << ' ' << k << '\n';
    }
    return 0;
}
