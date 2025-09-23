#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 5000;
    int m = 5000;
    cout << n << ' ' << m << '\n';
    auto edges = gen.tree<int>(n, true);
    for (auto &[u, v]: edges) {
        cout << u << ' ' << v << '\n';
    }

    for (int i = 0; i < m; ++i) {
        cout << gen.uniform(1, n) << ' ' << gen.uniform(1, n) << '\n';
    }

    return 0;
}
