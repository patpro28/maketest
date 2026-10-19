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
    Random rnd(20261015ULL + mode * 1000ULL + seed);
    int k = seed % 9 + 1;
    std::string s;
    auto digit = [&]() { return char('0' + rnd.uniform(0, 9)); };
    auto letter = [&]() {
        int c = rnd.uniform(0, 51);
        return char(c < 26 ? 'a' + c : 'A' + c - 26);
    };
    auto fill_blocks = [&](int n, int max_run) {
        bool numbers = seed % 2 == 0;
        while (static_cast<int>(s.size()) < n) {
            int len = rnd.uniform(1, max_run);
            len = std::min(len, n - static_cast<int>(s.size()));
            for (int i = 0; i < len; ++i) s += numbers ? digit() : letter();
            numbers = !numbers;
        }
    };
    if (mode == 0) {
        const std::vector<std::string> edge = {
            "0", "aBcXYZ", "0010a7b0012C56d00100e14f0000000g0009h16",
            "1234567890123456789012345678901234567890",
            "a1234b1357C1D5e25f37g101h1001i12345"};
        s = edge[seed / 9];
    } else if (mode == 1) {
        fill_blocks(60, 8);
        s += "a0B0000c7D14e49f98G999H000001000000000000";
    } else if (mode == 2) {
        fill_blocks(rnd.uniform(1000, static_cast<int>(N_MAX)), seed < 9 ? 20 : 2000);
    } else if (mode == 3) {
        if (seed / 9 == 0) {
            for (int i = 0; i < N_MAX; ++i) s += digit();
            s[0] = '9';
        } else if (seed / 9 == 1) {
            s.assign(N_MAX, '0');
        } else if (seed / 9 == 2) {
            for (int i = 0; i < N_MAX; ++i) s += letter();
        } else {
            fill_blocks(N_MAX, 3);
        }
    } else if (mode == 4) {
        k = 1;
        if (seed == 0) s = "a";
        else if (seed == 1) s = "5";
        else if (seed == 2) s.assign(N_MAX, '9');
        else if (seed == 3) s.assign(N_MAX, 'Z');
        else if (seed == 4) s = "a12345b0c123456789D12";
        else if (seed == 5) s = "12345678901234567890a12345678901234567890";
        else fill_blocks(N_MAX, seed % 2 ? 2 : 1000);
    } else {
        // All maximal digit runs have numerical value <= 10^12.
        if (seed / 9 == 0) {
            while (static_cast<int>(s.size()) < N_MAX) {
                long long value = rnd.uniform(0LL, 1000000000000LL);
                std::string block(rnd.uniform(0, 20), '0');
                block += std::to_string(value);
                int remaining = N_MAX - static_cast<int>(s.size());
                if (static_cast<int>(block.size()) > remaining) {
                    // Removing leading digits cannot increase a nonnegative value.
                    block = block.substr(block.size() - remaining);
                }
                s += block;
                if (static_cast<int>(s.size()) < N_MAX) s += letter();
            }
        } else {
            std::string tail = "1000000000000a999999999999B0c7D000000000001";
            s.assign(N_MAX - tail.size(), '0');
            s += tail;
        }
    }
    std::printf("%d\n%s\n", k, s.c_str());
    return 0;
}
