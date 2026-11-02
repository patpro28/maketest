#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "random.h"
#include "../params.h"
inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rnd(20261101311ULL + mode * 100ULL + seed);
    const int sizes[] = {1,2,3,5,8,9,17,31,32,33,65,7};
    int n = mode == 0 ? sizes[seed] : mode == 1 ? rnd.uniform(1,30) : mode == 2 ? rnd.uniform(1000,15000) : int(N_MAX) - (seed == 5);
    int m = mode == 0 ? 90 : mode == 1 ? 250 : mode == 2 ? rnd.uniform(1000,15000) : int(Q_MAX);
    int pattern = mode == 0 ? seed : seed % 6;
    auto value = [&]() -> int {
        const int specials[] = {-1000000000,-19,-2,-1,0,1,2,7,1000000000};
        return rnd.uniform(0,2) ? specials[rnd.uniform(0,8)] : rnd.uniform(-1000000000,1000000000);
    };
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        int x = value();
        if (pattern == 1) x = -rnd.uniform(1,1000000000);
        if (pattern == 2) x = 1000000000;
        if (pattern == 3) x = i % 2 ? -1000000000 : 1000000000;
        if (pattern == 4) { const int values[] = {-1000000000,7,9,-4,2,11,-1000000000}; x = values[i % 7]; }
        if (pattern == 5) x = 0;
        if (pattern == 6) x = -1000000000;
        if (pattern == 7) x = i <= n/2 ? i+1 : -(i+1);
        if (pattern == 8) x = i <= n/2 ? -(i+1) : i+1;
        if (pattern == 9) x = i % 3 ? 0 : -1;
        if (pattern == 10) x = i % 3 ? 0 : 1;
        if (pattern == 11) x = i % 2 ? -8 : 5;
        a[i] = x;
    }
    if (mode == 3 && seed == 4) {
        std::fill(a.begin(),a.end(),-1000000000);
        for (int i = n/2-50; i <= n/2+50; ++i) a[i] = i % 3 ? 1000000000 : -1;
    }
    if (mode == 3 && seed == 5) { std::fill(a.begin(),a.end(),-1000000000); a[n/2] = 1000000000; }
    std::printf("%d\n",n);
    for (int i = 0; i < n; ++i) std::printf("%d%c",a[i],i+1==n?'\n':' ');
    std::printf("%d\n",m);
    for (int j = 0; j < m; ++j) {
        bool update = j % 3 == 1;
        if (mode == 2) update = rnd.uniform(0,99) < (seed % 3 == 0 ? 10 : seed % 3 == 1 ? 50 : 90);
        if (mode == 0 && seed == 9) update = false;
        if (mode == 0 && seed == 10) update = true;
        if (mode == 3 && seed == 5) update = j+1 != m;
        if (update) {
            int pos = rnd.uniform(0,n-1), x = value();
            if (j % 7 == 0) pos = 0;
            if (j % 7 == 1) pos = n-1;
            if (j % 7 == 2 || (mode == 0 && seed == 11)) pos = n/2;
            if (j % 5 == 0) x = a[pos];
            if (j % 5 == 1) x = -1000000000;
            if (j % 5 == 2) x = 1000000000;
            if (j % 5 == 3) x = 0;
            if (mode == 3 && seed == 1) x = -rnd.uniform(1,1000000000);
            if (mode == 3 && seed == 2) x = 1000000000;
            a[pos] = x;
            std::printf("0 %d %d\n",pos+1,x);
        } else {
            int l = rnd.uniform(1,n), r = rnd.uniform(1,n);
            if (l > r) std::swap(l,r);
            if (j % 8 == 0) { l = 1; r = n; }
            if (j % 8 == 1) l = r;
            if (j % 8 == 2) l = 1;
            if (j % 8 == 3) r = n;
            if (j % 8 == 4) { l = 1; r = 1; }
            if (j % 8 == 5) { l = n; r = n; }
            if (mode == 3 && seed == 1) { l = rnd.uniform(1,n/4); r = rnd.uniform(n*3/4,n); }
            if (mode == 3 && seed == 2) { l = 1; r = n; }
            if (mode == 3 && seed == 5) { l = 1; r = n; }
            std::printf("1 %d %d\n",l,r);
        }
    }
    return 0;
}
