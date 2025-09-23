#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 100000;
    int k = gen.uniform<int>(1, 99);
    cout << t << ' ' << k << '\n';
    while (t--) {
        long long a = gen.uniform<long long>(1e6, 1e9);
        long long b = gen.uniform<long long>(a + 1, 1e18);
        cout << a << ' ' << b << '\n';
    }
    return 0;
}

