#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char *argv[])
{

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform<int>(1, 10);
    auto N = gen.gen_sum<int>(500, t, 3);
    auto Q = gen.gen_sum<int>(500, t);
    cout << t << '\n';
    while (t--)
    {
        int n = N[t];
        int q = Q[t];

        vector<int> a(n);
        for (int i = 0; i < n; i++)
        {
            a[i] = gen.uniform<int>(1, 100);
        }
        cout << n << " " << q << '\n';
        for (int i = 0; i < n; i++)
        {
            cout << a[i] << (i == n - 1 ? '\n' : ' ');
        }
        int64_t max_k = int64_t(n - 1) * (n - 2) * (n - 3) / 6;
        while (q--)
        {
            cout << gen.uniform<int64_t>(1, max_k) << '\n';
        }
    }

    return 0;
}
