#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char *argv[])
{

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(5e5, 1e6);
    cout << n << ' ' << gen.uniform<int>(n / 1000, n / 10) << '\n';
    for (int i = 0; i < n; ++i)
    {
        cout << gen.uniform<int>(-1e9, 1e9) << (i == n - 1 ? '\n' : ' ');
    }
    return 0;
}
