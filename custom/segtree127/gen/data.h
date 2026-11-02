#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "random.h"
#include "../params.h"
constexpr int KIND = 127;
inline long long pairs(long long c) { return c * (c - 1) / 2; }
inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rnd(20261031ULL + KIND * 10000ULL + mode * 100ULL + seed);
    const int sizes[] = {1,2,3,5,8,9,17,31,32,33,65,7};
    int n = mode == 0 ? sizes[seed] : mode == 1 ? rnd.uniform(1,30) : mode == 2 ? rnd.uniform(1000,20000) : int(N_MAX) - (seed == 5);
    int q = mode == 0 ? 80 : mode == 1 ? 250 : mode == 2 ? rnd.uniform(1000,20000) : int(Q_MAX);
    int pattern = mode == 0 ? seed : seed % 6;
    std::vector<long long> a(n + 1), b(n + 1);
    const long long big = 1000000000000000000LL;
    auto value = [&]() -> long long {
        if (KIND == 126) return rnd.uniform(0,3) ? rnd.uniform(1,4) : 1000000000;
        if (KIND == 129) { const int v[] = {0,1,2,3,4,9999,10000}; return rnd.uniform(0,2) ? v[rnd.uniform(0,6)] : rnd.uniform(0,10000); }
        return rnd.uniform(0,3) ? rnd.uniform(0,3) : 1000000000;
    };
    long long total = 0; int missing = 0;
    for (int i = 1; i <= n; ++i) {
        a[i] = value();
        if (pattern == 1) a[i] = KIND == 126 ? 1 : 0;
        if (pattern == 2) a[i] = KIND == 126 ? 1000000000 : KIND == 129 ? 10000 : 1000000000;
        if (pattern == 3) a[i] = KIND == 126 ? i % 2 + 1 : 1;
        if (pattern == 4) a[i] = KIND == 126 ? (i - 1) / 3 + 1 : i % 2;
        if (pattern == 5) a[i] = KIND == 126 ? (i == n ? 2 : 1) : (i == n ? 0 : 1);
        if (KIND == 116) {
            a[i] = pattern == 2 ? 1000000000LL - n + i : (i - 1) * 1000LL + 1;
            long long next = pattern == 2 ? a[i] + 1 : a[i] + 1000;
            b[i] = std::min(1000000000LL, next + rnd.uniform(-1,1));
            if (pattern == 1 || pattern == 3) b[i] = a[i];
            if (pattern == 4) b[i] = 1000000000;
            if (pattern == 5) b[i] = std::min(1000000000LL, next);
        }
        if (mode == 3 && seed == 1) {
            if (KIND == 116) b[i] = i == n - 1 ? a[i] + 1001 : a[i];
            if (KIND == 126) a[i] = i == n ? 2 : 1;
            if (KIND == 127) a[i] = i == n ? 0 : 1;
            if (KIND == 129) a[i] = 10000;
        }
        if (KIND == 129) total += pairs(a[i]);
        if (KIND == 127) missing += a[i] == 0;
    }
    std::printf("%d %d\n", n, q);
    if (KIND != 128) for (int i = 1; i <= n; ++i) std::printf("%lld%c", a[i], i == n ? '\n' : ' ');
    if (KIND == 116) for (int i = 1; i <= n; ++i) std::printf("%lld%c", b[i], i == n ? '\n' : ' ');
    for (int j = 0; j < q; ++j) {
        int pos = rnd.uniform(1,n);
        if (j % 7 == 0) pos = 1;
        if (j % 7 == 1) pos = n;
        if (j % 7 == 2) pos = std::max(1,n/2);
        bool update = j % 3 == 1;
        if (mode == 2) update = rnd.uniform(0,99) < (seed % 3 == 0 ? 10 : seed % 3 == 1 ? 50 : 90);
        if (mode == 0 && seed == 9) update = false;
        if (mode == 0 && seed == 10) update = true;
        if (mode == 3 && seed == 1) update = false;
        if (mode == 3 && seed == 5) update = j + 1 != q;
        if (update) {
            if (KIND == 116) {
                long long x = std::min(1000000000LL, (pos == n ? a[pos] : a[pos + 1]) + (j % 3 - 1));
                x = std::max(a[pos],x);
                if (j % 5 == 0) x = 1000000000;
                if (j % 5 == 1) x = a[pos];
                if (j % 5 == 2) x = b[pos];
                b[pos] = x; std::printf("1 %d %lld\n",pos,x);
            } else if (KIND == 127) {
                int type = a[pos] == 0 || rnd.uniform(0,1) == 0 ? 1 : 2;
                missing -= a[pos] == 0; a[pos] += type == 1 ? 1 : -1; missing += a[pos] == 0;
                std::printf("%d %d\n",type,pos);
            } else if (KIND == 128) std::printf("1 %d\n",j % 5 == 0 ? 1 : j % 5 == 1 ? n : pos);
            else {
                long long x = value();
                if (j % 5 == 0) x = a[pos];
                if (j % 5 == 1) x = KIND == 126 ? 1 : 0;
                if (j % 5 == 2) x = KIND == 126 ? 1000000000 : 10000;
                if (KIND == 129) total += pairs(x) - pairs(a[pos]);
                a[pos] = x; std::printf("1 %d %lld\n",pos,x);
            }
        } else {
            if (KIND == 116) std::printf("2\n");
            if (KIND == 126) {
                int k = j % 4 == 0 ? 1 : j % 4 == 1 ? n : j % 4 == 2 ? std::min(n,2) : rnd.uniform(1,n);
                if (mode == 3 && seed == 1) k = 2;
                std::printf("2 %d\n",k);
            }
            if (KIND == 127) {
                int k = j % 4 == 0 ? 1 : j % 4 == 1 ? n : j % 4 == 2 ? std::max(1,missing) : std::min(n,missing+1);
                if (mode == 3 && seed == 1) k = 1;
                std::printf("3 %d\n",k);
            }
            if (KIND == 128) std::printf("2 %d\n", mode == 3 && seed == 1 ? n : j % 3 == 0 ? 1 : j % 3 == 1 ? n : rnd.uniform(1,n));
            if (KIND == 129) {
                long long k = j % 6 == 0 ? 1 : j % 6 == 1 ? std::max(1LL,total) : j % 6 == 2 ? total + 1 : j % 6 == 3 ? big : j % 6 == 4 ? 2147483648LL : rnd.uniform(1LL,std::max(1LL,total));
                if (mode == 3 && seed == 1) k = total;
                std::printf("2 %lld\n",k);
            }
        }
    }
    return 0;
}
