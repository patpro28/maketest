#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char *argv[])
{

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(2, 1e5);
    cout << n << " " << gen.uniform<int>(1, 1e9) << "\n";
    for (int i = 0; i < n; i++)
    {
        cout << gen.uniform<int>(1, 1e9) << (i == n - 1 ? "\n" : " ");
    }
    return 0;
}
