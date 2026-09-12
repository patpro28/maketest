#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char *argv[])
{

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 100;
    cout << t << endl;
    while (t--)
    {
        long long A = gen.uniform<int>(1e4, 100000000);
        long long B = gen.uniform<int>(1e4, 100000000);
        int k = gen.uniform<int>(0, 10);
        cout << A << " " << (k > 0 ? B : A) << endl;
    }
    return 0;
}
