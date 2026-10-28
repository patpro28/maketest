#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
#include "random.h"
#include "../params.h"
inline int generate(int argc, char** argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rng(2026102803ULL + 1000 * mode + seed);
    const int sizes[] = {1,2,3,4,5,6,9,20,100,199,200,200};
    int n = mode == 0 ? sizes[seed] : mode == 1 ? rng.uniform(1, 25) : mode == 2 ? 3000 : int(N_MAX);
    int q = mode == 0 ? std::max(3, seed + 1) : mode == 1 ? rng.uniform(1, 40) : mode == 2 ? 3000 : int(Q_MAX);
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = rng.uniform(0, mode == 1 ? 8 : int(VALUE_MAX));
        if (mode == 0 || mode == 3) {
            if (seed == 0) a[i] = 0;
            if (seed == 1) a[i] = int(VALUE_MAX);
            if (seed == 2) a[i] = i + 1;
            if (seed == 3) a[i] = n - i;
            if (seed == 4) a[i] = i % 2 ? int(VALUE_MAX) : 0;
            if (seed == 5) a[i] = i % 7;
            if (seed == 6) a[i] = int(VALUE_MAX) - i / 100;
            if (seed == 8) a[i] = i % 101 ? int(VALUE_MAX) : 0;
            if (seed == 9) a[i] = i % 1000;
            if (seed == 10) a[i] = i == n / 2 ? 0 : int(VALUE_MAX);
            if (seed == 11) a[i] = rng.uniform(0, 5);
        }
    }
    std::vector<std::pair<int, int>> queries;
    for (int i = 0; i < q; ++i) {
        int l = rng.uniform(1, n), r = rng.uniform(1, n);
        if (l > r) std::swap(l, r);
        if (mode == 3 && seed % 4 == 0 && i % 5) { l = 1; r = n; }
        if (mode == 3 && seed == 2) l = 1;
        if (mode == 3 && seed == 3) r = n;
        if (i == 0) { l = 1; r = n; }
        if (i == 1) l = r = n;
        if (i == 2) l = r = 1;
        queries.push_back({l, r});
    }
    std::cout << n << ' ' << q << '\n';
    for (int i = 0; i < n; ++i) std::cout << (i ? " " : "") << a[i];
    std::cout << '\n';
    for (auto [l, r] : queries) std::cout << l << ' ' << r << '\n';
    return 0;
}
