#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(3, 10000);
    auto N = gen.gen_sum<int>(3e5, t, 1, 1e5);
    cerr << "Done N\n";
    int q = gen.uniform<int>(max(10, t), 1e6);
    cerr << "Process K: " << q << "\n";
    auto K = gen.gen_sum<long long>(1e6, q, 1, 1e5);
    cerr << "Done K\n";
    auto Q = gen.gen_sum<int>(q, t);
    cout << t << '\n';
    int idx_q = 0;
    while (t--) {
        long long n = N[t], q = Q[t];
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
