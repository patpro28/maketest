#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "random.h"
#include "../params.h"
constexpr int KIND = 161;
inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rnd(20261021ULL + KIND * 10000ULL + mode * 100ULL + seed);
    const int sizes[] = {1,2,3,5,8,9,17,31,32,33,65,7};
    int n = mode == 0 ? sizes[seed] : mode == 1 ? rnd.uniform(1,30) :
            mode == 2 ? rnd.uniform(1000,20000) : int(N_MAX) - (seed == 5);
    int q = mode == 0 ? 60 : mode == 1 ? 200 : mode == 2 ? rnd.uniform(1000,20000) : int(Q_MAX);
    if (KIND == 191) q = mode == 3 ? n : std::min(n, q);
    const int high = KIND == 172 ? 1048575 : 1000000000;
    const int low = KIND == 111 || KIND == 161 ? -1000000000 : KIND == 171 ? 1 : 0;
    auto value = [&]() -> long long {
        if (rnd.uniform(0,2) == 0) return rnd.uniform(low,high);
        const int special[] = {-1000000000,-7,-3,-1,0,1,2,3,6,7,12,18,999999999,1000000000};
        if (KIND == 172) return rnd.uniform(0,1) ? 1 << rnd.uniform(0,19) : 1048575;
        int x; do { x = special[rnd.uniform(0,13)]; } while (x < low || x > high);
        return x;
    };
    const long long big = 1000000000000000000LL;
    if (KIND == 191) {
        std::printf("%d %d\n",n,q);
        for (int j = 0; j < q; ++j) {
            int left = n - j;
            long long k = j % 6 == 0 ? 1 : j % 6 == 1 ? left : j % 6 == 2 ? left + 1LL :
                          j % 6 == 3 ? big : j % 6 == 4 ? 2 : rnd.uniform(1LL,big);
            if (mode == 3 && seed == 1) k = 2;
            if (mode == 3 && seed == 2) k = big;
            if (mode == 0 && seed == 9) k = 1;
            std::printf("%lld\n",k);
        }
        return 0;
    }
    int d = seed % 4 == 0 ? 1 : seed % 4 == 1 ? 3 : seed % 4 == 2 ? 1000000000 : 7;
    int count = n + (KIND == 101);
    std::vector<long long> a(count), b(n);
    int pattern = mode == 0 ? seed : seed % 6;
    long long total = 0;
    for (int i = 0; i < count; ++i) {
        long long x = value();
        if (pattern == 1) x = low;
        if (pattern == 2) x = high;
        if (pattern == 3) x = std::max(1,low);
        if (pattern == 4 || pattern == 11) x = i % 2 ? low : high;
        if (pattern == 5) x = std::clamp(static_cast<long long>(i % 7),static_cast<long long>(low),static_cast<long long>(high));
        if (pattern == 6) x = 7;
        if (pattern == 7) x = n - i + 1;
        if (pattern == 8) x = i % 3 == 0 ? low : high;
        if (mode == 3 && seed == 1) {
            if (KIND == 101) x = 1;
            if (KIND == 111) x = i + 1 == n ? 0 : 1;
            if (KIND == 121 || KIND == 131 || KIND == 181) x = i + 1 == n ? 1000000000 : 0;
            if (KIND == 151) x = 7;
            if (KIND == 161) { d = 3; x = i + 1 == n ? 0 : 1; }
            if (KIND == 171) x = 6;
            if (KIND == 172) x = i == 0 ? 1 : i + 1 == n ? 2 : 0;
        }
        a[i] = x; total += x;
        if (i < n) {
            b[i] = pattern == 1 ? 0 : pattern == 2 ? 1 : rnd.uniform(0,1);
            if (mode == 3 && seed == 1) b[i] = i + 1 == n;
        }
    }
    std::printf("%d %d",n,q);
    if (KIND == 161) std::printf(" %d",d);
    std::printf("\n");
    for (int i = 0; i < count; ++i) std::printf("%lld%c",a[i],i+1==count?'\n':' ');
    if (KIND == 181) for (int i = 0; i < n; ++i) std::printf("%lld%c",b[i],i+1==n?'\n':' ');
    for (int j = 0; j < q; ++j) {
        int pos = rnd.uniform(0,count-1);
        if (j % 7 == 0) pos = 0;
        if (j % 7 == 1) pos = count-1;
        if (j % 7 == 2) pos = count/2;
        if (KIND == 101) {
            int t = rnd.uniform(1,2);
            if (mode == 3 && seed == 1) { pos=n; t=j%2==0?2:1; }
            if (a[pos] == 0) t=1;
            a[pos] += t==1?1:-1;
            std::printf("%d %d\n",t,pos); continue;
        }
        bool update = j % 3 == 1;
        if (mode == 2) update = rnd.uniform(0,99) < (seed % 3 == 0 ? 10 : seed % 3 == 1 ? 50 : 90);
        if (mode == 0 && seed == 9) update = false;
        if (mode == 0 && seed == 10) update = true;
        if (mode == 3 && seed == 1) update = false;
        if (mode == 3 && seed == 5) update = j+1 != q;
        if (update) {
            long long x = value();
            if (j % 5 == 1) x = a[pos];
            if (j % 5 == 2) x = low;
            if (j % 5 == 3) x = high;
            if (KIND == 121) {
                x = std::max(1LL,x); total += x;
                std::printf("1 %d %lld\n",pos+1,x); continue;
            }
            total += x-a[pos]; a[pos]=x;
            std::printf("1 %d %lld",pos+1,x);
            if (KIND == 181) { b[pos]=rnd.uniform(0,1); std::printf(" %lld",b[pos]); }
            std::printf("\n"); continue;
        }
        int l = rnd.uniform(1,n), r = rnd.uniform(1,n);
        if (l > r) std::swap(l,r);
        if (j % 6 == 0) { l=1; r=n; }
        if (j % 6 == 1) l=r;
        if (j % 6 == 2) l=1;
        if (j % 6 == 3) r=n;
        if (mode == 3 && seed == 1) { l=1; r=n; }
        if (KIND == 111 || KIND == 131) std::printf("2 %d %d\n",l,r);
        if (KIND == 121) {
            long long k = j % 5 == 0 ? 1 : j % 5 == 1 ? big : j % 5 == 2 ? std::max(1LL,total) :
                          j % 5 == 3 ? total+1 : rnd.uniform(1LL,std::max(1LL,total+1));
            if (mode == 3 && seed == 1) k=1;
            std::printf("2 %lld\n",k); if (k<=total) --total;
        }
        if (KIND == 151) std::printf("2 %d\n",l);
        if (KIND == 161) {
            int k = j % 4 == 0 ? 1 : j % 4 == 1 ? n : j % 4 == 2 ? r-l+1 : rnd.uniform(1,n);
            if (mode == 3 && seed == 1) k=1;
            std::printf("2 %d %d %d\n",l,r,k);
        }
        if (KIND == 171) {
            long long g = j % 5 == 0 ? 1 : j % 5 == 1 ? a[l-1] : j % 5 == 2 ? high : j % 5 == 3 ? std::min(static_cast<long long>(high),a[l-1]+1) : 7;
            if (mode == 3 && seed == 1) g=2;
            std::printf("2 %d %lld\n",l,g);
        }
        if (KIND == 172) {
            int mask = j % 5 == 0 ? 1048575 : j % 5 == 1 ? 1 << rnd.uniform(0,19) : j % 5 == 2 ? std::max(1LL,a[l-1]) : j % 5 == 3 ? 3 : rnd.uniform(1,1048575);
            if (mode == 3 && seed == 1) mask=3;
            std::printf("2 %d %d\n",l,mask);
        }
        if (KIND == 181) {
            long long s = j % 5 == 0 ? 1 : j % 5 == 1 ? big : j % 5 == 2 ? std::max(1LL,total) : j % 5 == 3 ? std::max(1LL,a[l-1]) : total+1;
            int k = j % 4 == 0 ? 1 : j % 4 == 1 ? n : j % 4 == 2 ? r-l+1 : rnd.uniform(1,n);
            if (mode == 3 && seed == 1) { s=1; k=1; }
            std::printf("2 %d %lld %d\n",l,s,k);
        }
    }
    return 0;
}
