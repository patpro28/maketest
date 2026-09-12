#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char *argv[])
{

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(1, 1e6);

    cout << n << " " << 1 << "\n";
    for (int i = 0; i < n; i++)
    {
        int val = 1;
        cout << val << (i == n - 1 ? "\n" : " ");
    }
    return 0;
}
