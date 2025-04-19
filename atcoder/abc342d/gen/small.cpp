#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int NMIN = 2000;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(2, NMIN);
    cout << n << '\n';
    for (int i = 0; i < n - 2; ++i)
        cout << gen.uniform(0, NMIN) << " ";
    cout << 1 << ' ';
    cout << 0 << '\n';
    return 0;
}
