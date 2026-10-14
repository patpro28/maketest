#pragma once
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <numeric>
#include <set>
#include <utility>
#include <vector>
#include "random.h"

// Build separate connected components, then add internal edges only.
inline void generate_graph(Random& gen, const std::vector<int>& sizes,
                           int m, bool permute, bool path) {
    int n = std::accumulate(sizes.begin(), sizes.end(), 0);
    std::vector<int> labels(n);
    std::iota(labels.begin(), labels.end(), 1);
    if (permute) gen.shuffle(labels.begin(), labels.end());
    std::set<std::pair<int, int>> edges;
    std::vector<std::pair<int, int>> intervals;
    int start = 0;
    long long capacity = 0;
    for (int size : sizes) {
        capacity += 1LL * size * (size - 1) / 2;
        if (size > 1) intervals.emplace_back(start, start + size - 1);
        for (int i = 1; i < size; ++i) {
            int p = path ? i - 1 : gen.uniform(0, i - 1);
            edges.emplace(start + p, start + i);
        }
        start += size;
    }
    assert(m >= static_cast<int>(edges.size()) && m <= capacity);
    while (static_cast<int>(edges.size()) < m) {
        auto [lo, hi] = intervals[gen.uniform(0, static_cast<int>(intervals.size()) - 1)];
        int u = gen.uniform(lo, hi);
        int v = gen.uniform(lo, hi);
        if (u == v) continue;
        if (u > v) std::swap(u, v);
        edges.emplace(u, v);
    }
    std::vector<std::pair<int, int>> output(edges.begin(), edges.end());
    // Preserve the long chain's order to stress unbalanced DSU implementations.
    if (!path) gen.shuffle(output.begin(), output.end());
    std::printf("%d %d\n", n, m);
    for (auto [u, v] : output) {
        u = labels[u];
        v = labels[v];
        if (gen.uniform_bool()) std::swap(u, v);
        std::printf("%d %d\n", u, v);
    }
}
