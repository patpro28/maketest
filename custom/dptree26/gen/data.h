#pragma once
#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>
#include "random.h"
#include "../params.h"

struct Edge { int u, v; long long w; };

inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rng(20261022ULL + PROBLEM_KIND * 10000ULL + mode * 100ULL + seed);
    const long long LIM = VALUE_MAX;
    int n;
    if (mode == 0) {
        const int sizes[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15};
        n = sizes[seed];
    } else if (mode == 1) n = rng.uniform(1, 16);
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
        if (shape == 0) p = v - 1; // path
        else if (shape == 1) p = 0; // star
        else if (shape == 2) p = (v - 1) / 2;
        else if (shape == 3) p = v < n / 2 ? v - 1 : n / 2 - 1;
        else if (shape == 4) p = v < n / 2 ? v - 1 : (v - n / 2) % (n / 2);
        else if (shape == 5) p = v <= 4 ? 0 : v - 4;
        else if (shape == 6) p = rng.uniform(0, v - 1);
        else p = rng.uniform(std::max(0, v - 30), v - 1);
        edges.push_back({p, v, rng.uniform(0LL, LIM)});
    }
    std::vector<std::array<long long, 2>> value(n);
    for (auto &x : value) {
        x[0] = rng.uniform(PROBLEM_KIND == 23 ? 1LL : 0LL, LIM);
        x[1] = rng.uniform(0LL, LIM);
    }
    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            value[i] = {i % 2 ? 1 : LIM, i % 2 ? LIM : 0};
        }
        if (PROBLEM_KIND == 23) {
            if (seed == 2) { value[0][0] = 1; value[1][0] = LIM; value[2][0] = 1; }
            if (seed == 3 || seed == 10) {
                for (auto &x : value) x[0] = 1;
                value[0][0] = LIM;
            }
            if (seed == 6 || seed == 11) for (auto &x : value) x[0] = LIM;
        }
        if (PROBLEM_KIND == 24) {
            if (seed == 0) value[0] = {LIM, 0};
            if (seed == 1) { value[0] = {0, 4}; value[1] = {5, 0}; }
            if (seed == 2) value = {{0, LIM}, {LIM, 0}, {0, LIM}};
            if (seed == 3) for (auto &x : value) x = {0, 0};
            if (seed == 6 || seed == 11) for (auto &x : value) x = {LIM, LIM};
        }
        for (auto &e : edges) e.w = seed % 3 == 0 ? 0 : seed % 3 == 1 ? LIM : 1;
    } else if (mode == 1 || mode == 2) {
        if (seed % 3 == 0) {
            for (auto &x : value) {
                x[0] = rng.uniform(PROBLEM_KIND == 23 ? 1LL : 0LL, 20LL);
                x[1] = rng.uniform(0LL, 20LL);
            }
            for (auto &e : edges) e.w = rng.uniform(0LL, 20LL);
        }
    } else {
        if (PROBLEM_KIND == 23) {
            if (seed == 0 || seed == 3) for (auto &x : value) x[0] = LIM;
            if (seed == 1 || seed == 2) for (auto &x : value) x[0] = 1;
            if (seed == 1) value[0][0] = LIM;
            if (seed == 4) for (int i = 0; i < n; ++i) value[i][0] = i % 2 ? 1 : LIM;
        }
        if (PROBLEM_KIND == 24) {
            if (seed == 0 || seed == 3) for (auto &x : value) x = {LIM, LIM};
            if (seed == 1) for (auto &e : edges) e.w = 0;
            if (seed == 2) for (auto &x : value) x = {0, 0};
            if (seed == 4) {
                for (int i = 0; i < n; ++i) value[i] = i % 2
                    ? std::array<long long, 2>{LIM, 0}
                    : std::array<long long, 2>{0, LIM};
                for (auto &e : edges) e.w = 1;
            }
        }
    }
    std::vector<int> label(n);
    std::iota(label.begin(), label.end(), 0);
    if (mode == 0 && seed == 4) std::swap(label[0], label[n / 2]);
    if (mode == 0 && seed == 5) std::swap(label[0], label[n - 1]);
    if (mode != 0) {
        int first = seed >= 6 ? 0 : 1;
        for (int i = n - 1; i > first; --i)
            std::swap(label[i], label[rng.uniform(first, i)]);
    }
    std::vector<std::array<long long, 2>> printed(n);
    for (int i = 0; i < n; ++i) printed[label[i]] = value[i];
    for (int i = int(edges.size()) - 1; i > 0; --i)
        std::swap(edges[i], edges[rng.uniform(0, i)]);
    std::cout << n << '\n';
    if (PROBLEM_KIND == 23) {
        for (int i = 0; i < n; ++i) std::cout << (i ? " " : "") << printed[i][0];
        std::cout << '\n';
    }
    if (PROBLEM_KIND == 24)
        for (auto x : printed) std::cout << x[0] << ' ' << x[1] << '\n';
    for (auto e : edges) {
        if (rng.uniform_bool()) std::swap(e.u, e.v);
        std::cout << label[e.u] + 1 << ' ' << label[e.v] + 1;
        if (PROBLEM_KIND == 24) std::cout << ' ' << e.w;
        std::cout << '\n';
    }
    return 0;
}
