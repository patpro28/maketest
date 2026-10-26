#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "random.h"
#include "../params.h"

constexpr int KIND = 30;
inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rnd(20261019ULL + KIND * 10000ULL + mode * 100ULL + seed);
    const int low = VALUE_MIN, high = VALUE_MAX;
    std::vector<int> divisors;
    for (int x = 1; x <= 2520; ++x) if (2520 % x == 0) divisors.push_back(x);
    auto value = [&]() -> int {
        if (KIND == 31) return divisors[rnd.uniform(0, int(divisors.size()) - 1)];
        if (rnd.uniform(0, 2) == 0) return rnd.uniform(low, high);
        static const int special[] = {-1000000000, -7, -1, 0, 1, 2, 6, 12, 30, 210, 999999937, 1000000000};
        int x;
        do { x = special[rnd.uniform(0, 11)]; } while (x < low || x > high);
        return x;
    };
    const int sizes[] = {1, 2, 3, 5, 8, 9, 17, 31, 32, 33, 65, 7};
    int n = mode == 0 ? sizes[seed] : mode == 1 ? rnd.uniform(1, 30) :
            mode == 2 ? rnd.uniform(1000, 20000) : int(N_MAX) - (seed == 5);
    int q = mode == 0 ? 60 : mode == 1 ? 200 :
            mode == 2 ? rnd.uniform(1000, 20000) : int(Q_MAX);
    int pattern = mode == 0 ? seed : seed % 6;
    int k = KIND == 2 ? value() : 0;
    if (KIND == 2) {
        if (pattern == 1) k = low;
        if (pattern == 2) k = high;
        if (pattern == 3 || pattern == 4 || pattern == 5) k = 0;
    }
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        int x = value();
        if (pattern == 1) x = low;
        if (pattern == 2) x = high;
        if (pattern == 3) x = KIND == 31 ? 8 : KIND == 30 ? 6 : 0;
        if (pattern == 4) x = i % 2 ? low : high;
        if (pattern == 5) x = KIND == 31 ? divisors[i % divisors.size()] : std::max(low, i % 17 - 8);
        if (pattern == 6) x = KIND == 31 ? 9 : KIND == 30 ? 30 : KIND == 21 ? -7 : 7;
        if (pattern == 7) x = KIND == 31 ? divisors[(n - 1 - i) % divisors.size()] : n - i;
        if (pattern == 8) x = KIND == 31 ? (i % 2 ? 8 : 9) : KIND == 30 ? (i % 2 ? 12 : 18) : (i % 2 ? low : high);
        if (mode == 3 && seed == 3) x = KIND == 31 ? 8 : KIND == 30 ? 210 : KIND == 21 ? -7 : 0;
        if (mode == 3 && seed == 4) x = KIND == 31 ? (i % 2 ? 8 : 9) : KIND == 30 ? (i % 2 ? 999999937 : 1000000000) : (i % 2 ? low : high);
        a[i] = x;
    }
    if (KIND == 2 && pattern == 9) { k = high; std::fill(a.begin(), a.end(), low); }
    if (KIND == 2 && pattern == 10) { k = low; std::fill(a.begin(), a.end(), high); }
    if (KIND == 2 && pattern == 11) { k = 0; for (int i = 0; i < n; ++i) a[i] = i % 3 - 1; }
    if (KIND == 21 && pattern == 11) { std::fill(a.begin(), a.end(), 7); a[n / 2] = -7; a[n - 1] = -7; }
    if (KIND == 2) std::printf("%d %d %d\n", n, q, k);
    else std::printf("%d %d\n", n, q);
    for (int i = 0; i < n; ++i) std::printf("%d%c", a[i], i + 1 == n ? '\n' : ' ');
    for (int j = 0; j < q; ++j) {
        bool update = j % 3 == 1;
        if (mode == 2) update = rnd.uniform(0, 99) < (seed % 3 == 0 ? 10 : seed % 3 == 1 ? 50 : 90);
        if (mode == 0 && seed == 9) update = false;
        if (mode == 0 && seed == 10) update = true;
        if (mode == 3 && seed == 1) update = false;
        if (mode == 3 && seed == 5) update = j + 1 != q;
        if (KIND == 0 || KIND == 2) update = false;
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
            if (KIND == 0 || KIND == 2) std::printf("%d %d\n", l + 1, r + 1);
            else std::printf("2 %d %d\n", l + 1, r + 1);
        }
    }
    return 0;
}
