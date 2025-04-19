#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int NMAX = 100;
const int QMAX = 2e5;
const int AMAX = 1e8;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, NMAX);
    int m = gen.uniform(1, NMAX);
    int l = gen.uniform(1, NMAX);
    vector<int> a(n), b(m), c(l);
    for (auto &x: a) x = gen.uniform(0, AMAX);
    for (auto &x: b) x = gen.uniform(0, AMAX);
    for (auto &x: c) x = gen.uniform(0, AMAX);
    vector<int> vals;
    for (auto x: a) vals.push_back(x);
    for (auto x: b) vals.push_back(x);
    for (auto x: c) vals.push_back(x);
    for (int i = 0; i < m * n * l; ++i)
        vals.push_back(gen.uniform(0, 3 * AMAX));
    sort(vals.begin(), vals.end());
    cout << n << '\n';
    for (int i = 0; i < n; ++i)
        cout << a[i] << " \n"[i == n - 1];
    cout << m << '\n';
    for (int i = 0; i < m; ++i)
        cout << b[i] << " \n"[i == m - 1];
    cout << l << '\n';
    for (int i = 0; i < l; ++i)
        cout << c[i] << " \n"[i == l - 1];
    int q = gen.uniform(1000, QMAX);
    cout << q << '\n';
    for (int i = 0; i < q; ++i) {
        int x = gen.uniform(0, (int) vals.size() - 1);
        cout << vals[x] << ' ';
    }

    return 0;
}
