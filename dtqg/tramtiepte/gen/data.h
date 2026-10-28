#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>
#include "random.h"
#include "../params.h"
struct Edge { int u, v, w; };
inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rng(2026102501ULL + 1000 * mode + seed);
    int n = mode == 0 ? (seed < 2 ? 1 : seed == 2 ? 2 : 4 + seed)
          : mode == 1 ? rng.uniform(1, 35)
          : mode == 2 ? rng.uniform(500, 3000) : int(N_MAX);
    int shape = seed % 5;
    if (mode == 0 && seed == 10) n = 8;
    std::vector<long long> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        a[i] = rng.uniform(0LL, A_MAX);
        b[i] = rng.uniform(0LL, seed % 2 ? B_MAX : 1000LL);
    }
    std::vector<Edge> edges;
    for (int v = 1; v < n; ++v) {
        int p = shape == 0 ? v - 1 : shape == 1 ? 0 : shape == 2 ? (v - 1) / 2
              : shape == 3 ? (v < n / 2 ? v - 1 : n / 2 - 1) : rng.uniform(0, v - 1);
        edges.push_back({p, v, rng.uniform(1, int(W_MAX))});
    }
    if (mode == 0 || mode == 3) {
        if (seed <= 3 || seed == 10) {
            std::fill(a.begin(), a.end(), A_MAX);
            std::fill(b.begin(), b.end(), 0);
            for (auto &e : edges) e.w = int(W_MAX);
        }
        if (seed == 0 && mode == 0) a[0] = 0;
        if (seed == 1 && mode == 0) b[0] = B_MAX;
        if (seed == 4) std::fill(a.begin(), a.end(), 0);
        if (seed == 5) {
            std::fill(a.begin(), a.end(), 0);
            std::fill(b.begin(), b.end(), 0);
            a.back() = A_MAX;
        }
        if (seed == 6 || seed == 11) {
            std::fill(a.begin(), a.end(), 1);
            std::fill(b.begin(), b.end(), B_MAX);
            b.back() = 0;
            for (auto &e : edges) e.w = 1;
        }
        if (seed == 7) {
            std::fill(a.begin(), a.end(), A_MAX);
            std::fill(b.begin(), b.end(), B_MAX);
        }
        if (seed == 8) {
            std::fill(a.begin(), a.end(), 0);
            std::fill(b.begin(), b.end(), B_MAX);
        }
    }
    std::vector<int> label(n);
    std::iota(label.begin(), label.end(), 0);
    for (int i = n - 1; i > 0; --i) std::swap(label[i], label[rng.uniform(0, i)]);
    std::vector<long long> pa(n), pb(n);
    for (int i = 0; i < n; ++i) { pa[label[i]] = a[i]; pb[label[i]] = b[i]; }
    for (int i = int(edges.size()) - 1; i > 0; --i)
        std::swap(edges[i], edges[rng.uniform(0, i)]);
    std::cout << n << '\n';
    for (int i = 0; i < n; ++i) std::cout << (i ? " " : "") << pa[i];
    std::cout << '\n';
    for (int i = 0; i < n; ++i) std::cout << (i ? " " : "") << pb[i];
    std::cout << '\n';
    for (auto e : edges) {
        if (rng.uniform_bool()) std::swap(e.u, e.v);
        std::cout << label[e.u] + 1 << ' ' << label[e.v] + 1 << ' ' << e.w << '\n';
    }
    return 0;
}
