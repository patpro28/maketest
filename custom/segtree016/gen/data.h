#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include "random.h"
#include "../params.h"

constexpr int KIND = 16;

inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rng(20261111000ULL + KIND * 1000ULL + mode * 100ULL + seed);
    const int edge_sizes[] = {1, 2, 3, 5, 8, 9, 17, 31, 32, 33, 65, 7};
    int n = N_MAX - (seed == 5);
    int q = Q_MAX;
    if (mode == 0) {
        n = edge_sizes[seed];
        q = 72;
    } else if (mode == 1) {
        n = rng.uniform(1, 30);
        q = 160;
    } else if (mode == 2) {
        n = rng.uniform(2000, 20000);
        q = rng.uniform(2000, 20000);
    }

    bool extreme = mode == 3 && seed == 1;
    std::printf("%d %d", n, q);
    if (KIND == 18) {
        int step = rng.uniform(1, n);
        if (seed % 6 == 1) step = 1;
        if (seed % 6 == 3) step = n;
        if (seed % 6 == 5) step = std::min(n, 7);
        std::printf(" %d", step);
    }
    std::putchar('\n');

    for (int i = 1; i <= n; ++i) {
        int value = rng.uniform(int(VALUE_MIN), int(VALUE_MAX));
        if (seed % 6 == 1) value = VALUE_MAX;
        if (seed % 6 == 2) value = 0;
        if (seed % 6 == 4) value = i % 2 == 0 ? VALUE_MAX : VALUE_MIN;
        std::printf("%d%c", value, i == n ? '\n' : ' ');
    }
    if (KIND == 19) {
        for (int i = 1; i <= n; ++i) {
            int weight = rng.uniform(-10000, 10000);
            if (seed % 6 == 1) weight = 10000;
            if (seed % 6 == 2) weight = 0;
            if (seed % 6 == 4) weight = i % 2 == 0 ? 10000 : -10000;
            std::printf("%d%c", weight, i == n ? '\n' : ' ');
        }
    }

    for (int i = 0; i < q; ++i) {
        if (extreme) {
            if (i + 1 < q) {
                if (KIND == 16) std::printf("1 1 %d %d\n", n, int(VALUE_MAX));
                if (KIND == 17) std::printf("1 %d %d\n", n, int(VALUE_MAX));
                if (KIND == 18 || KIND == 19) std::printf("1 %d %d\n", n, int(VALUE_MIN));
            } else {
                if (KIND == 16) std::printf("2 %d %d\n", n, n);
                if (KIND == 17) std::printf("2 %d 1\n", n);
                if (KIND == 18 || KIND == 19) std::printf("2 1 %d\n", n);
            }
            continue;
        }

        const int update_rates[] = {20, 50, 85};
        bool update = rng.uniform(0, 99) < update_rates[seed % 3];
        if (mode == 0 && seed == 9) update = false;
        if (mode == 0 && seed == 10) update = true;
        int left = rng.uniform(1, n);
        int right = rng.uniform(1, n);
        if (update) {
            if (i % 8 == 1) left = 1;
            if (i % 8 == 2) left = n;
            if (i % 8 == 3) right = left;
            int value = rng.uniform(KIND == 16 ? 0 : int(VALUE_MIN), int(VALUE_MAX));
            if (i % 8 == 4) value = 0;
            if (i % 8 == 5) value = VALUE_MAX;
            if (i % 8 == 6 && KIND != 16) value = VALUE_MIN;
            if (KIND == 16) std::printf("1 %d %d %d\n", left, right, value);
            else std::printf("1 %d %d\n", left, value);
        } else {
            if (left > right) std::swap(left, right);
            if (i % 8 == 0) { left = 1; right = n; }
            if (i % 8 == 1) right = left;
            if (i % 8 == 2) left = 1;
            if (i % 8 == 3) right = n;
            if (KIND == 17 && i % 8 >= 4) std::swap(left, right);
            std::printf("2 %d %d\n", left, right);
        }
    }
    return 0;
}
