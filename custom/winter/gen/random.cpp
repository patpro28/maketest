#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 100000);
    int m = gen.uniform(n + 1, 300000);
    int q = gen.uniform(1, 100000);
    cout << n << ' ' << m << ' ' << q << '\n';
    auto edges = gen.tree<int>(n, true);
    for (int i = 0; i < m - n + 1; ++i) {
        int u = gen.uniform(1, n);
        int v = gen.uniform(1, n);
        cout << u << ' ' << v << '\n';
    }
    for (auto [u, v] : edges) cout << u << ' ' << v << '\n';
    while (q--) {
        int type = gen.uniform(1, 100);
        if (type == 100) 
            cout << 2 << ' ' << gen.uniform(1, 5) << '\n';
        if (type <= 50)
            cout << 1 << ' ' << gen.uniform(1, n) << '\n';
        if (type > 50 && type < 100)
            cout << 3 << ' ' << gen.uniform(1, n) << '\n';
    }
    return 0;
}
