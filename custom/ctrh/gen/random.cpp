#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

vector<int> gen_many(Random &gen, int n, int m) {
    // Gen x1 + x2 + ... + xm = n
    vector<int> res(m, 1);
    n -= m;
    for (int i = 0; i < n; ++i) {
        int idx = gen.uniform(0, m - 1);
        res[idx] ++;
    }
    return res;
}

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);
    int t = gen.uniform(1, 10000);

    cout << t << '\n';
    auto N = gen_many(gen, 200000, t);
    for (int i = 0; i < t; ++i) {
        int n = N[i];
        cout << n << '\n';
        auto edges = gen.tree<int>(n, true);
        for (auto [u, v]: edges) {
            cout << u << ' ' << v << '\n';
        }
    }
    return 0;
}
