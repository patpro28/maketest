#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <set>
#include <utility>
#include <vector>
#include "random.h"
#include "../params.h"
struct Op { char type; int u = 0, v = 0; };
inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rng(2026102701ULL + mode * 1000 + seed);
    int n = mode == 0 ? (seed == 0 || seed == 10 ? 1 : seed == 1 || seed == 8 ? 2 : seed >= 9 ? 2000 : 4 + seed)
          : mode == 1 ? (seed == 0 ? 1 : 2000) : int(N_MAX);
    int q = mode == 0 ? (seed == 0 ? 1 : seed >= 8 ? 2000 : 40 + seed * 7)
          : mode == 1 ? 2000 : int(Q_MAX);
    std::vector<int> color(n);
    for (int i = 0; i < n; ++i) color[i] = i % 2;
    if (seed == 4 || seed == 12) std::fill(color.begin(), color.end(), seed % 2);
    if (seed % 3 == 2) for (auto &x : color) x = rng.uniform(0, 1);
    std::vector<Op> ops;
    auto put = [&](char type, int u = 0, int v = 0) {
        if (int(ops.size()) < q) ops.push_back({type, u, v});
    };
    if (n == 1) while (int(ops.size()) < q) put('?');
    else if (mode >= 2 && seed == 0) {
        for (int v = 1; v < n && int(ops.size()) < q - 1; ++v) put('+', v - 1, v);
        put('?');
    } else if (mode == 3 && seed == 4) {
        const int half = 50000;
        std::fill(color.begin(), color.end(), 0);
        for (int i = half; i < 2 * half; ++i) color[i] = 1;
        for (int i = 1; i < half; ++i) { put('+', i - 1, i); put('+', half + i - 1, half + i); }
        put('?');
        bool bridge = false;
        while (int(ops.size()) < q - 1) {
            put(bridge ? '-' : '+', 0, half);
            bridge = !bridge;
            put('?');
        }
        if (int(ops.size()) < q) put('?');
    } else if (mode == 2) {
        int next = 1;
        while (int(ops.size()) < q - 1) {
            if (next < n && (int(ops.size()) % 3 != 2)) {
                int parent = seed % 3 == 0 ? next - 1 : seed % 3 == 1 ? 0 : rng.uniform(0, next - 1);
                put('+', parent, next++);
            } else put('?');
        }
        put('?');
    } else {
        std::vector<std::pair<int, int>> pool;
        std::set<std::pair<int, int>> used;
        auto add_edge = [&](int u, int v) {
            if (u == v) return;
            if (u > v) std::swap(u, v);
            if (used.insert({u, v}).second) pool.push_back({u, v});
        };
        int vertices = seed % 4 == 3 ? std::min(n, 3000) : n;
        int target = int(std::min<long long>(q / 2 + 1, 1LL * vertices * (vertices - 1) / 2));
        int tree_edges = std::min(vertices - 1, std::max(1, target / 2));
        for (int v = 1; v <= tree_edges; ++v) {
            int parent = seed % 3 == 0 ? v - 1 : seed % 3 == 1 ? 0 : rng.uniform(0, v - 1);
            add_edge(parent, v);
        }
        while (int(pool.size()) < target) add_edge(rng.uniform(0, vertices - 1), rng.uniform(0, vertices - 1));
        std::vector<bool> active(pool.size(), false);
        int initial = mode == 3 ? std::min(int(pool.size()), q / 4) : 0;
        for (int i = 0; i < initial; ++i) {
            put('+', pool[i].first, pool[i].second); active[i] = true;
        }
        while (int(ops.size()) < q - 1) {
            if (rng.uniform(0, 9) < 4) put('?');
            else {
                int id = rng.uniform(0, int(pool.size()) - 1);
                auto [u, v] = pool[id];
                if (rng.uniform_bool()) std::swap(u, v);
                put(active[id] ? '-' : '+', u, v);
                active[id] = !active[id];
            }
        }
        put('?');
    }
    while (int(ops.size()) < q) put('?');
    std::vector<int> label(n);
    std::iota(label.begin(), label.end(), 0);
    if (seed % 2) for (int i = n - 1; i > 0; --i) std::swap(label[i], label[rng.uniform(0, i)]);
    std::vector<int> printed(n);
    for (int i = 0; i < n; ++i) printed[label[i]] = color[i];
    std::cout << n << ' ' << q << '\n';
    for (int i = 0; i < n; ++i) std::cout << (i ? " " : "") << printed[i];
    std::cout << '\n';
    for (auto op : ops) {
        std::cout << op.type;
        if (op.type != '?') std::cout << ' ' << label[op.u] + 1 << ' ' << label[op.v] + 1;
        std::cout << '\n';
    }
    return 0;
}
