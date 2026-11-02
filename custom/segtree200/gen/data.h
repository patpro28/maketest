#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "random.h"
#include "../params.h"
constexpr int KIND = 200;
inline int generate(int argc, char **argv, int mode) {
    int seed=argc>1 ? std::atoi(argv[1]) : 0;
    Random rnd(20261101200ULL + (KIND-200)*10000ULL + mode*100ULL + seed);
    const int sizes[]={1,2,3,5,8,9,17,31,32,33,65,7};
    int n=mode==0 ? sizes[seed] : mode==1 ? rnd.uniform(1,30) : mode==2 ? rnd.uniform(1000,20000) : int(N_MAX)-(seed==5);
    int q=mode==0 ? 90 : mode==1 ? 250 : mode==2 ? rnd.uniform(1000,20000) : int(Q_MAX);
    int pattern=mode==0 ? seed : seed%6;
    const int low=VALUE_MIN,high=VALUE_MAX;
    auto value=[&]() -> int {
        if (KIND==205) return rnd.uniform(1,3);
        const int special[]={-1000000000,-7,-1,0,1,2,3,6,12,18,30,999999937,999999999,1000000000};
        if (rnd.uniform(0,2)==0) return rnd.uniform(low,high);
        int x; do { x=special[rnd.uniform(0,13)]; } while (x<low || x>high); return x;
    };
    std::vector<int> a(n);
    for (int i=0; i<n; ++i) {
        int x=value();
        if (pattern==1) x=low;
        if (pattern==2) x=high;
        if (pattern==3) x=KIND==205 ? 1 : std::clamp(6,low,high);
        if (pattern==4) x=i%2 ? low : high;
        if (pattern==5) x=KIND==205 ? i%3+1 : std::clamp(i%17,low,high);
        if (pattern==6) x=std::clamp(1,low,high);
        if (pattern==7) x=KIND==205 ? i%3+1 : std::clamp(n-i,low,high);
        if (mode==3 && seed==1) x=KIND==200 ? 0 : KIND==201 ? 9 : KIND==202 ? 0 : KIND==203 || KIND==204 ? 1000000000 : 1;
        if (mode==3 && seed==2) x=KIND==200 ? 1000000000 : KIND==201 || KIND==202 ? 0 : KIND==203 || KIND==204 ? 1000000000 : 1;
        a[i]=x;
    }
    std::printf("%d %d\n",n,q);
    for (int i=0; i<n; ++i) std::printf("%d%c",a[i],i+1==n?'\n':' ');
    for (int j=0; j<q; ++j) {
        bool update=j%3==1;
        if (mode==2) update=rnd.uniform(0,99)<(seed%3==0 ? 10 : seed%3==1 ? 50 : 90);
        if (mode==0 && seed==9) update=false;
        if (mode==0 && seed==10) update=true;
        if (mode==3 && seed==1) update=j==0;
        if (mode==3 && (seed==2 || seed==5)) update=j+1!=q;
        if (update) {
            int l=rnd.uniform(1,n),r=rnd.uniform(1,n); if (l>r) std::swap(l,r);
            if (j%8==0) { l=1;r=n; }
            if (j%8==1) l=r;
            if (j%8==2) l=1;
            if (j%8==3) r=n;
            if (j%8==4) { l=1;r=1; }
            if (j%8==5) { l=n;r=n; }
            if (mode==3 && (seed==1 || seed==2)) { l=1;r=n; }
            if (mode==3 && seed==4) {
                l=1;r=n;
                if (j%2) { l=std::max(1,n/2-j%101);r=std::min(n,n/2+j%103); }
            }
            if (mode==0 && seed==11) { l=1;r=n;if (j%2) { l=std::max(1,n/2);r=std::min(n,n/2+1); } }
            int x=value();
            if (j%5==0) x=low;
            if (j%5==1) x=high;
            if (j%5==2) x=std::clamp(1,low,high);
            if (mode==3 && seed==1) x=KIND==200 ? 1000000000 : KIND==201 ? 0 : KIND==202 || KIND==203 ? 777 : KIND==204 ? 6 : 1;
            if (mode==3 && seed==2) x=KIND==200 ? 1000000000 : KIND==201 || KIND==202 || KIND==203 ? (j%2 ? 1000000000 : 0) : KIND==204 ? (j%2 ? 2 : 3) : j%2+1;
            if (KIND==205) {
                int y=rnd.uniform(1,3);
                if (j%4==0) y=x;
                if (mode==3 && seed==1) y=2;
                if (mode==3 && seed==2) y=x+1;
                if (mode==3 && seed==4) { x=j%2 ? 1 : 2;y=x+1; }
                std::printf("1 %d %d %d %d\n",l,r,x,y);
            } else std::printf("1 %d %d %d\n",l,r,x);
        } else {
            int p=rnd.uniform(1,n);
            if (j%5==0) p=1;
            if (j%5==1) p=n;
            if (j%5==2) p=std::max(1,n/2);
            if (mode==3 && (seed==1 || seed==2)) p=n;
            std::printf("2 %d\n",p);
        }
    }
    return 0;
}
