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
    Random rnd(20261101ULL + 1530000ULL + mode * 100ULL + seed);
    std::vector<std::string> strings;
    if (mode == 0) {
        const std::vector<std::vector<std::string> > cases = {
            {"a", "a"}, {"a", "b"}, {"aaaaaa", "a", "aaa"},
            {"ab", "ba", "a"}, {"aa", "a", "aa"},
            {"ab", "ba", "b"}, {"abc", "acb", "bac"},
            {"xaybzc", "abc", "qabrc"}, {"ab", "bc", "ca"},
            {"aaab", "baaa", "aaba", "aaaa"},
            {"baba", "abab", "bbaa", "aabb"},
            {"cabca", "acabc", "bcaca", "abcac", "cacba"}
        };
        strings = cases[seed];
    } else if (mode == 1) {
        int k = rnd.uniform(2, 5);
        for (int i = 0; i < k; ++i) {
            int n = rnd.uniform(1, 8);
            std::string s(n, 'a');
            for (char &c : s) c = char('a' + rnd.uniform(0, 3));
            strings.push_back(s);
        }
    } else if (mode == 2) {
        int k = rnd.uniform(3, 12), length = seed % 2 ? 15 : 12;
        std::string base(length, 'a');
        for (char &c : base) c = char('a' + rnd.uniform(0, 4));
        for (int i = 0; i < k - 1; ++i) {
            std::string s;
            if (seed % 3 == 0) {
                for (char c : base) {
                    s += rnd.lower_string(rnd.uniform(0, 20)); s += c;
                }
                s += rnd.lower_string(30);
            } else s = rnd.lower_string(rnd.uniform(100, 600), 'a', 'e');
            strings.push_back(s);
        }
        int position = seed % k;
        strings.insert(strings.begin() + position, base);
    } else {
        int k = seed == 5 ? 2 : int(K_MAX);
        int used = int(SHORT_MAX);
        std::string base = seed == 1 || seed == 4 ? std::string(20, 'a') : "abcdefghijklmnopqrst";
        for (int i = 0; i < k - 1; ++i) {
            int n = (int(TOTAL_MAX) - used) / (k - 1 - i);
            std::string s;
            if (seed == 1) s.assign(n, 'a');
            else if (seed == 4) {
                s.assign(n, 'b');
                for (int j = 0; j < 10; ++j) s[j * (n - 1) / 9] = 'a';
            } else {
                // All subsets are feasible until the last record where specified.
                s = base;
                s += rnd.lower_string(n - 20);
                if (seed == 2 && i == k - 2) {
                    std::reverse(s.begin(), s.end());
                    s.assign(n, 'z'); s.replace(0, 20, "tsrqponmlkjihgfedcba");
                }
                if (seed == 3 && i == k - 2) s.assign(n, 'z');
            }
            used += n; strings.push_back(s);
        }
        int position = seed == 0 ? 0 : seed == 1 || seed == 5 ? k - 1 : k / 2;
        strings.insert(strings.begin() + position, base);
    }
    std::printf("%d\n", int(strings.size()));
    for (const std::string &s : strings) std::printf("%s\n", s.c_str());
    return 0;
}
