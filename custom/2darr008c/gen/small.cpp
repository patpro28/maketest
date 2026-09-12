#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char *argv[])
{

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int m = gen.uniform(1, 20);
    int n = gen.uniform(1, 20);
    int t = gen.uniform(1, 4000);
    cout << m << " " << n << " " << t << "\n";
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << gen.uniform<int>(-100, 100) << (j == n - 1 ? "\n" : " ");
        }
    }
    for (int i = 0; i < t; i++)
    {
        int x1 = gen.uniform(1, m);
        int y1 = gen.uniform(1, n);
        int x2 = gen.uniform(x1, m);
        int y2 = gen.uniform(y1, n);
        cout << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
    }
    return 0;
}
