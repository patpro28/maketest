#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform<int>(1, 50);
    auto N = gen.gen_sum<int>(10000, t, 2);
    auto M = gen.gen_sum<int>(1000, t);
    cout << t << '\n';
    for (int i = 0; i < t; ++i) {
        int n = N[i], m = M[i];
        cout << n << '\n';
        auto tree = gen.tree<int>(n, true);
        for (auto [u, v] : tree)
            cout << u << ' ' << v << ' ' << gen.uniform<char>('a', 'z') << '\n';
        for (int i = 0; i < m; ++i) {
            cout << gen.uniform<char>('a', 'z');
        }
        cout << '\n';
    }
    return 0;
}
