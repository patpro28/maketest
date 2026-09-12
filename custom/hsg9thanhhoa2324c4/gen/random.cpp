#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int MAX = 1e8 / 107897;

int main(int, char *argv[])
{

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 3e6;
    cout << n << '\n';
    vector<int> a(n);
    for (auto &x : a)
        x = gen.uniform<int>(1, MAX) * 107897;
    auto b = gen.perm<int>(n);
    for (int i = 0; i < n; i++)
        cout << a[i] << ' ' << b[i] << '\n';
    return 0;
}
