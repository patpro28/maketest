#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
#include "random.h"
#include "../params.h"
inline int generate(int argc, char** argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rng(2026102804ULL + 1000 * mode + seed);
    const int sizes[] = {1,2,3,4,5,6,8,12,100,199,2000,2000};
    int n = mode == 0 ? sizes[seed] : mode == 1 ? rng.uniform(1, 25) : mode == 2 ? 2000 : int(N_MAX);
    int q = mode == 0 ? (seed == 0 ? 1 : seed >= 10 ? 2000 : seed + 3)
          : mode == 1 ? rng.uniform(1, 40) : mode == 2 ? 2000 : int(Q_MAX);
    int stem = std::max(1, n / 2);
    std::vector<int> a(n), depth(n, 1), label(n);
    std::iota(label.begin(), label.end(), 0);
    std::vector<std::pair<int, int>> edges;
    for (int v = 1; v < n; ++v) {
        int p;
        if (seed <= 2 || seed == 10) p = v - 1;
        else if (seed == 3 || seed == 4) p = v < stem ? v - 1 : stem - 1;
        else if (seed == 5) p = 0;
        else if (seed == 6) p = (v - 1) / 2;
        else if (seed == 7 || seed == 11) p = v < stem ? v - 1 : v - stem;
        else if (seed == 9) p = v <= 4 ? 0 : v - 4;
        else p = rng.uniform(0, v - 1);
        edges.push_back({p, v}); depth[v] = depth[p] + 1;
    }
    for (int i = 0; i < n; ++i) {
        a[i] = rng.uniform(0, mode <= 1 ? 10 : int(VALUE_MAX));
        if (seed == 0) a[i] = i + 1;
        if (seed == 1) a[i] = n - i;
        if (seed == 2) a[i] = int(VALUE_MAX);
        if (seed == 3) a[i] = i < stem ? 1000000 + i : i % 1000 + 1;
        if (seed == 4) a[i] = i < stem ? i + 1 : rng.uniform(1, stem);
        if (seed == 5 && i == 0) a[i] = int(VALUE_MAX);
        if (seed == 6) a[i] = rng.uniform(0, 7);
        if (seed == 10) a[i] = (i / 97) % 11;
        if (seed == 11 && i >= stem) a[i] = 1;
    }
    if (seed % 2) for (int i = n - 1; i > 1; --i) std::swap(label[i], label[rng.uniform(1, i)]);
    std::vector<int> printed(n);
    for (int i = 0; i < n; ++i) printed[label[i]] = a[i];
    for (int i = int(edges.size()) - 1; i > 0; --i) std::swap(edges[i], edges[rng.uniform(0, i)]);
    std::cout << n << ' ' << q << '\n';
    for (int i = 0; i < n; ++i) std::cout << (i ? " " : "") << printed[i];
    std::cout << '\n';
    for (auto [u, v] : edges) {
        if (rng.uniform_bool()) std::swap(u, v);
        std::cout << label[u] + 1 << ' ' << label[v] + 1 << '\n';
    }
    for (int i = 0; i < q; ++i) {
        int v = rng.uniform(0, n - 1);
        if ((seed == 3 || seed == 4) && n > stem && i % 3) v = rng.uniform(stem, n - 1);
        if (seed <= 2 && i % 4) v = n - 1;
        if (i % 19 == 0) v = 0;
        int k = i % 5 == 0 ? 1 : i % 5 == 1 ? depth[v] : i % 5 == 2 ? std::max(1, depth[v] / 2) : rng.uniform(1, depth[v]);
        std::cout << label[v] + 1 << ' ' << k << '\n';
    }
    return 0;
}
