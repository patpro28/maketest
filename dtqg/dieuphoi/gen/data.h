#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
inline int generate(int argc, char** argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rng(2026102711ULL + 1000 * mode + seed);
    const int sizes[] = {1,2,3,4,5,6,12,20,200,199,200,200};
    int n = mode == 0 ? sizes[seed] : mode == 1 ? rng.uniform(1, 18) : mode == 2 ? 3000 : int(N_MAX);
    std::vector<long long> a(n), length(n), gap(n);
    for (int i = 0; i < n; ++i) {
        a[i] = rng.uniform(-10000LL, 10000LL); length[i] = rng.uniform(1LL, 5LL); gap[i] = rng.uniform(0LL, 5LL);
        if (mode == 1) a[i] = rng.uniform(-10LL, 10LL);
        if (mode == 0 || mode == 3) {
            if (seed == 0 || seed == 1 || seed == 8) {
                a[i] = seed == 0 ? 0 : seed == 1 ? A_MAX : -A_MAX;
                length[i] = LENGTH_MAX; gap[i] = LENGTH_MAX;
            }
            if (seed == 2) { a[i] = i; length[i] = 1; gap[i] = 0; }
            if (seed == 3) { a[i] = -A_MAX + 2 * i; length[i] = 1; gap[i] = 1; }
            if (seed == 4) { a[i] = 0; length[i] = 1; gap[i] = 0; }
            if (seed == 5) { a[i] = A_MAX - i; length[i] = 1; gap[i] = 0; }
            if (seed == 6) { a[i] = i % 2 ? A_MAX : -A_MAX; length[i] = 1; gap[i] = 0; }
            if (seed == 7) { a[i] = (i / 137) % 2 ? -i : i; length[i] = 1; gap[i] = 0; }
            if (seed == 9) { a[i] = rng.uniform(-A_MAX, A_MAX); length[i] = 1; gap[i] = 0; }
            if (seed == 10) { a[i] = rng.uniform(-A_MAX, A_MAX); length[i] = LENGTH_MAX; gap[i] = 0; }
            if (seed == 11) { a[i] = 2 * i + rng.uniform(-2000, 2000); length[i] = 1; gap[i] = 1; }
        }
    }
    std::cout << n << '\n';
    for (int i = 0; i < n; ++i) std::cout << a[i] << ' ' << length[i] << '\n';
    if (n > 1) {
        for (int i = 0; i + 1 < n; ++i) std::cout << (i ? " " : "") << gap[i];
        std::cout << '\n';
    }
    return 0;
}
