#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "random.h"
#include "../params.h"
inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rnd(20261101ULL + mode * 100ULL + seed);
    const int sizes[] = {1,2,3,5,8,9,17,31,32,33,65,7};
    int n = mode == 0 ? sizes[seed] : mode == 1 ? rnd.uniform(1,30) : mode == 2 ? rnd.uniform(1000,15000) : int(N_MAX) - (seed == 5);
    int m = mode == 0 ? 80 : mode == 1 ? 200 : mode == 2 ? rnd.uniform(1000,15000) : int(Q_MAX);
    int pattern = mode == 0 ? seed : seed % 6;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        int x = rnd.uniform(1,1000000000);
        if (pattern == 1) x = 999999937;
        if (pattern == 2) x = i % 2 ? 10 : 6;
        if (pattern == 3) x = i % 2 ? 12 : 6;
        if (pattern == 4) x = i % 3 == 0 ? 1 : i % 3 == 1 ? 999999937 : 1000000000;
        if (pattern == 5) x = 2 * (i % 499 + 1);
        if (pattern == 6) x = 1000000000;
        if (pattern == 7) x = 1 << (i % 30);
        if (pattern == 8) { const int values[] = {6,10,15}; x = values[i % 3]; }
        if (pattern == 9) x = 1;
        if (pattern == 10) x = i % 2 ? 999999937 : 1000000000;
        if (pattern == 11) x = 30;
        a[i] = x;
    }
    if (pattern == 11) { a[0] = 6; a[n-1] = 6; }
    if (mode == 3 && seed == 5) { std::fill(a.begin(),a.end(),12); a[n/2] = 6; }
    std::printf("%d\n",n);
    for (int i = 0; i < n; ++i) std::printf("%d%c",a[i],i+1==n?'\n':' ');
    std::printf("%d\n",m);
    for (int j = 0; j < m; ++j) {
        int l = rnd.uniform(1,n), r = rnd.uniform(1,n);
        if (l > r) std::swap(l,r);
        if (j % 8 == 0) { l = 1; r = n; }
        if (j % 8 == 1) l = r;
        if (j % 8 == 2) l = 1;
        if (j % 8 == 3) r = n;
        if (j % 8 == 4) { l = 1; r = 1; }
        if (j % 8 == 5) { l = n; r = n; }
        if (mode == 3 && seed == 1) { l = rnd.uniform(1,std::max(1,n/4)); r = rnd.uniform(std::max(1,n*3/4),n); }
        if (mode == 3 && seed == 5) {
            l = std::max(1,n/2-100); r = std::min(n,n/2+100);
            if (j % 3 == 0) r = n/2;
            if (j % 3 == 1) l = n/2+2;
        }
        std::printf("%d %d\n",l,r);
    }
    return 0;
}
