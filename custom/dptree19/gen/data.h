#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>
#include "random.h"
#include "../params.h"

struct Edge { int u, v; long long w; };

inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rng(20261018ULL + PROBLEM_KIND * 10000ULL + mode * 100ULL + seed);
    const long long LIM = VALUE_MAX;
    int n;
    if (mode == 0) {
        const int sizes[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15};
        n = sizes[seed];
        if (PROBLEM_KIND == 19) n = std::max(2, n);
    } else if (mode == 1) n = rng.uniform(PROBLEM_KIND == 19 ? 2 : 1, 16);
    else if (mode == 2) n = rng.uniform(200, 6000);
    else n = int(N_MAX);

    int shape = seed % 8;
    if (mode == 0) {
        const int shapes[] = {0, 0, 0, 1, 0, 1, 2, 3, 0, 6, 1, 0};
        shape = shapes[seed];
    }
    std::vector<Edge> edges;
    for (int v = 1; v < n; ++v) {
        int p = 0;
        if (shape == 0) p = v - 1;                         // path
        else if (shape == 1) p = 0;                        // star
        else if (shape == 2) p = (v - 1) / 2;              // binary tree
        else if (shape == 3) p = v < n / 2 ? v - 1 : n / 2 - 1; // broom
        else if (shape == 4) p = v < n / 2 ? v - 1 : (v - n / 2) % (n / 2);
        else if (shape == 5) p = v <= 4 ? 0 : v - 4;       // four long branches
        else if (shape == 6) p = rng.uniform(0, v - 1);
        else p = rng.uniform(std::max(0, v - 30), v - 1);
        edges.push_back({p, v, rng.uniform(1LL, LIM)});
    }
    std::vector<long long> value(n);
    for (int i = 0; i < n; ++i) {
        if (PROBLEM_KIND == 18) value[i] = rng.uniform(-LIM, LIM);
        else value[i] = rng.uniform(1LL, LIM);
    }

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            if (PROBLEM_KIND == 18) {
                const long long pattern[] = {8, -3, 9, 0, -LIM, LIM};
                value[i] = pattern[i % 6];
            } else value[i] = i % 3 == 0 ? LIM : 1;
        }
        if (PROBLEM_KIND == 18) {
            if (seed == 0 || seed == 5) std::fill(value.begin(), value.end(), -LIM);
            if (seed == 1) value = {-5, 7};
            if (seed == 3) { std::fill(value.begin(), value.end(), 5); value[0] = -1; }
            if (seed == 6) std::fill(value.begin(), value.end(), 0);
            if (seed == 10) std::fill(value.begin(), value.end(), LIM);
            if (seed == 11) {
                std::fill(value.begin(), value.end(), -LIM);
                value[n - 1] = LIM;
            }
        }
        if (PROBLEM_KIND == 22) {
            if (seed == 0) value[0] = LIM;
            if (seed == 2) value = {1, LIM, 1};
            if (seed == 3 || seed == 10) {
                std::fill(value.begin(), value.end(), 1);
                value[0] = LIM;
            }
            if (seed == 6 || seed == 11) std::fill(value.begin(), value.end(), LIM);
        }
        for (int i = 0; i < n - 1; ++i) {
            edges[i].w = i % 2 ? 1 : LIM;
            if (seed == 0 || seed == 1 || seed == 3 || seed == 6 || seed == 10)
                edges[i].w = LIM;
        }
    } else if (mode == 3) {
        if (seed <= 3) {
            std::fill(value.begin(), value.end(), LIM);
            for (auto &e : edges) e.w = LIM;
        }
        if (PROBLEM_KIND == 18 && seed == 1) std::fill(value.begin(), value.end(), -LIM);
        if (PROBLEM_KIND == 18 && seed == 2) std::fill(value.begin(), value.end(), 0);
        if (seed == 4)
            for (int i = 0; i < n; ++i) value[i] = PROBLEM_KIND == 18 && i % 2 ? -LIM : 1;
    } else if (seed % 3 == 0) {
        for (int i = 0; i < n; ++i) {
            value[i] = rng.uniform(1LL, 20LL);
            if (PROBLEM_KIND == 18) value[i] -= 10;
        }
        for (auto &e : edges) e.w = rng.uniform(1LL, 20LL);
    }

    std::vector<int> label(n);
    std::iota(label.begin(), label.end(), 0);
    if (mode == 0 && seed == 4) std::swap(label[0], label[n / 2]);
    if (mode == 0 && seed == 5) std::swap(label[0], label[n - 1]);
    if (mode != 0) {
        // Keep the root for the first six shapes; move it for general trees.
        int first = seed >= 6 ? 0 : 1;
        for (int i = n - 1; i > first; --i)
            std::swap(label[i], label[rng.uniform(first, i)]);
    }
    std::vector<long long> printed(n);
    for (int i = 0; i < n; ++i) printed[label[i]] = value[i];
    for (int i = int(edges.size()) - 1; i > 0; --i)
        std::swap(edges[i], edges[rng.uniform(0, i)]);
    std::cout << n << '\n';
    if (PROBLEM_KIND == 18 || PROBLEM_KIND == 22) {
        for (int i = 0; i < n; ++i) std::cout << (i ? " " : "") << printed[i];
        std::cout << '\n';
    }
    for (auto e : edges) {
        if (rng.uniform_bool()) std::swap(e.u, e.v);
        std::cout << label[e.u] + 1 << ' ' << label[e.v] + 1;
        if (PROBLEM_KIND == 19) std::cout << ' ' << e.w;
        std::cout << '\n';
    }
    return 0;
}
