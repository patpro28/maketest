#include <iostream>
#include <vector>
#include <map>
#include "random.h"
#include "../params.h"
using namespace std;

const int N = 20;
const int Q = 100;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, N);
    int q = gen.uniform(10, Q);
    cout << n << ' ' << q << '\n';
    // Generate n different integers for array a
    map<int, bool> used;
    for (int i = 0; i < n; ++i) {
        int x = gen.uniform<int>(-20, 20);
        while (used[x]) {
            x = gen.uniform<int>(-20, 20);
        }
        used[x] = true;
        cout << x << ' ';
    }
    cout << '\n';

    for (int i = 0; i < q; ++i) {
        int l = gen.uniform(1, n);
        int r = gen.uniform(l, n);
        int k = gen.uniform(1, r - l + 1);
        cout << l << ' ' << r << ' ' << k << '\n';
    }

    return 0;
}
