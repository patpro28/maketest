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
        int n = gen.uniform(2, 100);
        string s = gen.lower_string(n);
        cout << n << endl;
        cout << s << endl;
    }
    return 0;
}
