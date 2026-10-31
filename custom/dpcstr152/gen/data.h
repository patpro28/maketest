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
    Random rnd(20261028ULL + KIND * 10000ULL + mode * 100ULL + seed);
    const std::string alphabet = ALPHABET;
    const int ns[] = {1, 1, 2, 3, 5, 6, 7, 8, 5, 9};
    const int ms[] = {1, 4, 1, 3, 6, 5, 7, 8, 8, 9};
    int n = mode == 0 ? ns[seed] : mode == 1 ? rnd.uniform(1, 9) : mode == 2 ? rnd.uniform(30, int(N_MAX)/2) : int(N_MAX);
    int m = mode == 0 ? ms[seed] : mode == 1 ? rnd.uniform(1, 9) : mode == 2 ? rnd.uniform(30, int(N_MAX)/2) : int(N_MAX) - seed % 2;
    if (mode == 3 && seed == 5) n = 1;
    int pattern = mode == 0 ? seed : mode == 1 ? 0 : seed;
    std::string a(n, 'a'), b(m, 'a');
    for (char &c : a) c = alphabet[rnd.uniform(0, int(alphabet.size())-1)];
    for (char &c : b) c = alphabet[rnd.uniform(0, int(alphabet.size())-1)];
    if (pattern == 1) { a.assign(n, 'a'); b.assign(m, 'a'); }
    if (pattern == 2) { a.assign(n, 'a'); b.assign(m, 'b'); }
    if (pattern == 3) {
        for (int i = 0; i < n; ++i) a[i] = i < n/2 ? 'a' : 'b';
        for (int j = 0; j < m; ++j) b[j] = j < m/2 ? 'b' : 'a';
    }
    if (pattern == 4) {
        for (int i = 0; i < n; ++i) a[i] = "ab"[i%2];
        for (int j = 0; j < m; ++j) b[j] = "ba"[j%2];
    }
    if (pattern == 5) {
        for (int i = 0; i < n; ++i) a[i] = alphabet[i%alphabet.size()];
        for (int j = 0; j < m; ++j) b[j] = alphabet[(alphabet.size()-1)-(j%alphabet.size())];
    }
    if (pattern == 6) {
        for (int i = 0; i < n; ++i) a[i] = "aeiou"[i%5];
        for (int j = 0; j < m; ++j) b[j] = "aeiou"[j%5];
        if (KIND == 152) { a.assign(n, 'c'); b.assign(m, 'c'); }
    }
    if (pattern == 7) {
        a.assign(n, 'a'); b.assign(m, 'a'); a[n/2] = 'b'; b[m/2] = 'b';
    }
    if (pattern == 8) { a.assign(n, 'a'); b.assign(m, 'b'); b[m/2] = 'a'; }
    if (pattern == 9) {
        for (int i = 0; i < n; ++i) a[i] = "abx"[i%3];
        for (int j = 0; j < m; ++j) b[j] = "xab"[j%3];
        if (KIND == 152) { for (char &c : a) if (c == 'x') c = 'c'; for (char &c : b) if (c == 'x') c = 'c'; }
    }
    int k = mode == 0 ? seed % 6 : mode == 1 ? rnd.uniform(0, 5) : seed % 6;
    if (KIND == 151) std::printf("%d %d %d\n", n, m, k);
    else std::printf("%d %d\n", n, m);
    std::printf("%s\n%s\n", a.c_str(), b.c_str());
    if (KIND == 132 || KIND == 150) {
        char c = seed % 3 == 0 ? 'z' : seed % 3 == 1 ? 'a' : 'b';
        if (pattern == 9) c = 'x';
        std::printf("%c\n", c);
    }
    auto weight = [&](int i) -> long long {
        if (pattern == 1 || pattern == 3 || pattern == 5) return W_MAX;
        if (pattern == 2) return 0;
        if (pattern == 4) return i % 2 ? 1 : W_MAX;
        if (mode == 1) return rnd.uniform(0LL, 20LL);
        return rnd.uniform(0LL, static_cast<long long>(W_MAX));
    };
    if (KIND == 130) {
        for (int i = 0; i < 26; ++i) std::printf("%lld%c", weight(i), i == 25 ? '\n' : ' ');
    }
    if (KIND == 131) {
        for (int i = 0; i < n; ++i) std::printf("%lld%c", weight(i), i+1 == n ? '\n' : ' ');
        for (int j = 0; j < m; ++j) std::printf("%lld%c", weight(j+1), j+1 == m ? '\n' : ' ');
    }
    return 0;
}
