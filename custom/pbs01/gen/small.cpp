#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int N = 100;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, N);
    int q = gen.uniform(1, N);
    cout << n << '\n';
    for (int i = 1; i <= n; ++i) {
        cout << gen.uniform<int>(1, 100) << ' ';
    }
    cout << '\n';
    cout << q << '\n';
    while (q--) {
        int type = gen.uniform(1, 2);
        if (type == 1) {
            int l = gen.uniform(1, n);
            int v = gen.uniform<int>(1, 100);
            cout << type << ' ' << l << ' ' << v << '\n';
        } else {
            int l = gen.uniform(1, n);
            int r = gen.uniform(l, n);
            int k = gen.uniform(1, r - l + 1);
            cout << type << ' ' << l << ' ' << r << ' ' << k << '\n';
        }
    }
    return 0;
}
