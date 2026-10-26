#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "random.h"
#include "../params.h"

constexpr int KIND = 22;
inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rnd(20261019ULL + KIND * 10000ULL + mode * 100ULL + seed);
    const int low = VALUE_MIN, high = VALUE_MAX;
    auto value = [&]() -> int {
        if (rnd.uniform(0, 2) == 0) return rnd.uniform(low, high);
        static const int special[] = {-1000000000, -30, -7, -2, -1, 0, 1, 2, 7, 30, 1000000000};
        return special[rnd.uniform(0, 10)];
    };
    const int sizes[] = {int(N_MIN), 2, 3, 5, 8, 9, 17, 31, 32, 33, 65, 7};
    int n = mode == 0 ? sizes[seed] : mode == 1 ? rnd.uniform(int(N_MIN), 30) :
            mode == 2 ? rnd.uniform(1000, 20000) : int(N_MAX) - (seed == 5);
    int q = mode == 0 ? 60 : mode == 1 ? 200 :
            mode == 2 ? rnd.uniform(1000, 20000) : int(Q_MAX);
    int pattern = mode == 0 ? seed : seed % 6;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        int x = value();
        if (pattern == 1) x = low;
        if (pattern == 2) x = high;
        if (pattern == 3) x = 0;
        if (pattern == 4) x = i % 2 ? low : high;
        if (pattern == 5) x = i % 17 - 8;
        if (pattern == 6) x = -7;
        if (pattern == 7) x = n - i;
        if (pattern == 8) x = (i / 3) * 6 - 30;
        if (mode == 3 && seed == 3) x = 7;
        if (pattern == 11) x = i % 2 ? -2 : -1;
        a[i] = x;
    }
    std::printf("%d %d\n", n, q);
    for (int i = 0; i < n; ++i) std::printf("%d%c", a[i], i + 1 == n ? '\n' : ' ');
    for (int j = 0; j < q; ++j) {
        bool update = j % 3 == 1;
        if (mode == 2) update = rnd.uniform(0, 99) < (seed % 3 == 0 ? 10 : seed % 3 == 1 ? 50 : 90);
        if (mode == 0 && seed == 9) update = false;
        if (mode == 0 && seed == 10) update = true;
        if (mode == 3 && seed == 1) update = false;
        if (mode == 3 && seed == 5) update = j + 1 != q;
        if (KIND == 1) update = false;
        if (update) {
            int pos = rnd.uniform(0, n - 1);
            if (j % 4 == 1 || (mode == 0 && seed == 11)) pos = n / 2;
            if (j % 7 == 1) pos = 0;
            if (j % 7 == 2) pos = n - 1;
            int x = value();
            if (j % 5 == 1) x = a[pos];
            if (j % 5 == 2) x = low;
            if (j % 5 == 3) x = high;
            if (mode == 0 && seed == 11) x = j % 2 ? low : high;
            a[pos] = x;
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
            if (KIND == 22 && l == r) { if (r + 1 < n) ++r; else --l; }
            if (KIND == 1) std::printf("%d %d\n", l + 1, r + 1);
            else if (KIND == 23) {
                int u = value(), v = value();
                if (u > v) std::swap(u, v);
                if (j % 8 == 0) { u = low; v = high; }
                if (j % 8 == 1) u = v = a[l];
                if (j % 8 == 2) u = v = low;
                if (j % 8 == 3) u = v = high;
                if (j % 8 == 4) { u = std::min(a[l], a[r]); v = std::max(a[l], a[r]); }
                if (j % 8 == 5) { u = -1; v = 1; }
                if (j % 8 == 6) u = v = 0;
                std::printf("2 %d %d %d %d\n", l + 1, r + 1, u, v);
            } else std::printf("2 %d %d\n", l + 1, r + 1);
        }
    }
    return 0;
}
