#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int N = 200000;
const int Q = 200000;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, N);
    int q = gen.uniform(1, Q);
    cout << n << ' ' << q << '\n';
    for (int i = 0; i < n; ++i) {
        int x = gen.uniform<int>(1, 2e5);
        cout << x << ' ';
    }
    cout << '\n';

    for (int i = 0; i < q; ++i) {
        int l = gen.uniform(1, n);
        int r = gen.uniform(l, n);
        cout << l << ' ' << r << '\n';
    }

    return 0;
}
