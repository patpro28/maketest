#include <cstdlib>
#include <iostream>
#include "random.h"
using namespace std;
int main(int, char* argv[]) {
    int seed = atoi(argv[1]);
    Random rng(seed);
    int n = rng.uniform(1, seed < 10 ? 30 : 10000);
    cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        int a;
        switch (seed % 5) {
            case 0: a = rng.uniform(1, n); break;
            case 1: a = rng.uniform(1, 1000000000); break;
            case 2: a = rng.uniform(1, 1 + n/5); break;
            case 3: a = rng.uniform(1, 2*n); break;
            default: a = rng.uniform_bool() ? rng.uniform(1,n) : 1000000000;
        }
        cout << a << (i+1 == n ? '\n' : ' ');
    }
}
