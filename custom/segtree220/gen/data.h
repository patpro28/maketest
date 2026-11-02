#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "random.h"
#include "../params.h"
inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rnd(20261101220ULL + mode * 100ULL + seed);
    const int sizes[] = {1,2,3,5,8,9,17,31,32,33,65,7};
    int n = mode == 0 ? sizes[seed] : mode == 1 ? rnd.uniform(1,30) : mode == 2 ? rnd.uniform(1000,15000) : int(N_MAX) - (seed == 5);
    int m = mode == 0 ? 90 : mode == 1 ? 250 : mode == 2 ? rnd.uniform(1000,15000) : int(Q_MAX);
    int pattern = mode == 0 ? seed : seed % 6;
    auto delta = [&]() -> int {
        const int values[] = {-10000,-7,-1,0,1,3,10000};
        return rnd.uniform(0,2) ? values[rnd.uniform(0,6)] : rnd.uniform(-10000,10000);
    };
    std::vector<int> a(n);
    for (int i=0; i<n; ++i) {
        int x=delta();
        if (pattern==1) x=-10000;
        if (pattern==2) x=10000;
        if (pattern==3) x=i%2 ? -10000 : 10000;
        if (pattern==4) x=0;
        if (pattern==5) x=-10000;
        if (pattern==6) x=-1;
        if (pattern==7) x=i%10001;
        if (pattern==8) x=-(i%10001);
        if (pattern==9) x=7;
        if (pattern==10) x=0;
        if (pattern==11) x=i==n/2 ? 10000 : -10000;
        a[i]=x;
    }
    std::printf("%d %d\n",n,m);
    for (int i=0; i<n; ++i) std::printf("%d%c",a[i],i+1==n?'\n':' ');
    for (int j=0; j<m; ++j) {
        bool update=j%3==1;
        if (mode==2) update=rnd.uniform(0,99)<(seed%3==0 ? 10 : seed%3==1 ? 50 : 90);
        if (mode==0 && seed==9) update=false;
        if (mode==0 && seed==10) update=true;
        if (mode==3 && (seed==2 || seed==5)) update=j+1!=m;
        int l=rnd.uniform(1,n),r=rnd.uniform(1,n); if (l>r) std::swap(l,r);
        if (j%8==0) { l=1; r=n; }
        if (j%8==1) l=r;
        if (j%8==2) l=1;
        if (j%8==3) r=n;
        if (j%8==4) { l=1; r=1; }
        if (j%8==5) { l=n; r=n; }
        if (mode==3 && (seed==2 || seed==5)) { l=1; r=n; }
        if (mode==3 && seed==4) {
            if (update) { l=1; r=n; }
            else { l=std::max(1,n/2-j%100); r=std::min(n,n/2+j%100); }
        }
        if (mode==0 && seed==11) {
            l=std::max(1,n/2-j%3); r=std::min(n,n/2+j%4+1);
        }
        if (update) {
            int k=delta();
            if (j%5==0) k=0;
            if (j%5==1) k=10000;
            if (j%5==2) k=-10000;
            if (mode==3 && seed==1) k=-rnd.uniform(1,10000);
            if (mode==3 && seed==2) k=10000;
            if (mode==3 && seed==5) k=-10000;
            if (mode==3 && seed==4) k=j%2 ? 10000 : -10000;
            std::printf("0 %d %d %d\n",l,r,k);
        } else std::printf("1 %d %d\n",l,r);
    }
    return 0;
}
