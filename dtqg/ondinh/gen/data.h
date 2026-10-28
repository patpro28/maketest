#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
inline int generate(int argc, char** argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rng(2026102713ULL + 1000 * mode + seed);
    const int sizes[] = {1,2,3,4,5,6,8,10,20,30,100,100};
    int n = mode == 0 ? sizes[seed] : mode == 1 ? rng.uniform(1, 18) : mode == 2 ? 1000 : int(N_MAX);
    std::vector<long long> a(n), w(n), c(n);
    for (int i = 0; i < n; ++i) {
        a[i] = rng.uniform(0LL, 30LL); w[i] = rng.uniform(1LL, 30LL); c[i] = rng.uniform(1LL, 30LL);
        if (mode == 0 || mode == 3) {
            a[i] = rng.uniform(0LL, VALUE_MAX); w[i] = rng.uniform(1LL, VALUE_MAX); c[i] = rng.uniform(1LL, VALUE_MAX);
            if (seed == 0) a[i] = 123456;
            if (seed == 1) { a[i] = i % 2 ? VALUE_MAX : 0; w[i] = VALUE_MAX; c[i] = 1; }
            if (seed == 2) { a[i] = i % 2 ? VALUE_MAX : 0; w[i] = 1; c[i] = VALUE_MAX; }
            if (seed == 3) { a[i] = i % 2 ? VALUE_MAX : 0; w[i] = c[i] = VALUE_MAX; }
            if (seed == 5) {
                a[i] = i < n / 2 ? i + 1 : i % 2 ? VALUE_MAX : 0;
                w[i] = i < n / 2 ? 1 : 1000; c[i] = VALUE_MAX;
            }
            if (seed == 6) { c[i] = i % 2 ? 1 : VALUE_MAX; w[i] = i % 3 ? 7 : VALUE_MAX; }
            if (seed == 7) { a[i] = i % 2; w[i] = VALUE_MAX; c[i] = i % 3 + 1; }
            if (seed == 8) { a[i] = VALUE_MAX - i; w[i] = i % 3 + 1; c[i] = VALUE_MAX; }
            if (seed == 9) { w[i] = c[i] = 1; }
            if (seed == 10) { a[i] = i == 0 ? VALUE_MAX / 2 : i % 2 ? VALUE_MAX : 0; w[i] = i == 0 ? VALUE_MAX : 1; }
            if (seed == 11) { a[i] = rng.uniform(0LL, 4LL); }
        }
    }
    std::cout << n << '\n';
    for (int i = 0; i < n; ++i) std::cout << a[i] << ' ' << w[i] << '\n';
    if (n > 1) {
        for (int i = 0; i + 1 < n; ++i) std::cout << (i ? " " : "") << c[i];
        std::cout << '\n';
    }
    return 0;
}
