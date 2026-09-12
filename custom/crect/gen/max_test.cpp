#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char *argv[])
{

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int m = gen.uniform(400, 500);
    int n = gen.uniform(400, 500);
    cout << m << ' ' << n << '\n';
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            char c = gen.uniform('A', 'C');
            cout << c;
        }
        cout << '\n';
    }
    return 0;
}
