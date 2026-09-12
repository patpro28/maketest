#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(3, 1000);
    auto N = gen.gen_sum<int>(3e5, t, 1, 1e5);
    auto M = gen.gen_sum<int>(3e5, t, 1, 1e5);
    cout << t << "\n";
    for (int i = 0; i < t; i++) {
        int n = N[i], mx = M[i];
        cout << n << '\n';
        for (int j = 0; j < n; ++j) {
            cout << gen.uniform(1, mx) << (j + 1 == n ? '\n' : ' ');
        }
    }
    return 0;
}
