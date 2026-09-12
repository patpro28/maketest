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
        long long A = gen.uniform<int>(1LL, 1000);
        long long B = gen.uniform<int>(1LL, 1000);
        int k = 1;
        cout << A << " " << (k > 0 ? B : A) << endl;
    }
    return 0;
}
