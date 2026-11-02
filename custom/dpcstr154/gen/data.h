#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>
#include "random.h"
#include "../params.h"

inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rnd(20261101ULL + 1540000ULL + mode * 100ULL + seed);
    std::string a, b;
    if (mode == 0) {
        const std::vector<std::pair<std::string, std::string> > cases = {
            {"a", "a"}, {"a", "b"}, {"ab", "bb"}, {"aa", "ab"},
            {"abcde", "axbyczdwe"}, {"abca", "acba"}, {"aaaaa", "aa"},
            {"ab", "aaaabbbb"}, {"abc", "cba"}, {"ba", "aaaaab"},
            {"abac", "baca"}, {"z", "zzzzzzzz"}
        };
        a = cases[seed].first; b = cases[seed].second;
    } else if (mode == 1) {
        a = rnd.lower_string(rnd.uniform(1, 10), 'a', 'd');
        b = rnd.lower_string(rnd.uniform(1, 15), 'a', 'd');
    } else if (mode == 2) {
        a = rnd.lower_string(rnd.uniform(100, 500), 'a', seed % 2 ? 'z' : 'c');
        b = rnd.lower_string(rnd.uniform(1000, 10000), 'a', seed % 2 ? 'z' : 'c');
        if (seed == 3) {
            a.assign(300, 'a'); a += std::string(200, 'b');
            b.assign(5000, 'b'); b += std::string(5000, 'a');
        }
    } else {
        int n = int(N_MAX), m = int(M_MAX);
        if (seed == 0) {
            a = rnd.lower_string(n); b = rnd.lower_string(m);
        } else if (seed == 1) {
            a.assign(n, 'a'); b.assign(m, 'a');
        } else if (seed == 2) {
            a.assign(n, 'a'); b.assign(m, 'b');
        } else if (seed == 3) {
            for (int i = 0; i < n; ++i) a += "abcdefghijklmnopqrstuvwxyz"[i % 26];
            b.assign(m - n, 'z'); b += a;
        } else if (seed == 4) {
            a.assign(n / 2, 'a'); a += std::string(n / 2, 'b');
            b.assign(m / 2, 'b'); b += std::string(m / 2, 'a');
        } else if (seed == 5) {
            a.assign(n, 'a'); b.assign(m, 'b'); b[m - 1] = 'a';
        } else if (seed == 6) {
            for (int i = 0; i < n; ++i) a += "ab"[i % 2];
            b.assign(m - 2, 'z'); b += "ab";
        } else {
            a.assign(n, 'a'); b = "a";
        }
    }
    std::printf("%d %d\n%s\n%s\n", int(a.size()), int(b.size()), a.c_str(), b.c_str());
    return 0;
}
