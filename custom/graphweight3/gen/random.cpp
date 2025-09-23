#include <iostream>
#include <vector>
#include <map>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(25000, 50000);
    int m = gen.uniform<int>(min(400000ll, 1ll * n * (n - 1) / 2), min(500000ll, 1ll * n * (n - 1) / 2));
    cout << n << ' ' << m << '\n';
    map<pair<int, int>, bool> used_edges;
    used_edges[{0, 0}] = true; // to avoid self-loop
    for (int i = 0; i < m; ++i) {
        int u = 0, v = 0;
        while (used_edges.count({u, v}) || u == v) {
            u = gen.uniform(1, n);
            v = gen.uniform(1, n);
        }
        used_edges[{u, v}] = true;
        cout << u << ' ' << v << ' ' << gen.uniform(1, 1000000) << '\n';
    }
    int q = 200;
    cout << q << '\n';
    for (int i = 0; i < q; ++i) {
        int u = gen.uniform(1, n);
        int w = gen.uniform(1, 1000000);
        cout << u << ' ' << w << '\n';
    }
    return 0;
}
