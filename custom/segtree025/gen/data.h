#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "random.h"
#include "../params.h"

constexpr int KIND = 25;
inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rnd(20261020ULL + 1000000ULL + KIND * 10000ULL + mode * 100ULL + seed);
    const int low = VALUE_MIN, high = VALUE_MAX;
    const int sizes[] = {1, 2, 3, 5, 8, 9, 17, 31, 32, 33, 65, 7};
    int n = mode == 0 ? sizes[seed] : mode == 1 ? rnd.uniform(1, 30) :
            mode == 2 ? rnd.uniform(1000, 20000) : int(N_MAX) - (seed == 5);
    int q = mode == 0 ? 60 : mode == 1 ? 200 :
            mode == 2 ? rnd.uniform(1000, 20000) : int(Q_MAX);
    static const long long bounds[] = {1, 30, 29, 1000000000000000000LL, 1000000000000000000LL, 6, 7, 1000000000, 999999999, 97, 1000000000000000000LL, 12};
    static const int mods[] = {1, 7, 1000000000, 2, 999999937, 97, 3, 1, 999999999, 1000000000, 2, 7};
    static const int divisors[] = {1, 3, 1000000000, 7, 2, 999999937, 6, 1, 10, 1000000000, 3, 7};
    long long setting = 0;
    if (KIND == 15) setting = mode == 0 ? mods[seed] : mods[seed % 12];
    if (KIND == 33) setting = mode == 0 ? bounds[seed] : bounds[seed % 12];
    if (KIND == 51) setting = mode == 0 ? divisors[seed] : divisors[seed % 12];
    auto value = [&]() -> int {
        if (KIND == 51 && rnd.uniform(0, 2) == 0) {
            long long x;
            do { x = setting * rnd.uniform(-2, 2); } while (x < low || x > high);
            return int(x);
        }
        if (rnd.uniform(0, 2) == 0) return rnd.uniform(low, high);
        static const int special[] = {-1000000000, -7, -1, 0, 1, 2, 3, 5, 6, 7, 12, 30, 97, 999999937, 1000000000};
        int x;
        do { x = special[rnd.uniform(0, 14)]; } while (x < low || x > high);
        return x;
    };
    int pattern = mode == 0 ? seed : seed % 6;
    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        long long x = value();
        if (pattern == 1) x = low;
        if (pattern == 2) x = high;
        if (pattern == 3) x = std::max(low, 0);
        if (pattern == 4) x = i % 2 ? low : high;
        if (pattern == 5) x = std::clamp(i % 17 - 8, low, high);
        if (pattern == 6) x = std::clamp(-7, low, high);
        if (pattern == 7) x = n - i;
        if (pattern == 8) x = std::clamp((i / 3) * 6 - 30, low, high);
        if (pattern == 11) x = i % 2 ? low : high;
        if (mode == 3 && seed == 3) x = std::clamp(7, low, high);
        if (KIND == 33 && mode == 0) {
            if (seed == 0) x = 1;
            if (seed == 1 || seed == 2) { static const int v[] = {6, 5, 1}; x = v[i % 3]; }
            if (seed == 3 || seed == 4) { static const int v[] = {999999937, 999999929, 999999893, 999999883, 1}; x = v[i % 5]; }
            if (seed == 5) x = 1;
            if (seed == 6) x = 2;
            if (seed == 7) { static const int v[] = {1, 2, 5, 10, 1000000000}; x = v[i % 5]; }
            if (seed == 8) x = 1000000000;
            if (seed == 9) x = 97;
            if (seed == 11) x = 6;
        }
        if (KIND == 51 && mode == 0 && seed == 11) { static const int v[] = {0, 7, -7, 8, -8}; x = v[i % 5]; }
        a[i] = x;
    }
    if (KIND == 15 || KIND == 33 || KIND == 51) std::printf("%d %d %lld\n", n, q, setting);
    else std::printf("%d %d\n", n, q);
    for (int i = 0; i < n; ++i) std::printf("%lld%c", a[i], i + 1 == n ? '\n' : ' ');
    for (int j = 0; j < q; ++j) {
        bool update = j % 3 == 1;
        if (mode == 2) update = rnd.uniform(0, 99) < (seed % 3 == 0 ? 10 : seed % 3 == 1 ? 50 : 90);
        if (mode == 0 && seed == 9) update = false;
        if (mode == 0 && seed == 10) update = true;
        if (mode == 3 && seed == 1) update = false;
        if (mode == 3 && seed == 5) update = j + 1 != q;
        if (KIND == 4) update = false;
        if (update) {
            int pos = rnd.uniform(0, n - 1);
            if (j % 4 == 1 || (mode == 0 && seed == 11)) pos = n / 2;
            if (j % 7 == 1) pos = 0;
            if (j % 7 == 2) pos = n - 1;
            int x = value();
            if (j % 5 == 1) x = KIND == 14 ? 0 : int(a[pos]);
            if (j % 5 == 2) x = low;
            if (j % 5 == 3) x = high;
            if (mode == 0 && seed == 11) x = KIND == 14 ? high : j % 2 ? low : high;
            if (KIND == 33 && mode == 0 && seed == 11) { pos = n / 2; x = j % 2 ? 5 : 6; }
            if (KIND == 14) a[pos] += x;
            else a[pos] = x;
            std::printf("1 %d %d\n", pos + 1, x);
        } else {
            int l = rnd.uniform(0, n - 1), r = rnd.uniform(0, n - 1);
            if (l > r) std::swap(l, r);
            if (mode == 3 && (seed == 1 || seed == 3)) { l = rnd.uniform(0, n / 4); r = rnd.uniform(3 * n / 4, n - 1); }
            if (j % 6 == 0) { l = 0; r = n - 1; }
            if (j % 6 == 2) l = r = n / 2;
            if (j % 6 == 3) l = 0;
            if (j % 6 == 4) r = n - 1;
            if (mode == 3 && seed == 5) { l = 0; r = n - 1; }
            if (KIND == 33 && mode == 0 && seed == 3 && j % 8 == 3) { l = 0; r = 1; }
            if (KIND == 4) std::printf("%d %d\n", l + 1, r + 1);
            else std::printf("2 %d %d\n", l + 1, r + 1);
        }
    }
    return 0;
}
