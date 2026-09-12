#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(5, 100);
    cout << t << '\n';
    auto N = gen.gen_sum<int>(5e4, t, 1, 1e4);
    for (int i = 0; i < t; i++) {
        int n = N[i], m = gen.uniform<int>(1, 1e9);
        int k = gen.uniform<int>(1, max(1, m / 10));
        cout << n << ' ' << m << '\n';
        vector<int> b(n);
        for (auto &x : b) {
            x = gen.uniform(1, m / k) * k;
        }
        for (int i = 1; i < n; ++i) b[i] = __gcd(b[i], b[i - 1]);
        for (auto x : b) cout << x << ' ';
        cout << '\n';
    }
    return 0;
}
