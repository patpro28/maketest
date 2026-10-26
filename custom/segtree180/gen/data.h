#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "random.h"
#include "../params.h"

constexpr int KIND = 180;
inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rnd(20261020ULL + 2000000ULL + KIND * 10000ULL + mode * 100ULL + seed);
    const int low = VALUE_MIN, high = VALUE_MAX;
    auto value = [&]() -> int {
        if (rnd.uniform(0, 2) == 0) return rnd.uniform(low, high);
        static const int special[] = {-1000000000, -7, -1, 0, 1, 2, 3, 7, 1000000000};
        int x;
        do { x = special[rnd.uniform(0, 8)]; } while (x < low || x > high);
        return x;
    };
    const int sizes[] = {1, 2, 3, 5, 8, 9, 17, 31, 32, 33, 65, 7};
    int n = mode == 0 ? sizes[seed] : mode == 1 ? rnd.uniform(1, 30) :
            mode == 2 ? rnd.uniform(1000, 20000) : int(N_MAX) - (seed == 5);
    int q = mode == 0 ? 60 : mode == 1 ? 200 :
            mode == 2 ? rnd.uniform(1000, 20000) : int(Q_MAX);
    int pattern = mode == 0 ? seed : seed % 6;
    std::vector<long long> a(n);
    long long total = 0;
    int active = 0;
    for (int i = 0; i < n; ++i) {
        int x = value();
        if (pattern == 1) x = low;
        if (pattern == 2) x = high;
        if (pattern == 3) x = std::clamp(0, low, high);
        if (pattern == 4 || pattern == 11) x = i % 2 ? low : high;
        if (pattern == 5) x = std::clamp(i % 7 - 3, low, high);
        if (pattern == 6) x = std::clamp(7, low, high);
        if (pattern == 7) x = std::clamp(n - i, low, high);
        if (pattern == 8) x = std::clamp((i / 3) % 7, low, high);
        if (mode == 3 && seed == 1) {
            if (KIND == 100 || KIND == 120 || KIND == 130 || KIND == 140) x = 1;
            if (KIND == 110 || KIND == 160 || KIND == 180) x = 7;
            if (KIND == 150) x = high;
            if (KIND == 170 || KIND == 190) x = 0;
        }
        if (mode == 3 && seed == 3) x = std::clamp(7, low, high);
        a[i] = x; total += x; active += x > 0;
    }
    std::printf("%d %d\n", n, q);
    for (int i = 0; i < n; ++i) std::printf("%lld%c", a[i], i + 1 == n ? '\n' : ' ');
    int searches = 0;
    for (int j = 0; j < q; ++j) {
        if (KIND == 140) {
            int x = j % 4 == 0 ? 1 : j % 4 == 1 ? high : j % 4 == 2 ? int(std::max(1LL, a[n / 2])) : rnd.uniform(1, high);
            if (mode == 3 && seed == 1) x = 1;
            if (mode == 3 && seed == 3) x = 8;
            std::printf("%d\n", x);
            continue;
        }
        bool update = j % 3 == 1;
        if (mode == 2) update = rnd.uniform(0, 99) < (seed % 3 == 0 ? 10 : seed % 3 == 1 ? 50 : 90);
        if (mode == 0 && seed == 9) update = false;
        if (mode == 0 && seed == 10) update = true;
        if (mode == 3 && seed == 1) update = false;
        if (mode == 3 && seed == 5) update = j + 1 != q;
        if (update) {
            int pos = rnd.uniform(0, n - 1);
            if (j % 4 == 1 || (mode == 0 && seed == 11)) pos = n / 2;
            if (j % 7 == 1) pos = 0;
            if (j % 7 == 2) pos = n - 1;
            int x = value();
            if (j % 5 == 1) x = int(a[pos]);
            if (j % 5 == 2) x = low;
            if (j % 5 == 3) x = high;
            if (KIND == 100 || KIND == 120) x = 1 - int(a[pos]);
            total += x - a[pos]; active += int(x > 0) - int(a[pos] > 0); a[pos] = x;
            if (KIND == 100 || KIND == 120) std::printf("1 %d\n", pos + 1);
            else std::printf("1 %d %d\n", pos + 1, x);
            continue;
        }
        int which = searches++;
        long long target = j % 6 == 0 ? total + 1 : j % 6 == 1 ? std::max(1LL, total) : j % 6 == 2 ? 1 :
                           j % 6 == 3 ? 1000000000000000000LL : j % 6 == 4 ? rnd.uniform(1LL, 100000000000000LL) : std::max(1LL, a[n / 2]);
        if (KIND == 130 && mode == 3 && seed == 1) target = j % 2 ? n : n + 1;
        int k = j % 4 == 0 ? 1 : j % 4 == 1 ? n : j % 4 == 2 ? std::max(1, active) : std::min(n, active + 1);
        if (KIND == 100) std::printf("2\n");
        if (KIND == 110) {
            int c = j % 4 == 0 ? int(a[0]) : j % 4 == 1 ? int(a[n - 1]) : value();
            if (mode == 3 && seed == 1) c = 7;
            std::printf("2 %d\n", c);
        }
        if (KIND == 120) std::printf("2 %d\n", k);
        if (KIND == 130) std::printf("2 %lld\n", target);
        if (KIND == 150) {
            int x = j % 4 == 0 ? int(a[0]) : j % 4 == 1 ? int(std::max(0LL, a[0] - 1)) : j % 4 == 2 ? high : 0;
            if (mode == 3 && seed == 1) x = high - 1;
            std::printf("2 %d\n", x);
        }
        if (KIND == 160) {
            int l = rnd.uniform(0, n - 1), r = rnd.uniform(0, n - 1);
            if (l > r) std::swap(l, r);
            if (j % 6 == 0) { l = 0; r = n - 1; }
            if (j % 6 == 2) l = r = n / 2;
            if (j % 6 == 3) l = 0;
            if (j % 6 == 4) r = n - 1;
            int u = value(), v = value();
            if (u > v) std::swap(u, v);
            if (j % 7 == 0) { u = low; v = high; }
            if (j % 7 == 1) u = v = int(a[l]);
            if (j % 7 == 2) { u = int(std::max(static_cast<long long>(low), a[l] - 1)); v = int(std::min(static_cast<long long>(high), a[l] + 1)); }
            if (j % 7 == 3) u = v = low;
            if (j % 7 == 4) u = v = high;
            if (j % 7 == 6) { u = -1; v = 1; }
            if (mode == 3 && seed == 1) { l = 0; r = n - 1; u = v = 7; }
            std::printf("2 %d %d %d %d\n", l + 1, r + 1, u, v);
        }
        if (KIND == 170 || KIND == 180) {
            int l = rnd.uniform(0, n - 1);
            if (j % 8 == 0) l = 0;
            if (j % 8 == 1) l = n - 1;
            if (j % 8 == 2) l = n / 2;
            long long budget = j % 6 == 0 ? 0 : j % 6 == 1 ? total : j % 6 == 2 ? std::max(0LL, a[l] - 1) :
                               j % 6 == 3 ? a[l] : j % 6 == 4 ? 1000000000000000000LL : rnd.uniform(0LL, 1000000000000LL);
            int difference = j % 5 == 0 ? 0 : j % 5 == 1 ? high : j % 5 == 2 ? int(a[l]) : j % 5 == 3 ? rnd.uniform(0, high) : high;
            if (mode == 3 && seed == 1) { l = 0; budget = total; difference = 0; }
            if (KIND == 170) std::printf("2 %d %lld\n", l + 1, budget);
            else std::printf("2 %d %lld %d\n", l + 1, budget, difference);
        }
        if (KIND == 190) {
            int type = 2 + which % 3;
            int x = std::max(1, value());
            if (j % 4 == 0) x = high;
            if (j % 4 == 1) x = 1;
            if (j % 4 == 2) x = int(std::max(1LL, a[0]));
            if (type == 2) std::printf("2 %d\n", x);
            if (type == 3) std::printf("3 %lld\n", target);
            if (type == 4) std::printf("4 %d\n", k);
        }
    }
    return 0;
}
