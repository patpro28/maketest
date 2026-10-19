#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include "random.h"
#include "../params.h"

inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rnd(20261015ULL + mode * 100ULL + seed);
    std::vector<int> a;
    std::vector<std::pair<int, int>> queries;
    if (mode == 0) {
        const std::vector<std::vector<int>> arrays = {
            {1}, {1000000000}, {7, 7, 7, 7}, {1, 2, 2, 3, 5, 8, 13},
            {1000000000, 1, 999999999, 1, 1000000000}, {10, 8, 8, 5, 5, 2},
            {1, 1000000000, 500000000, 500000000}, {42}};
        a = arrays[seed];
        queries = {{1, 0}, {1, 1000000000}, {1000000000, 0}, {1000000000, 1000000000}};
        for (int value : a) {
            for (int delta = -1; delta <= 1; ++delta) {
                int x = std::max(1, std::min(1000000000, value + delta));
                for (int k : {0, 1, 2, 5, 1000000000}) queries.emplace_back(x, k);
            }
        }
    } else if (mode == 1) {
        for (int i = 0; i < 40; ++i) a.push_back(rnd.uniform(1, 25));
        if (seed == 0) std::fill(a.begin(), a.end(), 12);
        for (int x = 1; x <= 25; ++x)
            for (int k = 0; k <= 25; ++k) queries.emplace_back(x, k);
    } else {
        int n = mode == 3 ? static_cast<int>(N_MAX) : rnd.uniform(1000, 10000);
        int q = mode == 3 ? static_cast<int>(Q_MAX) : rnd.uniform(1000, 10000);
        if (mode == 4) {
            const std::vector<std::pair<int, int>> dimensions = {
                {1, 200000}, {200000, 1}, {5, 200000},
                {200000, 5}, {1000, 1000}, {999, 1001}};
            n = dimensions[seed].first;
            q = dimensions[seed].second;
        }
        for (int i = 0; i < n; ++i) {
            int value = rnd.uniform(1, static_cast<int>(VALUE_MAX));
            if (seed == 0) value = 500000000;
            if (seed == 1) value = rnd.uniform(1, 20);
            if (seed == 2) value = i % 2 ? 1 : VALUE_MAX;
            a.push_back(value);
        }
        if (seed == 3) std::sort(a.begin(), a.end());
        if (seed == 4) std::sort(a.rbegin(), a.rend());
        for (int i = 0; i < q; ++i) {
            int x = rnd.uniform(1, static_cast<int>(VALUE_MAX));
            int k = rnd.uniform(0, static_cast<int>(VALUE_MAX));
            switch (i % 6) {
                case 0: x = a[rnd.uniform(0, n - 1)]; k = 0; break;
                case 1: k = 1; break;
                case 2: x = 1; k = VALUE_MAX; break;
                case 3: x = VALUE_MAX; k = VALUE_MAX; break;
                case 4:
                    x = a[rnd.uniform(0, n - 1)];
                    k = seed % 2 ? x : VALUE_MAX - x;
                    break;
                default: break;
            }
            queries.emplace_back(x, k);
        }
    }
    std::printf("%d %d\n", static_cast<int>(a.size()), static_cast<int>(queries.size()));
    for (std::size_t i = 0; i < a.size(); ++i)
        std::printf("%d%c", a[i], i + 1 == a.size() ? '\n' : ' ');
    for (const auto &query : queries) std::printf("%d %d\n", query.first, query.second);
    return 0;
}
