#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <tuple>
#include <vector>
#include "random.h"
#include "../params.h"

using i64 = long long;
using Query = std::tuple<i64, i64, i64>;

inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rnd(20261015ULL + mode * 100ULL + seed);
    std::vector<Query> cases;
    auto add = [&](i64 l, i64 r, i64 a) { cases.emplace_back(l, r, a); };
    if (mode == 0) {
        if (seed == 0) {
            add(1, 1, 1);  // Also test the smallest possible T.
        } else {
            const std::vector<i64> divisors = {1, 2, 3, 7, 10, 999983, A_MAX};
            const std::vector<i64> points = {
                1, 2, 3, 999999999, 1000000000, 2147483647LL,
                2147483648LL, 9007199254740991LL, 9007199254740992LL,
                9007199254740993LL, LR_MAX - 1, LR_MAX};
            for (i64 a : divisors) {
                add(1, LR_MAX, a);
                add(1, a, a);
                add(1, 2 * a, a);
                for (i64 x : points) {
                    add(x, x, a);
                    add(std::max(1LL, x - 2 * a), std::min(LR_MAX, x + 2 * a), a);
                    i64 multiple = x / a * a;
                    for (i64 delta = -1; delta <= 1; ++delta) {
                        i64 l = std::max(1LL, std::min(LR_MAX, multiple + delta));
                        add(l, std::min(LR_MAX, l + a + seed), a);
                    }
                }
            }
        }
    } else if (mode == 4) {
        const std::vector<Query> queries = {
            {1, 1, 1}, {1, 1000000, 1}, {1, 1000000, 1000000},
            {999983, 1000000, 999983}, {17, 999999, 37}};
        cases.push_back(queries[seed]);
    } else if (mode == 5) {
        for (int i = 0; i < T_MAX; ++i) {
            i64 l = rnd.uniform(1LL, LR_MAX);
            i64 r = rnd.uniform(l, LR_MAX);
            if (seed == 0) {
                l = i + 1;
                r = LR_MAX - i;
            } else if (seed == 1) {
                l = LR_MAX - i;
                r = std::min(LR_MAX, l + i % 3);
            } else if (i % 3 == 0) {
                l = 9007199254740991LL + i;
                r = l + i % 5;
            }
            add(l, r, 1);
        }
    } else if (mode == 1) {
        // Exhaust all intervals within [1,120] for A in [1,20], split in four files.
        for (i64 a = 1; a <= 20; ++a)
            for (i64 l = seed * 30 + 1; l <= (seed + 1) * 30; ++l)
                for (i64 r = l; r <= 120; ++r) add(l, r, a);
    } else {
        for (int i = 0; i < T_MAX; ++i) {
            i64 a = rnd.uniform(1LL, A_MAX);
            i64 l = 1, r = LR_MAX;
            if (mode == 2) {
                switch ((i + seed) % 5) {
                    case 0:
                        l = rnd.uniform(1LL, LR_MAX);
                        r = rnd.uniform(1LL, LR_MAX);
                        if (l > r) std::swap(l, r);
                        break;
                    case 1:
                        l = rnd.uniform(1LL, LR_MAX);
                        r = std::min(LR_MAX, l + rnd.uniform(0LL, 200LL));
                        break;
                    case 2:
                        l = rnd.uniform(1LL, LR_MAX);
                        r = l;
                        break;
                    case 3: {
                        i64 k = rnd.uniform(1LL, LR_MAX / a);
                        l = std::max(1LL, k * a - rnd.uniform(0LL, 1LL));
                        r = std::min(LR_MAX, k * a + rnd.uniform(0LL, 1LL));
                        break;
                    }
                    default:
                        a = rnd.uniform(1LL, 10LL);
                        l = rnd.uniform(1LL, 1000000LL);
                        r = LR_MAX - rnd.uniform(0LL, 1000000LL);
                }
            } else if (seed == 0) {
                a = i % 2 ? A_MAX : 1;
            } else if (seed == 1) {
                // Near 10^18, both parities of the quotient and all endpoint alignments.
                a = i % A_MAX + 1;
                i64 k = LR_MAX / a - i % 3;
                l = std::max(1LL, k * a - i % 2);
                r = std::min(LR_MAX, l + i % 4);
            } else {
                // Large answers and large quotients that do not fit in 32 bits.
                l = i % 2 + 1;
                r = LR_MAX - i;
                a = i % 100 + 1;
            }
            add(l, r, a);
        }
    }
    std::printf("%d\n", static_cast<int>(cases.size()));
    for (const auto &q : cases)
        std::printf("%lld %lld %lld\n", std::get<0>(q), std::get<1>(q), std::get<2>(q));
    return 0;
}
