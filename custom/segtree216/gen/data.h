#pragma once
#include "random.h"
#include "../params.h"
#include <algorithm>
#include <cstdio>
#include <cstdlib>

constexpr int KIND = 216;
constexpr int AXIS_END = 1000000000;

inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rng(20261110000ULL + KIND * 1000ULL + mode * 100ULL + seed);
    const int sizes[] = {1, 2, 3, 5, 8, 9, 17, 31, 32, 33, 65, 7};
    int n = N_MAX - (seed == 5);
    int q = Q_MAX;
    if (mode == 0) { n = sizes[seed]; q = 72; }
    if (mode == 1) { n = rng.uniform(1, 30); q = 160; }
    if (mode == 2) { n = rng.uniform(3000, 18000); q = rng.uniform(3000, 18000); }

    int setting = 0;
    if (KIND == 215) {
        const int moduli[] = {1, 2, 7, 1000000000, 999999937, 1024};
        setting = moduli[seed % 6];
    }
    if (KIND == 217) {
        setting = rng.uniform(1, n);
        if (seed % 6 == 1) setting = 1;
        if (seed % 6 == 3) setting = n;
        if (seed % 6 == 4) setting = std::min(n, 7);
    }

    if (KIND == 218) {
        std::printf("%d\n", q);
    } else {
        std::printf("%d %d", n, q);
        if (KIND == 215 || KIND == 217) std::printf(" %d", setting);
        std::putchar('\n');
        for (int i = 1; i <= n; ++i) {
            int value = rng.uniform(int(VALUE_MIN), int(VALUE_MAX));
            if (seed % 6 == 1) value = VALUE_MAX;
            if (seed % 6 == 2) value = 0;
            if (seed % 6 == 4) value = i % 2 ? VALUE_MIN : VALUE_MAX;
            std::printf("%d%c", value, i == n ? '\n' : ' ');
        }
        if (KIND == 219) {
            for (int i = 1; i <= n; ++i) {
                int weight = rng.uniform(0, 10000);
                if (seed % 6 == 1) weight = 10000;
                if (seed % 6 == 2) weight = i % 2 ? 0 : 10000;
                if (seed % 6 == 3) weight = 0;
                std::printf("%d%c", weight, i == n ? '\n' : ' ');
            }
        }
    }

    int end = KIND == 218 ? AXIS_END : n;
    for (int i = 0; i < q; ++i) {
        bool update = i % 3 != 0;
        if (mode == 2) update = rng.uniform(0, 99) < (seed % 3 == 0 ? 20 : seed % 3 == 1 ? 50 : 85);
        if (mode == 0 && seed == 9) update = false;
        if (mode == 0 && seed == 10) update = true;
        if (mode == 3 && seed == 1) update = i + 1 != q;
        if (mode == 3 && seed == 3) update = false;

        int left = rng.uniform(1, end);
        int right = rng.uniform(1, end);
        if (left > right) std::swap(left, right);
        if (i % 8 == 0) { left = 1; right = end; }
        if (i % 8 == 1) right = left;
        if (i % 8 == 2) left = 1;
        if (i % 8 == 3) right = end;
        if (i % 8 == 4) { left = end; right = end; }
        if (i % 8 == 5) { left = 1; right = 1; }
        if (KIND == 211 && i % 4 == 3) std::swap(left, right);
        if (mode == 3 && seed == 1) { left = 1; right = end; }
        if (mode == 3 && seed == 2 && update) { left = 1; right = end; }
        if (KIND == 218 && mode == 3 && seed == 5) {
            left = 3 * i + 1;
            right = left + 1;
        }

        if (update) {
            int delta = rng.uniform(int(VALUE_MIN), int(VALUE_MAX));
            if (i % 5 == 0) delta = VALUE_MIN;
            if (i % 5 == 1) delta = VALUE_MAX;
            if (i % 5 == 2) delta = 0;
            if (mode == 3 && seed == 1) delta = VALUE_MAX;
            std::printf("1 %d %d %d\n", left, right, delta);
        } else {
            std::printf("2 %d %d\n", left, right);
        }
    }
    return 0;
}
