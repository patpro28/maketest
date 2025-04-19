#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(10, 100);
    cout << t << '\n';
    auto N = gen.gen_sum<int>(200, t, 2, 20);
    for (int i = 0; i < t; ++i) {
        cout << N[i] << '\n';
        auto edges = gen.tree<int>(N[i], true);
        for (auto [u, v] : edges) {
            cout << u << ' ' << v << '\n';
        }
        int min = gen.uniform(1, 10);
        int max = gen.uniform(min, 20);
        for (int j = 0; j < N[i]; ++j) {
            cout << gen.uniform(min, max) << ' ';
        }
        cout << '\n';
    }
    return 0;
}
