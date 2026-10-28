#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
inline int generate(int argc, char** argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rng(2026102712ULL + 1000 * mode + seed);
    int n = mode == 0 ? (seed == 0 ? 1 : seed < 4 ? 2 : seed < 8 ? 4 + seed : 200)
          : mode == 1 ? rng.uniform(1, 18) : mode == 2 ? 2000 : int(N_MAX);
    std::vector<long long> l(n), r(n), u(n), v(n);
    for (int i = 0; i < n; ++i) {
        l[i] = rng.uniform(-10LL, 10LL); r[i] = l[i] + rng.uniform(0LL, 5LL);
        u[i] = rng.uniform(0LL, 5LL); v[i] = rng.uniform(0LL, 5LL);
        if (mode == 2 && seed % 2) { l[i] *= 1000000; r[i] *= 1000000; }
        if (mode == 0 || mode == 3) {
            l[i] = r[i] = rng.uniform(-VALUE_MAX, VALUE_MAX);
            u[i] = rng.uniform(0LL, 100LL); v[i] = rng.uniform(0LL, 100LL);
            if (seed == 0) { l[i] = -20; r[i] = 20; u[i] = v[i] = VALUE_MAX; }
            if (seed == 1) { l[i] = r[i] = i % 2 ? VALUE_MAX : -VALUE_MAX; u[i] = v[i] = 0; }
            if (seed == 2) { l[i] = r[i] = i % 2 ? VALUE_MAX : 0; u[i] = v[i] = VALUE_MAX; }
            if (seed == 3) u[i] = 0;
            if (seed == 4) v[i] = 0;
            if (seed == 5) { l[i] = r[i] = i; u[i] = 0; v[i] = 1; }
            if (seed == 6) { l[i] = r[i] = -i; u[i] = 1; v[i] = 0; }
            if (seed == 7) { l[i] = i % 3 ? -VALUE_MAX : VALUE_MAX; r[i] = i % 3 ? VALUE_MAX : VALUE_MAX; }
            if (seed == 8) { u[i] = v[i] = i % 1000 == 0 ? VALUE_MAX : 0; }
            if (seed == 9) { l[i] = r[i] = VALUE_MAX; u[i] = v[i] = VALUE_MAX; }
            if (seed == 10) { l[i] = r[i] = i % 2 ? VALUE_MAX : -VALUE_MAX; u[i] = 1; v[i] = 3; }
            if (seed == 11) {
                l[i] = rng.uniform(-2LL, 2LL); r[i] = l[i] + rng.uniform(0LL, 2LL);
                u[i] = rng.uniform(0LL, 2LL); v[i] = rng.uniform(0LL, 2LL);
            }
        }
    }
    std::cout << n << '\n';
    for (int i = 0; i < n; ++i) std::cout << l[i] << ' ' << r[i] << '\n';
    for (int i = 0; i + 1 < n; ++i) std::cout << u[i] << ' ' << v[i] << '\n';
    return 0;
}
