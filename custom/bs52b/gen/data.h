#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "random.h"
#include "../params.h"

using i64 = long long;
inline i64 choose3(i64 n) { return n < 3 ? 0 : n * (n - 1) * (n - 2) / 6; }
struct Case { std::vector<int> a; std::vector<i64> queries; };

inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rnd(20261016ULL + 1000ULL * mode + seed);
    std::vector<Case> tests;
    auto create = [&](int n, int q, int pattern) {
        Case test;
        for (int i = 0; i < n; ++i) {
            int v = rnd.uniform(-static_cast<int>(A_MAX), static_cast<int>(A_MAX));
            if (pattern == 0) v = -7;
            if (pattern == 1) v = i % 2 ? A_MAX : -A_MAX;
            if (pattern == 2) v = i - n / 2;
            if (pattern == 3) v = n / 2 - i;
            if (pattern == 4) v = rnd.uniform(-5, 5);
            test.a.push_back(v);
        }
        i64 total = choose3(n);
        for (int i = 0; i < q; ++i) {
            i64 k = rnd.uniform(1LL, total);
            if (i % 6 == 0) k = 1;
            if (i % 6 == 1) k = total;
            if (i % 6 == 2 || i % 6 == 3 || i % 6 == 4) {
                int position = rnd.uniform(3, n);
                int delta = i % 6 - 3;
                k = std::max(1LL, std::min(total, choose3(position) + delta));
            }
            test.queries.push_back(k);
        }
        return test;
    };
    if (mode == 0) {
        const std::vector<int> sizes = {3,4,5,6,30,1292,2346,3000};
        int n = sizes[seed];
        Case test = create(n, n <= 30 ? static_cast<int>(choose3(n)) : 3000, seed % 6);
        if (n <= 30) {
            for (std::size_t i = 0; i < test.queries.size(); ++i) test.queries[i] = i + 1;
            rnd.shuffle(test.queries.begin(), test.queries.end());
        }
        if (seed == 0) test.a = {-1000000000, 0, 1000000000};
        if (seed == 1) test.a = {-5, -5, -5, -5};
        if (seed == 2) test.a = {7, -9, -9, 7, 0};
        tests.push_back(test);
    } else if (mode == 1) {
        for (int t = 0; t < 30; ++t) {
            int n = rnd.uniform(3, 12);
            Case test = create(n, static_cast<int>(choose3(n)), (seed + t) % 6);
            for (std::size_t i = 0; i < test.queries.size(); ++i) test.queries[i] = i + 1;
            rnd.shuffle(test.queries.begin(), test.queries.end());
            tests.push_back(test);
        }
    } else if (mode == 2) {
        for (int t = 0; t < 10; ++t)
            tests.push_back(create(rnd.uniform(1000, 10000), rnd.uniform(100, 2000), seed));
    } else if (mode == 3) {
        tests.push_back(create(N_MAX, Q_MAX, seed));
    } else {
        for (int t = 0; t < T_MAX; ++t)
            tests.push_back(create(seed == 0 ? 300 : 3, 300, t % 6));
    }
    std::printf("%d\n", static_cast<int>(tests.size()));
    for (const Case &test : tests) {
        std::printf("%d %d\n", static_cast<int>(test.a.size()), static_cast<int>(test.queries.size()));
        for (std::size_t i = 0; i < test.a.size(); ++i)
            std::printf("%d%c", test.a[i], i + 1 == test.a.size() ? '\n' : ' ');
        for (i64 k : test.queries) std::printf("%lld\n", k);
    }
    return 0;
}
