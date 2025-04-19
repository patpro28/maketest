#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(10, 15);
    cout << t << '\n';
    auto N = gen.gen_sum<int>(1000000, t, 1, 100000);
    for (int i = 0; i < t; ++i) {
        cout << N[i] << '\n';
        auto edges = gen.tree<int>(N[i], true);
        for (auto [u, v] : edges) {
            cout << u << ' ' << v << '\n';
        }
        int min = gen.uniform(1, 10000000);
        int max = gen.uniform(min, min * 100);
        for (int j = 0; j < N[i]; ++j) {
            cout << gen.uniform(min, max) << ' ';
        }
        cout << '\n';
    }
    return 0;
}
