#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char *argv[])
{

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(1e5, 1e6);
    int l = 1;

    cout << n << ' ' << l << '\n';
    for (int i = 0; i < n; ++i)
    {
        bool small = gen.uniform_bool();
        if (small)
        {
            cout << gen.uniform<int>(1, 2000) << ' ';
        }
        else
        {
            cout << gen.uniform<long long>(1, 1e9) << ' ';
        }
    }
    cout << '\n';
    return 0;
}
