#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 2000);
    int k = gen.uniform<int>(0, 10000);
    int m = 2;
    cout << n << ' ' << k << ' ' << m << endl;
    for (int i = 0; i < n; ++i)
        cout << gen.uniform<int>(1, 1e6) << ' ';
    return 0;
}
