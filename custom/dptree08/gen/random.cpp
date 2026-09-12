#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char *argv[])
{

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform<int>(2, 20);
    cout << t << '\n';
    auto N = gen.gen_sum<int>(2e5, t, 1, 1e5);
    while (t--)
    {
        int n = N[t];
        cout << n << '\n';
        for (int i = 0; i < n; ++i)
        {
            int l = gen.uniform<int>(1, 1e9);
            int r = gen.uniform<int>(l, 1e9);
            cout << l << ' ' << r << '\n';
        }
        auto edges = gen.tree<int>(n, true);
        for (auto [u, v] : edges)
        {
            cout << u << ' ' << v << '\n';
        }
    }
    return 0;
}
