#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>
#include "random.h"
#include "../params.h"
struct Edge { int u, v; long long d; };
inline int generate(int argc, char** argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rng(2026102714ULL + 1000 * mode + seed);
    int n = mode == 0 ? (seed == 0 ? 1 : seed == 1 ? 2 : seed < 8 ? seed + 2 : 200)
          : mode == 1 ? rng.uniform(1, 18) : mode == 2 ? 500 : int(N_MAX);
    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = rng.uniform(-10LL, 10LL);
        if (mode == 0 || mode == 3) {
            a[i] = rng.uniform(-VALUE_MAX, VALUE_MAX);
            if (seed == 0 || seed == 2 || seed == 10) a[i] = i % 2 ? VALUE_MAX : -VALUE_MAX;
            if (seed == 4) a[i] = rng.uniform(0LL, VALUE_MAX);
            if (seed == 5) a[i] = 0;
            if (seed == 7) a[i] = rng.uniform(0LL, 4LL);
            if (seed == 8) a[i] = i;
            if (seed == 9) a[i] = i == 0 ? VALUE_MAX : 0;
        }
    }
    std::vector<Edge> edges;
    int shape = seed % 8;
    for (int v = 1; v < n; ++v) {
        int p = shape == 0 ? v - 1 : shape == 1 ? 0 : shape == 2 ? (v - 1) / 2
              : shape == 3 ? (v < n / 2 ? v - 1 : n / 2 - 1)
              : shape == 4 ? rng.uniform(0, v - 1) : shape == 5 ? (v <= 4 ? 0 : v - 4)
              : shape == 6 ? (v < n / 2 ? v - 1 : v - n / 2)
              : rng.uniform(std::max(0, v - 20), v - 1);
        long long d = rng.uniform(0LL, 5LL);
        if (mode == 0 || mode == 3) {
            d = rng.uniform(0LL, VALUE_MAX);
            if (seed == 0 || seed == 1 || seed == 2 || seed == 8) d = 0;
            if (seed == 3 || seed == 10) d = v % 2;
            if (seed == 4 || seed == 5) d = VALUE_MAX;
            if (seed == 7) d = rng.uniform(0LL, 2LL);
            if (seed == 11) d = v % 3 ? 0 : VALUE_MAX;
        }
        edges.push_back({p, v, d});
    }
    std::vector<int> label(n); std::iota(label.begin(), label.end(), 0);
    if (seed % 2) for (int i = n - 1; i > 0; --i) std::swap(label[i], label[rng.uniform(0, i)]);
    std::vector<long long> printed(n);
    for (int i = 0; i < n; ++i) printed[label[i]] = a[i];
    for (int i = int(edges.size()) - 1; i > 0; --i) std::swap(edges[i], edges[rng.uniform(0, i)]);
    std::cout << n << '\n';
    for (int i = 0; i < n; ++i) std::cout << (i ? " " : "") << printed[i];
    std::cout << '\n';
    for (auto e : edges) {
        if (rng.uniform_bool()) std::swap(e.u, e.v);
        std::cout << label[e.u] + 1 << ' ' << label[e.v] + 1 << ' ' << e.d << '\n';
    }
    return 0;
}
