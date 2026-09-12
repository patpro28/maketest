#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char *argv[])
{

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform<int>(1, 1e4);
    int k = gen.uniform<int>(1, 10);
    if (k == 1)
        t = 1;
    cout << t << endl;
    auto N = gen.gen_sum<int>(2e5, t, 2);
    while (t--)
    {
        int n = N[t];
        cout << n << endl;
        for (int i = 0; i < n; ++i)
        {
            cout << gen.uniform<int>(0, 1e9) << (i == n - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
