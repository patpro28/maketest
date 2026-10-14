#include <algorithm>
#include <cstdlib>
#include <iostream>
#include "random.h"
#include "../params.h"
using namespace std;
int main(int, char* argv[]) {
    int seed = atoi(argv[1]);
    Random rng(seed);
    cout << T_MAX << '\n';
    for (int i = 0; i < T_MAX; ++i) {
        int n = rng.uniform<int>(2, N_MAX);
        int s = rng.uniform<int>(1, S_MAX);
        switch (seed % 5) {
            case 0: break;
            case 1: n = 2; break;
            case 2: n = rng.uniform<int>(3, 32); break;
            case 3: n = rng.uniform<int>(2, 100000); break;
            case 4: n = rng.uniform<int>(2, 100000); s = max(1, min<int>(S_MAX, n + rng.uniform<int>(-2, 2))); break;
        }
        cout << n << ' ' << s << '\n';
    }
}
