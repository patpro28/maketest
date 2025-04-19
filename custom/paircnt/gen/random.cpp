#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, 5);
    cout << t << '\n';
    int q = gen.uniform(1, 100000);
    auto Q = gen.gen_sum<int>(100000, q, 1);
    auto nQ = gen.gen_sum<int>(q, t, 1);
    int k = 0;
    while (t--) {
        int n = gen.uniform(1, 100000);
        cout << n << ' ' << nQ[t] << '\n';
        auto edges = gen.tree<int>(n, true);
        for (auto [u, v] : edges) cout << u << ' ' << v << '\n';
        while (nQ[t]--) {
            cout << Q[k] << ' ' << gen.uniform(1, 100) << ' ';
            auto v = gen.choice<int>(Q[k], 1, n);
            for (auto x : v) cout << x << ' ';
            cout << '\n';
            k++;
        }
    }
    return 0;
}
