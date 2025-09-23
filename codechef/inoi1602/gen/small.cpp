#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char *argv[])
{

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 10;
    int k = gen.uniform<int>(1, 3);
    cout << n << " " << k << endl;
    for (int i = 0; i < n; i++)
    {
        cout << gen.uniform<int>(-10, 10) << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << gen.uniform<int>(1, 2 * k) << " ";
    }
    cout << endl;
    return 0;
}
