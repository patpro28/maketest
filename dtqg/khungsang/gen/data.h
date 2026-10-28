#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include "random.h"
#include "../params.h"
inline int generate(int argc, char** argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rng(2026102802ULL + 1000 * mode + seed);
    int r, c;
    if (mode == 0) {
        const int rows[] = {1,1,1,8,2,2,4,5,10,20,1,200};
        const int cols[] = {1,1,8,1,2,3,5,4,10,30,200,1};
        r = rows[seed]; c = cols[seed];
    } else if (mode == 1) { r = rng.uniform(1, 7); c = rng.uniform(1, 7); }
    else if (mode == 2) { r = 50; c = 60; }
    else {
        r = c = 1000;
        if (seed == 0) { r = 1; c = int(CELLS_MAX); }
        if (seed == 1) { r = int(CELLS_MAX); c = 1; }
        if (seed == 9) { r = 100; c = 10000; }
        if (seed == 10) { r = 10000; c = 100; }
        if (seed == 11) { r = 2; c = int(CELLS_MAX) / 2; }
    }
    std::cout << r << ' ' << c << '\n';
    for (int i = 0; i < r; ++i) {
        std::string row(c, '0');
        for (int j = 0; j < c; ++j) {
            bool one = rng.uniform(0, 99) < (seed % 3 == 0 ? 90 : seed % 3 == 1 ? 50 : 75);
            if (mode == 0) {
                if (seed == 0) one = false;
                if (seed >= 1 && seed <= 4) one = true;
                if (seed == 5) one = i > 0 || j != 1;
                if (seed == 6) one = (i + j) % 2;
                if (seed == 7) one = i + 1 < r;
                if (seed == 8) one = j <= i;
                if (seed >= 10) one = true;
            }
            if (mode == 3) {
                if (seed <= 2) one = true;
                if (seed == 3) one = false;
                if (seed == 4) one = (i + j) % 2;
                if (seed == 5) one = j <= i;
                if (seed == 6) one = j >= i;
                if (seed == 7) one = i % 37 != 0 && j % 41 != 0;
                if (seed == 8) one = rng.uniform(0, 99) < 90;
                if (seed == 11) one = i == 0 || j % 97 != 0;
            }
            row[j] = one ? '1' : '0';
        }
        std::cout << row << '\n';
    }
    return 0;
}
