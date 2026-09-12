#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char *argv[])
{
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);
    int n = gen.uniform<int>(1, 1e5);
    int k = gen.uniform<int>(0, n);
    auto edges = gen.tree<int>(n);
    vector<int> c(n, 0);
    for (auto [u, v] : edges)
    {
        if (c[v] == 0)
            c[v] = gen.uniform(1, 3);
        c[u] = gen.uniform(1, 3);
        while (c[u] == c[v])
            c[u] = gen.uniform(1, 3);
    }
    auto perm = gen.perm<int>(n);
    for (int i = 0; i < n - k; ++i)
        c[perm[i]] = 0;
    cout << n << ' ' << k << '\n';
    for (auto [u, v] : edges)
        cout << u + 1 << ' ' << v + 1 << '\n';
    for (int i = 0; i < n; ++i)
    {
        if (c[i] != 0)
            cout << i + 1 << ' ' << c[i] << '\n';
    }
    return 0;
}
