#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char *argv[])
{

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(1e4, 1e6);
    int k = gen.uniform<int>(1, n);

    cout << n << " " << k << "\n";
    for (int i = 0; i < n; i++)
    {
        int val = gen.uniform<int>(0, 1);
        cout << val << (i == n - 1 ? "\n" : " ");
    }
    return 0;
}
