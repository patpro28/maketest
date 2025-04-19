#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

vector<int> val;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(1, 100);
    int m = gen.uniform<int>(2, 20);
    val.resize(m);
    for (int i = 0; i < m; ++i) {
        val[i] = gen.uniform<int>(1, 100);
    }
    int l = gen.uniform<int>(1, n);
    int r = gen.uniform<int>(1, n);
    if (l > r) swap(l, r);
    cout << n << ' ' << l << ' ' << r << '\n';
    for (int i = 0; i < n; ++i) {
        cout << val[gen.uniform<int>(0, m - 1)] << ' ';
    }
    return 0;
}
