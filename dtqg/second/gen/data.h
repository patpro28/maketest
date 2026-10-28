#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>
#include "random.h"
#include "../params.h"
inline int generate(int argc, char** argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rng(2026102801ULL + 1000 * mode + seed);
    const int sizes[] = {1,2,3,4,5,6,8,10,100,199,200,200};
    int n = mode == 0 ? sizes[seed] : mode == 1 ? rng.uniform(1, 20) : mode == 2 ? 3000 : int(N_MAX);
    std::vector<int> a(n); std::iota(a.begin(), a.end(), 1);
    if (seed == 1) std::reverse(a.begin(), a.end());
    if (seed == 2 || seed == 3) {
        int low = 1, high = n;
        for (int i = 0; i < n; ++i) a[i] = (i % 2 == (seed == 2 ? 0 : 1)) ? high-- : low++;
    }
    if (seed == 4 || seed == 5) {
        a.clear();
        if (seed == 4) {
            for (int x = 1; x <= n; x += 2) a.push_back(x);
            for (int x = n - n % 2; x >= 2; x -= 2) a.push_back(x);
        } else {
            for (int x = n - n % 2; x >= 2; x -= 2) a.push_back(x);
            for (int x = 1; x <= n; x += 2) a.push_back(x);
        }
    }
    if (seed == 6) std::rotate(a.begin(), a.begin() + n / 3, a.end());
    if (seed == 7) for (int i = 1; i < n; i += 2) std::swap(a[i - 1], a[i]);
    if (seed == 9 || seed == 11) {
        int block = seed == 9 ? 37 : 101;
        for (int l = 0; l < n; l += block) std::reverse(a.begin() + l, a.begin() + std::min(n, l + block));
    }
    if (seed == 10) {
        const int p[] = {2,1,5,3,4,8,6,7};
        for (int l = 0; l + 8 <= n; l += 8) for (int j = 0; j < 8; ++j) a[l + j] = l + p[j];
    }
    if (mode == 2 || seed == 8 || (mode == 1 && seed % 3 == 1))
        for (int i = n - 1; i > 0; --i) std::swap(a[i], a[rng.uniform(0, i)]);
    std::cout << n << '\n';
    for (int i = 0; i < n; ++i) std::cout << (i ? " " : "") << a[i];
    std::cout << '\n'; return 0;
}
