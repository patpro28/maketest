#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, 10);
    auto N = gen.gen_sum<int>(100, t, 1, 1e5);
    int q = gen.uniform<int>(t, 100);
    auto K = gen.gen_sum<int>(100, q, 1, 1e5);
    auto Q = gen.gen_sum<int>(q, t);
    cout << t << '\n';
    int idx_q = 0;
    while (t--) {
        int n = N[t], q = Q[t];
        cout << n << ' ' << q << '\n';
        auto edges = gen.tree<int>(n, true);
        for (auto e : edges) {
            cout << e.first << ' ' << e.second << '\n';
        }
        for (int i = 0; i < q; i++) {
            int k = min(K[idx_q++], n);
            cout << k << ' ';
            auto nodes = gen.gen_distinct<int>(k, 1, n);
            for (auto node : nodes) {
                cout << node << ' ';
            }
            cout << '\n';
        }
    }
    
    return 0;
}
