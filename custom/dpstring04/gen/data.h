#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include "random.h"
#include "../params.h"

inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rnd(20261025ULL + KIND * 10000ULL + mode * 100ULL + seed);
    const std::string alphabet = ALPHABET;
    const int sizes[] = {1, 2, 3, 4, 5, 6, 7, 8, 10, 12};
    int n = mode == 0 ? sizes[seed] : mode == 1 ? rnd.uniform(1, KIND == 4 || KIND == 9 ? 7 : 12) :
            mode == 2 ? rnd.uniform(300, 3000) : int(N_MAX) - (seed % 2);
    if (mode == 0 && (KIND == 4 || KIND == 9)) n = std::min(n, 7);
    std::string s(n, alphabet[0]);
    int pattern = mode == 0 ? seed : seed % 6;
    for (int i = 0; i < n; ++i) {
        s[i] = alphabet[rnd.uniform(0, int(alphabet.size()) - 1)];
        if (mode != 1) {
            if (pattern == 1) s[i] = alphabet[0];
            if (pattern == 2) s[i] = alphabet[i % 2];
            if (pattern == 3) s[i] = alphabet[(i / 3) % 2];
            if (pattern == 4) s[i] = alphabet[(i / 2) % 2];
            if (pattern == 5) s[i] = alphabet[i % alphabet.size()];
            if (pattern == 6) s[i] = alphabet.back();
            if (pattern == 7) s[i] = alphabet[(i + (i / 4)) % alphabet.size()];
        }
    }
    if (KIND == 1 || KIND == 6) {
        const std::string pool = mode == 0 && seed == 6 ? "aeiou" :
                                 mode == 0 && seed == 7 ? "bcdfg" : "aeioubcdfgz";
        for (int i = 0; i < n; ++i) {
            s[i] = pool[rnd.uniform(0, int(pool.size()) - 1)];
            if (pattern == 1) s[i] = 'a';
            if (pattern == 2) s[i] = i % 2 ? 'z' : 'e';
            if (pattern == 3) s[i] = "abbb"[i % 4];
            if (pattern == 4) s[i] = "aaabb"[i % 5];
        }
    }
    if (KIND == 5) {
        if (mode == 0 && seed == 0) s = "?";
        if (pattern == 1) s.assign(n, '?');
        if (pattern == 3) { s.assign(n, '?'); s[0] = 'A'; s[n-1] = 'B'; }
        if (pattern == 4) { s.assign(n, '?'); s[0] = 'B'; s[n-1] = 'A'; }
        if (pattern == 5) for (int i = 0; i < n; ++i) s[i] = "AB?"[i % 3];
    }
    if (KIND == 8 && pattern == 3) for (int i = 0; i < n; ++i) s[i] = "abba"[i % 4];
    if (KIND == 9 && pattern == 5) for (int i = 0; i < n; ++i) s[i] = "ABCA"[i % 4];
    std::vector<long long> w(n);
    for (int i = 0; i < n; ++i) {
        w[i] = rnd.uniform(0LL, static_cast<long long>(W_MAX));
        if (mode == 1) w[i] = rnd.uniform(0LL, 20LL);
        if (pattern == 1) w[i] = W_MAX;
        if (pattern == 2) w[i] = 0;
        if (pattern == 3) w[i] = i % 2 ? 1 : W_MAX;
        if (pattern == 4) w[i] = i % 2 ? W_MAX : 0;
        if (pattern == 5) w[i] = W_MAX;
        if (mode == 0 && seed == 9) w[i] = (i == n/2 ? W_MAX : 1);
    }
    if (KIND == 5) {
        long long x = seed % 3 == 0 ? 0 : seed % 3 == 1 ? 1 : W_MAX;
        long long y = seed % 3 == 2 ? 0 : W_MAX;
        std::printf("%d %lld %lld\n", n, x, y);
    } else std::printf("%d\n", n);
    std::printf("%s\n", s.c_str());
    if (KIND != 0 && KIND != 5) {
        for (int i = 0; i < n; ++i) std::printf("%lld%c", w[i], i + 1 == n ? '\n' : ' ');
    }
    return 0;
}
