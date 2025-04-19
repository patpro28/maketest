#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, 10);
    auto N = gen.gen_sum(200000, t);
    auto Q = gen.gen_sum(200000, t);

    cout << t << endl;
    while (t--) {
        int n = 2 * N[t];
        cout << N[t] << " " << Q[t] << endl;
        auto edges = gen.tree<int>(n, true);
        for (auto &[a, b] : edges) {
            cout << a << " " << b << endl;
        }
        vector<int> color(n);
        for (int i = 0; i < N[t]; ++i)
            color[i] = color[i + N[t]] = i + 1;
        gen.shuffle(color.begin(), color.end());
        for (int i = 0; i < n; i++) {
            cout << color[i] << " \n"[i == n - 1];
        }
        for (int i = 0; i < Q[t]; i++) {
            int type = gen.uniform(1, 2);
            if (type == 1) {
                auto [u, v] = gen.uniform_pair(1, n);
                cout << type << " " << u << " " << v << endl;
            } else {
                cout << type << " " << gen.uniform(1, N[t]) << endl;
            }
        }
    }
    return 0;
}
