#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n, q;
    n = gen.uniform<int>(1, 300000);
    q = gen.uniform<int>(1, 300000);
    cout << n << "\n";
    auto edges = gen.tree<int>(n, true);

    for (auto e : edges) {
        cout << e.first << " " << e.second << ' ' << gen.uniform<int>(1, 1e9) << "\n";
    }

    cout << q << "\n";
    while (q--) {
        int u = gen.uniform<int>(1, n - 1);
        int v = gen.uniform<int>(u + 1, n);
        int w = gen.uniform<int>(1, 1e9);
        cout << u << " " << v << " " << w << "\n";
    }
    
    return 0;
}
