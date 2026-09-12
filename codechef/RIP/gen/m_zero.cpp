#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform<int>(3, 100000);
    auto N = gen.gen_sum<int>(3e5, t, 1, 1e5);
    cout << t << "\n";
    while (t--) {
        int n = N[t], m = 0;
        cout << n << " " << m << '\n';
        for (int i = 0; i < n; ++i) {
            cout << gen.uniform<int>(1, n) << (i == n - 1 ? '\n' : ' ');
        }
        for (int i = 0; i < n; ++i) {
            cout << gen.uniform<int>(1, min(n, 10000)) << (i == n - 1 ? '\n' : ' ');
        }
        auto perm = gen.perm<int>(n);
        for (int i = 0; i < m; ++i) {
            cout << perm[i] + 1 << ' ';
        }
        cout << '\n';
    }
    return 0;
}
