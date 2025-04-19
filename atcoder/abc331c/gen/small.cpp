#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int NMIN = 1;
const int NMAX = 2000;
const int AMAX = 100;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(NMIN, NMAX);
    cout << n << '\n';
    for (int i = 0; i < n; ++i)
        cout << gen.uniform(1, AMAX) << " \n"[i == n - 1];
    return 0;
}
