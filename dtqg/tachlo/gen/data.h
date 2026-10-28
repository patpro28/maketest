#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rng(2026102703ULL + mode * 1000 + seed);
    const int sizes[] = {1, 2, 3, 4, 5, 6, 12, 20, 200, 199, 200, 200};
    int n = mode == 0 ? sizes[seed] : mode == 1 ? 200 : mode == 2 ? 3000 : int(N_MAX);
    int k = seed % 4 == 0 ? 1 : std::min(n, 20 - seed % 5);
    if (mode == 0 && (seed == 1 || seed == 7)) k = n;
    if (mode == 3 && (seed == 1 || seed == 3 || seed == 4 || seed == 11 || seed == 13)) k = 20;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        if (seed == 0 || seed == 1 || (mode == 0 && seed == 8)) a[i] = n;
        else if (seed == 2 || seed == 3) a[i] = i + 1;
        else if (seed == 4) a[i] = i % std::min(n, 2) + 1;
        else if (seed == 5) a[i] = i % std::min(n, 3) + 1;
        else if (seed == 6 || seed == 7) a[i] = i / 2 + 1;
        else if (seed == 8) a[i] = rng.uniform(1, std::min(n, 7));
        else if (seed == 9) a[i] = rng.uniform(1, n);
        else if (seed == 10) a[i] = (i / 37) % std::min(n, 13) + 1;
        else if (seed == 11) a[i] = i % 997 == 0 ? n : 1;
        else if (seed == 12) a[i] = rng.uniform(1, std::min(n, 100));
        else a[i] = i % 5000 + 1;
    }
    if (seed == 7) for (int i = n - 1; i > 0; --i) std::swap(a[i], a[rng.uniform(0, i)]);
    std::cout << n << ' ' << k << '\n';
    for (int i = 0; i < n; ++i) std::cout << (i ? " " : "") << a[i];
    std::cout << '\n';
    return 0;
}
