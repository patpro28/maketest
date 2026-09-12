#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char *argv[])
{

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 10;
    cout << t << endl;
    while (t--)
    {
        int x = gen.uniform(0, 10);
        int y = gen.uniform(int(x == 0), 10);
        cout << x << " " << y << endl;
    }
    return 0;
}
