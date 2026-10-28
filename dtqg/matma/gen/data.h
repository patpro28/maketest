#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "random.h"
#include "../params.h"
inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rng(2026102702ULL + mode * 1000 + seed);
    long long length = mode == 0 ? 1 + seed : mode == 1 ? rng.uniform(1LL, 10LL)
                     : mode == 2 ? 100000 : L_MAX - seed * 17;
    std::vector<std::pair<std::string, int>> patterns;
    if (mode == 0) {
        if (seed == 0) patterns = {{"a", 1}};
        if (seed == 1) { length = 4; patterns = {{"a", -1}, {"b", -2}, {"c", -3}}; }
        if (seed == 2) { length = 10; patterns = {{"a", 1000}, {"a", -1000}, {"aa", 1}}; }
        if (seed == 3) patterns = {{"a", 1}, {"ba", 3}, {"aba", 5}};
        if (seed == 4) { length = 1; patterns = {{std::string(80, 'a'), 1000}}; }
        if (seed == 5) { length = L_MAX; patterns = {{"a", -1000}, {"b", -1000}, {"c", -1000}}; }
        if (seed == 6) { length = L_MAX; patterns = {{"a", 1000}}; }
        if (seed == 7) { length = L_MAX; patterns = {{std::string(80, 'a'), 1000}}; }
        if (seed == 8) for (int i = 1; i <= 12; ++i) patterns.push_back({std::string(i, 'a'), i % 2 ? 13 : -7});
        if (seed == 9) for (int i = 0; i < 20; ++i) patterns.push_back({"a", i % 2 ? -999 : 1000});
        if (seed == 10) { length = L_MAX; patterns = {{std::string(26, 'a'), -7}, {std::string(27, 'b'), 9}, {std::string(27, 'c'), 11}}; }
        if (seed == 11) patterns = {{"a", -9}, {"ab", 40}, {"b", -11}, {"ba", 35}, {"aba", -100}, {"bab", 80}};
    } else {
        if (mode == 3 && seed < 4) {
            if (seed == 0) patterns = {{"a", -1000}, {"b", -999}, {"c", -998}};
            if (seed == 1) patterns = {{"a", 1000}, {"aa", 1000}, {"aaa", 1000}, {"aaaa", 1000}};
            if (seed == 2) patterns = {{std::string(80, 'a'), 1000}};
            if (seed == 3) patterns = {{"ab", 1000}, {"ba", 1000}, {"a", -3}, {"b", -5}, {"c", -1000}};
        } else if (seed % 7 == 4) {
            for (int i = 0; i < 3; ++i) {
                std::string s(1, char('a' + i));
                int len = i == 0 ? 26 : 27;
                while (int(s.size()) < len) s += char('a' + rng.uniform(0, 2));
                patterns.push_back({s, rng.uniform(-1000, 1000)});
            }
        } else {
            int m = seed % 4 == 0 ? 20 : rng.uniform(1, 20);
            int remaining = 80;
            for (int i = 0; i < m; ++i) {
                int len = rng.uniform(1, std::min(12, remaining - (m - i - 1)));
                remaining -= len;
                std::string s;
                for (int j = 0; j < len; ++j) s += char('a' + rng.uniform(0, seed % 3 == 0 ? 0 : 2));
                int w = seed == 0 ? 0 : rng.uniform(-1000, 1000);
                patterns.push_back({s, w});
            }
        }
        if (mode == 3 && seed == 8) length = (1LL << 39) - 1;
        if (mode == 3 && seed == 9) length = (1LL << 39);
        if (mode == 3 && seed == 10) length = (1LL << 39) + 1;
    }
    std::cout << patterns.size() << ' ' << length << '\n';
    for (auto [s, w] : patterns) std::cout << s << ' ' << w << '\n';
    return 0;
}
