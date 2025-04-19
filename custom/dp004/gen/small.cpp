#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char *argv[])
{

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 100);
    cout << n << endl;
    for (int i = 0; i < n; ++i)
        cout << gen.uniform(1, 100) << " \n"[i == n - 1];
    for (int i = 1; i < n; ++i)
        cout << gen.uniform(1, 200) << " \n"[i == n - 1];
    return 0;
}
