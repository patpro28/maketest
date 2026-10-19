#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "random.h"
#include "../params.h"

inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rnd(20261016ULL + mode * 1000ULL + seed);
    int n = 2, m = 0;
    std::vector<int> slippery;
    if (mode == 0) {
        const std::vector<int> sizes = {2,2,2,2,3,3,3,3,6,6,6,6,10,10,10,10};
        const std::vector<int> counts = {0,1,0,1,0,1,1,1,0,1,2,3,30,4,5,6};
        const std::vector<std::vector<int>> lists = {
            {},{}, {1},{2}, {1},{1},{3},{1,3}, {2,4,5},{2,4,5},{2,4,5},{2,4,5},
            {},{1,3,5,7,9},{2,4,6,8,10},{2,3,4,5,6,7,8,9,10}};
        n = sizes[seed]; m = counts[seed]; slippery = lists[seed];
    } else if (mode == 1) {
        n = seed < 4 ? seed + 2 : 20;
        m = seed % 8;
        for (int i = 1; i <= n; ++i)
            if (rnd.uniform(0, 2) == 0) slippery.push_back(i);
        if (seed == 0) slippery.clear();
        if (static_cast<int>(slippery.size()) == n) slippery.pop_back();
    } else if (mode == 2) {
        n = rnd.uniform(100, static_cast<int>(N_MAX));
        m = seed % 4 == 0 ? 0 : rnd.uniform(1, static_cast<int>(M_MAX));
        int pattern = seed % 4;
        for (int i = 1; i <= n; ++i) {
            bool choose = pattern == 0 ? rnd.uniform(0, 2) == 0 :
                          pattern == 1 ? rnd.uniform(1, n) <= 15 :
                          pattern == 2 ? i <= 20 : i > n - 20;
            if (choose) slippery.push_back(i);
        }
    } else if (mode == 3) {
        n = N_MAX;
        m = seed % 2 ? 0 : M_MAX;
        if (seed == 0 || seed == 1) { /* no slippery stairs */ }
        else if (seed == 2) {
            for (int i = 1; i <= 30; ++i) slippery.push_back(i * 3000);
        } else if (seed == 3) {
            for (int i = 2; i <= n; i += 2) slippery.push_back(i);
        } else if (seed == 4 || seed == 5) {
            for (int i = 2; i <= n; ++i) slippery.push_back(i);
        } else if (seed == 6) {
            slippery = {1, n};
        } else {
            for (int i = n - 30; i <= n; ++i) slippery.push_back(i);
        }
    } else {
        n = N_MAX;
        m = 0;
        for (int i = 1; i <= n; ++i) {
            bool choose = seed == 0 ? false : seed == 1 ? i == 1 : seed == 2 ? i == n :
                          seed == 3 ? i % 2 == 0 : seed == 4 ? i > 1 : rnd.uniform(0, 3) == 0;
            if (choose) slippery.push_back(i);
        }
    }
    rnd.shuffle(slippery.begin(), slippery.end());
    std::printf("%d %d %d\n", n, static_cast<int>(slippery.size()), m);
    for (std::size_t i = 0; i < slippery.size(); ++i) {
        if (i) std::printf(" ");
        std::printf("%d", slippery[i]);
    }
    std::printf("\n");
    return 0;
}
