#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char *argv[])
{
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    vector<int> a(6);
    for (auto &x : a)
        x = gen.uniform<int>(1, 1e9);

    int n = gen.uniform(2, 25);
    int k = gen.uniform(0, 1);
    if (k)
        n = 25;
    cout << n << '\n';
    for (int i = 0; i < n; ++i)
        cout << a[gen.uniform(0, 9)] << ' ';

    return 0;
}
