#pragma once

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include "random.h"
#include "../params.h"

constexpr int KIND = 224;

inline void print_query(Random &rng, int left, int right, int number, bool extreme) {
    std::printf("1 %d %d", left, right);
    if constexpr (KIND == 227) {
        constexpr long long LIMIT = 1000000000000000LL;
        long long low = rng.uniform(-LIMIT, LIMIT);
        long long high = rng.uniform(-LIMIT, LIMIT);
        if (low > high) std::swap(low, high);
        if (number % 4 == 1) high = low;
        if (number % 4 == 2) { low = -LIMIT; high = LIMIT; }
        if (extreme) { low = 0; high = 0; }
        std::printf(" %lld %lld", low, high);
    }
    if constexpr (KIND == 229) {
        int u = rng.uniform(left, right - 1);
        int t = rng.uniform(u + 1, right);
        int v = rng.uniform(u, t - 1);
        int s = rng.uniform(v + 1, t);
        if (number % 4 == 0) {
            u = left;
            t = right;
            v = (left + right) / 2;
            s = v + 1;
        }
        const long long budgets[] = {0, 1, 9, 1000000000LL, 1000000000000000LL};
        long long budget = budgets[number % 5];
        if (number % 6 == 5) budget = rng.uniform(0LL, 2000000000LL);
        std::printf(" %d %d %d %d %lld", u, v, s, t, budget);
    }
    std::putchar('\n');
}

inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rng(20261112000ULL + KIND * 1000ULL + mode * 100ULL + seed);
    const int edge_sizes[] = {1, 2, 3, 5, 8, 9, 17, 31, 32, 33, 65, 7};
    int n = N_MAX - (seed == 5);
    int q = Q_MAX;
    if (mode == 0) {
        n = edge_sizes[seed];
        q = 68;
    } else if (mode == 1) {
        n = rng.uniform(1, 24);
        q = 115;
    } else if (mode == 2) {
        n = rng.uniform(2000, 16000);
        q = rng.uniform(3000, 18000);
    }

    bool uniform_add = mode == 3 && seed == 1;
    bool half_add = mode == 3 && seed == 2;
    std::printf("%d %d", n, q);
    if constexpr (KIND == 227) {
        const int slopes[] = {0, VALUE_MIN, VALUE_MAX, -7, 5, 0};
        int slope = uniform_add ? 0 : slopes[seed % 6];
        std::printf(" %d", slope);
    }
    std::putchar('\n');

    for (int i = 1; i <= n; ++i) {
        int value = rng.uniform(int(VALUE_MIN), int(VALUE_MAX));
        if (seed % 6 == 1) value = VALUE_MAX;
        if (seed % 6 == 2) value = 0;
        if (seed % 6 == 3) value = rng.uniform(-3, 3);
        if (seed % 6 == 4) value = i % 2 ? VALUE_MIN : VALUE_MAX;
        std::printf("%d%c", value, i == n ? '\n' : ' ');
    }
    for (int number = 0; number < q; ++number) {
        const int rates[] = {40, 60, 85};
        bool update = rng.uniform(0, 99) < rates[seed % 3];
        if (mode == 0 && seed == 9) update = false;
        if (mode == 0 && seed == 10) update = true;
        if (KIND == 229 && n == 1) update = true;

        if (uniform_add || half_add) {
            if (number + 1 == q) {
                print_query(rng, 1, n, number, true);
            } else {
                int right = uniform_add ? n : n / 2;
                int value = uniform_add ? VALUE_MAX : VALUE_MIN;
                std::printf("0 1 %d %d\n", right, value);
            }
            continue;
        }

        int left = rng.uniform(1, n);
        int right = rng.uniform(1, n);
        if (left > right) std::swap(left, right);
        if (number % 10 == 0) { left = 1; right = n; }
        if (number % 10 == 1) right = left;
        if (number % 10 == 2) left = 1;
        if (number % 10 == 3) right = n;
        if (KIND == 225 && number % 10 >= 6) std::swap(left, right);

        if (update) {
            int delta = rng.uniform(int(VALUE_MIN), int(VALUE_MAX));
            if (number % 8 == 0) delta = VALUE_MAX;
            if (number % 8 == 1) delta = VALUE_MIN;
            if (number % 8 == 2) delta = 0;
            std::printf("0 %d %d %d\n", left, right, delta);
        } else {
            if (KIND == 229 && left == right) {
                if (left > 1) --left;
                else ++right;
            }
            print_query(rng, left, right, number, false);
        }
    }
    return 0;
}
