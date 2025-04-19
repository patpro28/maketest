#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, 100000);
    auto N = gen.gen_sum(200000, t);
    cout << t << '\n';
    for (int i = 0; i < t; ++i) {
        int n = N[i];
        cout << n << ' ' << gen.uniform(1, n) << '\n';
        auto edges = gen.tree<int>(n, true);
        for (auto [u, v]: edges) {
            cout << u << ' ' << v << '\n';
        }
    }

    return 0;
}
