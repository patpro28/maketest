#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 50000);
    int k = gen.uniform<int>(0, 100);
    int m = 1;
    cout << n << ' ' << k << ' ' << m << endl;
    for (int i = 0; i < n; ++i)
        cout << gen.uniform<int>(1, 1e4) << ' ';
    return 0;
}
