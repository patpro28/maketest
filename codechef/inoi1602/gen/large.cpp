#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char *argv[])
{

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 700;
    int k = 7;
    cout << n << " " << k << endl;
    for (int i = 0; i < n; i++)
    {
        cout << gen.uniform<int>(-1e6, 1e6) << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << gen.uniform<int>(1, 2 * k) << " ";
    }
    cout << endl;
    return 0;
}
