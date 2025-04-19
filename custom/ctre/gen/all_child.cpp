#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);
    int n = gen.uniform(3, 15);
    cout << n << '\n';
    for (int i = 2; i <= n; ++i)
        cout << 1 << ' ' << i << '\n';
    return 0;
}
