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
        int n = gen.uniform(1, 100);
        vector<int> arr(n + 1);
        for (int i = 0; i <= n; i++)
        {
            arr[i] = gen.uniform(1, 100);
        }
        cout << n << endl;
        for (int i = 0; i <= n; i++)
        {
            cout << arr[i] << (i == n ? '\n' : ' ');
        }
    }
    return 0;
}
