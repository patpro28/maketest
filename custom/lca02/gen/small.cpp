#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 20);
    int q = gen.uniform(1, 100);
    cout << n << ' ' << q << '\n';
    auto edges = gen.tree<int>(n, true);
    for (auto e : edges) {
        cout << e.first << ' ' << e.second << '\n';
    }
    for (int i = 0; i < q; i++) {
        int u = gen.uniform(1, n);
        int v = gen.uniform(1, n);
        cout << u << ' ' << v << '\n';
    }
    return 0;
}
