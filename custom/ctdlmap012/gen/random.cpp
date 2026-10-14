#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"

int main(int argc, char* argv[]) {
    assert(argc == 2);
    const int seed = std::atoi(argv[1]);
    assert(0 <= seed && seed < 12);
    Random rng(seed + 12012);
    const int n = seed == 0 ? 101 : N_MAX;
    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        switch (seed) {
        case 0: a[i] = 0; break;
        case 1: a[i] = A_MAX; break;
        case 2: a[i] = -A_MAX; break;
        case 3: a[i] = i - n / 2; break;
        case 4: a[i] = n / 2 - i; break;
        case 5: a[i] = i < n / 2 ? -A_MAX : A_MAX; break;
        case 6: a[i] = i % 2 ? A_MAX : -A_MAX; break;
        case 7: {
            const long long values[] = {-A_MAX, -A_MAX + 1, 0, A_MAX - 1, A_MAX};
            a[i] = values[i % 5];
            break;
        }
        case 8: a[i] = rng.uniform<long long>(-5, 5); break;
        case 9: a[i] = rng.uniform<long long>(-A_MAX, A_MAX); break;
        case 10:
            a[i] = i < n / 2 ? rng.uniform<long long>(-A_MAX, A_MAX) : a[i - n / 2];
            break;
        case 11: a[i] = A_MAX - rng.uniform<long long>(0, 1000); break;
        }
    }
    if (seed == 10) rng.shuffle(a.begin() + n / 2, a.end());
    std::cout << n << '\n';
    for (int i = 0; i < n; ++i) std::cout << a[i] << (i + 1 == n ? '\n' : ' ');
}
