#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rng(2026102503ULL + 1000 * mode + seed);
    int n = mode == 0 ? 1 + seed : mode == 1 ? rng.uniform(1, 40)
          : mode == 2 ? rng.uniform(1000, 3000) : int(N_MAX);
    int l = rng.uniform(1, n), r = rng.uniform(l, n);
    long long c = rng.uniform(0LL, VALUE_MAX);
    std::vector<long long> h(n);
    for (auto &x : h) x = rng.uniform(1LL, seed % 3 ? VALUE_MAX : 5LL);
    if (mode == 0) {
        if (seed == 0) { l = r = 1; c = 0; h[0] = VALUE_MAX; }
        if (seed == 1) { l = r = 1; c = VALUE_MAX; }
        if (seed == 2) { l = r = 2; }
        if (seed == 3) { l = r = n; }
        if (seed == 4) { l = 1; r = n; c = 0; }
        if (seed == 5) { l = 2; r = 3; c = 4; h = {1, 2, 10, 11, 3, 4}; }
        if (seed == 6) { l = 2; r = 3; std::fill(h.begin(), h.end(), 8); }
        if (seed == 7) { l = 3; r = 5; for (int i = 0; i < n; ++i) h[i] = i + 1; }
        if (seed == 8) { l = 2; r = 6; for (int i = 0; i < n; ++i) h[i] = n - i; }
        if (seed == 9) { l = 3; r = 7; for (int i = 0; i < n; ++i) h[i] = i % 2 ? VALUE_MAX : 1; }
        if (seed == 10) { l = 6; r = 10; }
        if (seed == 11) { l = 4; r = 5; c = 0; }
    } else if (mode == 1) {
        if (seed % 3 == 0) { l = 1; r = n; }
        if (seed % 3 == 1) r = l;
        if (seed % 4 == 0) c = 0;
    } else if (mode == 3) {
        if (seed == 0) { l = r = 1; c = VALUE_MAX; }
        if (seed == 1) { l = r = n; }
        if (seed == 2) { l = 1; r = n; c = 0; }
        if (seed == 3) { l = 333; r = 1000; std::fill(h.begin(), h.end(), VALUE_MAX); }
        if (seed == 4) { l = 2; r = n; for (int i = 0; i < n; ++i) h[i] = i + 1; }
        if (seed == 5) { l = 2; r = n; for (int i = 0; i < n; ++i) h[i] = n - i; }
        if (seed == 6) { l = 17; r = 100003; for (int i = 0; i < n; ++i) h[i] = i % 2 ? VALUE_MAX : 1; }
        if (seed == 7) { l = n / 2 + 1; r = n - 1; }
        if (seed == 8) { l = 1; r = n; c = VALUE_MAX; }
        if (seed == 9) { l = 400; r = 1200; for (int i = 0; i < n; ++i) h[i] = (i / 37) % 7 + 1; }
    }
    std::cout << n << ' ' << l << ' ' << r << ' ' << c << '\n';
    for (int i = 0; i < n; ++i) std::cout << (i ? " " : "") << h[i];
    std::cout << '\n';
    return 0;
}
