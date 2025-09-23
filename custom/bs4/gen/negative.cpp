#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 100000);
    cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        long long a = gen.uniform<long long>(-1e12, -100);
        cout << a << ' ';
    }
    cout << '\n';
    int t = gen.uniform(1, 100000);
    cout << t << '\n';
    for (int i = 0; i < t - 1; ++i) {
        long long a = gen.uniform<long long>(-1e12, 1e12);
        if (a == 0) a = gen.uniform<long long>(-1e12, 1e12);
        cout << a << '\n';
    }

    cout << -1 << '\n';

    return 0;
}
