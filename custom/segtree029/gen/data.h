#pragma once

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include "random.h"
#include "../params.h"

constexpr int KIND = 29;

inline void print_query(Random &rng, int n, int left, int right, int number) {
    if constexpr (KIND == 24) {
        const int references[] = {VALUE_MIN, VALUE_MAX, 0};
        int h = number % 4 == 3 ? rng.uniform(int(VALUE_MIN), int(VALUE_MAX))
                                : references[number % 4];
        std::printf("2 %d %d %d\n", left, right, h);
    } else if constexpr (KIND == 26) {
        if (left == right) {
            if (left > 1) --left;
            else ++right;
        }
        int u = rng.uniform(left, right);
        int v = rng.uniform(u, right);
        if (number % 4 == 0) { u = left; v = right - 1; }
        if (number % 4 == 1) { u = left + 1; v = right; }
        if (number % 4 == 2 && right - left >= 2) { u = left + 1; v = right - 1; }
        if (u == left && v == right) --v;
        std::printf("2 %d %d %d %d\n", left, right, u, v);
    } else if constexpr (KIND == 27) {
        right = std::min(right, n - 1);
        left = std::min(left, right);
        int u = number % 3 == 0 ? right + 1 : rng.uniform(right + 1, n);
        int v = number % 3 == 1 ? n : rng.uniform(u, n);
        if (number % 8 == 0) { right = n / 2; u = right + 1; v = n; }
        left = std::min(left, right);
        std::printf("2 %d %d %d %d\n", left, right, u, v);
    } else {
        std::printf("2 %d %d\n", left, right);
    }
}

inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rng(20261112000ULL + KIND * 1000ULL + mode * 100ULL + seed);
    const int edge_sizes[] = {1, 2, 3, 5, 8, 9, 17, 31, 32, 33, 65, 7};
    int n = N_MAX - (seed == 5);
    int q = Q_MAX;
    if (mode == 0) {
        n = edge_sizes[seed];
        q = 84;
    } else if (mode == 1) {
        n = rng.uniform(1, 25);
        q = 120;
    } else if (mode == 2) {
        n = rng.uniform(2000, 17000);
        q = rng.uniform(3000, 20000);
    }

    std::printf("%d %d\n", n, q);
    for (int i = 1; i <= n; ++i) {
        int value = rng.uniform(int(VALUE_MIN), int(VALUE_MAX));
        if (seed % 6 == 1) value = VALUE_MAX;
        if (seed % 6 == 2) value = VALUE_MIN;
        if (seed % 6 == 3) value = rng.uniform(KIND == 29 ? 0 : -3, 3);
        if (seed % 6 == 4) value = i % 2 == 0 ? VALUE_MAX : VALUE_MIN;
        std::printf("%d%c", value, i == n ? '\n' : ' ');
    }

    for (int number = 0; number < q; ++number) {
        const int rates[] = {35, 55, 85};
        bool update = rng.uniform(0, 99) < rates[seed % 3];
        if (mode == 0 && seed == 9) update = false;
        if (mode == 0 && seed == 10) update = true;
        if ((KIND == 26 || KIND == 27) && n == 1) update = true;
        int left = rng.uniform(1, n);
        if (update) {
            if (number % 8 == 0) left = 1;
            if (number % 8 == 1) left = n;
            int value = rng.uniform(int(VALUE_MIN), int(VALUE_MAX));
            if (number % 8 == 2) value = VALUE_MAX;
            if (number % 8 == 3) value = VALUE_MIN;
            if (number % 8 == 4) value = 0;
            if (mode == 3 && seed == 1) value = VALUE_MAX;
            std::printf("1 %d %d\n", left, value);
        } else {
            int right = rng.uniform(1, n);
            if (left > right) std::swap(left, right);
            if (number % 8 == 0) { left = 1; right = n; }
            if (number % 8 == 1) right = left;
            if (number % 8 == 2) left = 1;
            if (number % 8 == 3) right = n;
            print_query(rng, n, left, right, number);
        }
    }
    return 0;
}
