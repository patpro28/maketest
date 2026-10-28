#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>
#include "random.h"
#include "../params.h"
struct Edge { int u, v, c, w; };
inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rng(2026102502ULL + 1000 * mode + seed);
    int n = mode == 0 ? 2 + seed : mode == 1 ? rng.uniform(1, 20)
          : mode == 2 ? rng.uniform(500, 2000) : int(N_MAX);
    int m = mode == 0 ? seed * 3 : mode == 1 ? rng.uniform(0, 70)
          : mode == 2 ? rng.uniform(2000, 6000) : int(M_MAX);
    int s = 0, t = n - 1;
    std::vector<long long> p(n);
    for (auto &x : p) x = rng.uniform(0LL, seed % 2 ? VALUE_MAX : 15LL);
    std::vector<Edge> edges;
    if (mode == 0 && seed <= 3) {
        if (seed == 0) { n = 1; s = t = 0; p.assign(1, VALUE_MAX); }
        if (seed == 1) { n = 2; t = 1; p.assign(2, 0); }
        if (seed == 2) {
            n = 3; t = 2; p.assign(3, VALUE_MAX);
            edges = {{0, 1, 1000000000, 1}, {1, 2, 1000000000, 2}};
        }
        if (seed == 3) {
            n = 4; t = 3; p = {0, 100, 0, 0};
            edges = {{0, 1, 1, 1}, {0, 2, 2, 2}, {2, 1, 2, 2}, {1, 3, 2, 1}};
        }
    } else if (mode == 3 && seed <= 3) {
        for (int i = 0; i < m; ++i) {
            int u = i % n, v = (i + 1) % n;
            int c = seed == 0 ? 1000000000 : i + 1;
            edges.push_back({u, v, c, int(VALUE_MAX)});
        }
        std::fill(p.begin(), p.end(), seed == 2 ? 0 : VALUE_MAX);
        if (seed == 3) t = s;
    } else if (mode == 3 && seed == 8) {
        // Quadratic last-edge transitions: many incoming and outgoing lines.
        std::fill(p.begin(), p.end(), VALUE_MAX);
        for (int i = 0; i < m; ++i) {
            if (i < m / 2) edges.push_back({0, 1, i + 1, 1});
            else edges.push_back({1, n - 1, i + 1, 1});
        }
    } else if (mode == 3 && (seed == 4 || seed == 5)) {
        // Many lines at one hub: explicit line-to-line edges would be quadratic.
        std::fill(p.begin(), p.end(), VALUE_MAX);
        edges.push_back({0, 1, 1, 1});
        for (int i = 1; i < m; ++i) {
            int v = i == m - 1 ? n - 1 : 2 + i % (n - 2);
            edges.push_back({1, v, seed == 4 ? i + 1 : 1, 1});
        }
    } else {
        int usable = mode == 3 && seed == 6 ? n - 1 : n;
        for (int i = 0; i < m; ++i) {
            int u = rng.uniform(0, usable - 1), v = rng.uniform(0, usable - 1);
            int c = seed % 3 == 0 ? 1000000000 : seed % 3 == 1 ? i + 1 : rng.uniform(1, 5);
            int w = rng.uniform(1, seed % 2 ? int(VALUE_MAX) : 20);
            edges.push_back({u, v, c, w});
        }
        if (mode == 0 && seed == 4) s = t;
        if (mode == 0 && seed == 5) std::fill(p.begin(), p.end(), 0);
        if (mode == 0 && seed == 6) edges = {{0, t, 7, 9}, {0, t, 7, 2}, {t, 0, 8, 1}};
        if (mode == 0 && seed == 7) edges = {{t, 0, 1, 1}};
        if (mode == 0 && seed == 8) edges = {{0, 0, 1, 1}, {0, t, 2, 3}, {t, t, 3, 1}};
        if (mode == 0 && seed == 9) {
            std::fill(p.begin(), p.end(), VALUE_MAX);
            edges = {{0, 1, 1, int(VALUE_MAX)}, {1, t, 2, int(VALUE_MAX)}};
        }
        if (mode == 3 && seed == 7) std::fill(p.begin(), p.end(), 0);
    }
    std::vector<int> label(n);
    std::iota(label.begin(), label.end(), 0);
    for (int i = n - 1; i > 0; --i) std::swap(label[i], label[rng.uniform(0, i)]);
    std::vector<long long> printed(n);
    for (int i = 0; i < n; ++i) printed[label[i]] = p[i];
    for (int i = int(edges.size()) - 1; i > 0; --i)
        std::swap(edges[i], edges[rng.uniform(0, i)]);
    std::cout << n << ' ' << edges.size() << ' ' << label[s] + 1 << ' ' << label[t] + 1 << '\n';
    for (int i = 0; i < n; ++i) std::cout << (i ? " " : "") << printed[i];
    std::cout << '\n';
    for (auto e : edges)
        std::cout << label[e.u] + 1 << ' ' << label[e.v] + 1 << ' ' << e.c << ' ' << e.w << '\n';
    return 0;
}
