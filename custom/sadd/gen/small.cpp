#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, 100);
    cout << t << '\n';
    while (t--) {
        long long x = gen.uniform(1, 10);
        long long N = 1ll << x;
        long long L = gen.uniform(1ll, N);
        long long R = gen.uniform(L, N);
        cout << N << ' ' << L << ' ' << R << '\n';
    }
    return 0;
}
