#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int NMIN = 20000;
const int NMAX = 200000;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(NMAX, NMAX);
    cout << n << '\n';
    for (int i = 0; i < n; ++i)
        cout << gen.uniform(0, 1) << " \n"[i == n - 1];
    return 0;
}
