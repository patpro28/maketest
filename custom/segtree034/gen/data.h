#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "random.h"
#include "../params.h"

constexpr int KIND = 34;
inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rnd(20261020ULL + KIND * 10000ULL + mode * 100ULL + seed);
    const int low = VALUE_MIN, high = VALUE_MAX;
    auto value = [&]() -> int {
        if (KIND == 4) return rnd.uniform(0, 1) ? 1 : -1;
        if (rnd.uniform(0, 2) == 0) return rnd.uniform(low, high);
        static const int special[] = {-1000000000, -100000000, -10000, -7, -1, 0, 1, 2, 6, 12, 10000, 100000000, 1000000000};
        int x;
        do { x = special[rnd.uniform(0, 12)]; } while (x < low || x > high);
        return x;
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
        if (pattern == 3) x = std::max(low, 0);
        if (pattern == 4) x = i % 2 ? low : high;
        if (pattern == 5) x = std::clamp(i % 17 - 8, low, high);
        if (pattern == 6) x = std::clamp(-7, low, high);
        if (pattern == 7) x = std::clamp(n - i, low, high);
        if (pattern == 8) x = std::clamp((i / 3) * 6 - 30, low, high);
        if (pattern == 11) x = i % 2 ? low : high;
        if (mode == 3 && seed == 3) x = KIND == 25 ? n - i : std::clamp(7, low, high);
        if (KIND == 4) {
            x = value();
            if (pattern == 1) x = -1;
            if (pattern == 2) x = 1;
            if (pattern == 3 || pattern == 7) x = i % 2 ? -1 : 1;
            if (pattern == 4) x = i % 2 ? 1 : -1;
            if (pattern == 5 || pattern == 6) x = i < n / 2 ? 1 : -1;
            if (pattern == 8 || pattern == 11) { static const int trick[] = {1, -1, -1, 1, 1, -1}; x = trick[i % 6]; }
        }
        a[i] = x;
    }
    std::printf("%d %d\n", n, q);
    if (KIND == 4) { for (int x : a) std::putchar(x == 1 ? '(' : ')'); std::putchar('\n'); }
    else for (int i = 0; i < n; ++i) std::printf("%d%c", a[i], i + 1 == n ? '\n' : ' ');
    for (int j = 0; j < q; ++j) {
        bool update = j % 3 == 1;
        if (mode == 2) update = rnd.uniform(0, 99) < (seed % 3 == 0 ? 10 : seed % 3 == 1 ? 50 : 90);
        if (mode == 0 && seed == 9) update = false;
        if (mode == 0 && seed == 10) update = true;
        if (mode == 3 && seed == 1) update = false;
        if (mode == 3 && seed == 5) update = j + 1 != q;
        if (KIND == 3 || KIND == 4) update = false;
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
            if (KIND == 25 && l == r) { if (r + 1 < n) ++r; else --l; }
            if (KIND == 3 || KIND == 4) std::printf("%d %d\n", l + 1, r + 1);
            else if (KIND == 15 || KIND == 34) {
                int c = value();
                if (j % 6 == 0) c = low;
                if (j % 6 == 1) c = high;
                if (j % 6 == 2) c = a[l];
                if (j % 6 == 3) c = 0;
                if (j % 6 == 5) c = a[r];
                std::printf("2 %d %d %d\n", l + 1, r + 1, c);
            } else std::printf("2 %d %d\n", l + 1, r + 1);
        }
    }
    return 0;
}
