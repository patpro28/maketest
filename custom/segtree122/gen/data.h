#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "random.h"
#include "../params.h"
constexpr int KIND = 122;
inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rnd(20261021ULL + 9000000ULL + KIND * 10000ULL + mode * 100ULL + seed);
    const int sizes[] = {1,2,3,5,8,9,17,31,32,33,65,7};
    int n = mode == 0 ? sizes[seed] : mode == 1 ? rnd.uniform(1,30) : mode == 2 ? rnd.uniform(1000,20000) : int(N_MAX) - (seed == 5);
    if (KIND == 132) n = std::max(3,n);
    int q = mode == 0 ? 60 : mode == 1 ? 200 : mode == 2 ? rnd.uniform(1000,20000) : int(Q_MAX);
    int pattern = mode == 0 ? seed : seed % 6;
    const long long big = 1000000000000000000LL;
    if (KIND == 122) {
        std::printf("%d\n",n);
        for (int i = 1; i <= n; ++i) {
            int e = rnd.uniform(0,i-1);
            if (pattern == 1) e = 0;
            if (pattern == 2) e = i-1;
            if (pattern == 3) e = (i-1)/2;
            if (pattern == 4) e = i%2 ? 0 : i-1;
            if (pattern == 5) e = std::max(0,i-2);
            std::printf("%d%c",e,i==n?'\n':' ');
        }
        return 0;
    }
    int c = n, initial = n;
    if (KIND == 193 && mode == 0 && seed == 0) initial = 0;
    if (KIND == 193) std::printf("%d %d %d\n",c,initial,q);
    else std::printf("%d %d\n",n,q);
    const int low = KIND == 162 || KIND == 173 || KIND == 182 ? 1 : 0;
    const int high = KIND == 102 ? 1048575 : KIND == 112 || KIND == 192 ? 1 : KIND == 193 ? c : 1000000000;
    auto value = [&]() -> int {
        if (rnd.uniform(0,2) == 0) return rnd.uniform(low,high);
        if (KIND == 102) return rnd.uniform(0,1) ? 1 << rnd.uniform(0,19) : rnd.uniform(0,1) ? 0 : 1048575;
        const int specials[] = {0,1,2,3,4,5,6,7,12,18,30,999999893,999999929,999999937,1000000000};
        int x; do { x=specials[rnd.uniform(0,14)]; } while (x<low || x>high);
        return x;
    };
    std::vector<long long> a(n);
    long long total=0;
    for (int i=0; i<n; ++i) {
        long long x=value();
        if (pattern==1) x=low;
        if (pattern==2) x=high;
        if (pattern==3) x=std::clamp(6,low,high);
        if (pattern==4 || pattern==11) x=i%2?low:high;
        if (pattern==5) x=std::clamp(i%7,low,high);
        if (pattern==6) x=std::clamp(7,low,high);
        if (pattern==7) x=std::clamp(n-i,low,high);
        if (KIND==174) x=pattern==1?0:pattern==2?i%26:pattern==3?25:pattern==4?i%2:mode==1?rnd.uniform(0,2):rnd.uniform(0,25);
        if (mode==3 && seed==1) {
            if (KIND==102) x=i+1==n?1<<19:0;
            if (KIND==112) x=i+1==n;
            if (KIND==132) x=i+1==n/3 || i+1==2*n/3 || i+1==n;
            if (KIND==162) x=i+1==n?5:6;
            if (KIND==173) x=6;
            if (KIND==174) x=i+1==n?25:0;
            if (KIND==182) x=i+1==n?5:6;
            if (KIND==192) x=i+1==n?0:1;
            if (KIND==193) x=c;
        }
        if (mode==3 && seed==3 && KIND==132) x=0;
        if (mode==3 && seed==3 && KIND==192) x=0;
        a[i]=x;total+=x;
        if (KIND==174) std::putchar('a'+int(x));
        else if (i<initial) std::printf("%lld%c",x,i+1==initial?'\n':' ');
    }
    if (KIND==174 || (KIND==193 && initial==0)) std::putchar('\n');
    for (int j=0; j<q; ++j) {
        int pos=rnd.uniform(0,n-1);
        if (j%7==0) pos=0;
        if (j%7==1) pos=n-1;
        if (j%7==2) pos=n/2;
        bool update=j%3==1;
        if (mode==2) update=rnd.uniform(0,99)<(seed%3==0?10:seed%3==1?50:90);
        if (mode==0 && seed==9) update=false;
        if (mode==0 && seed==10) update=true;
        if (mode==3 && seed==1) update=false;
        if (mode==3 && seed==5) update=j+1!=q;
        if (mode==3 && seed==3 && (KIND==132 || KIND==192)) update=false;
        if (update) {
            if (KIND==112) { a[pos]=1-a[pos]; std::printf("1 %d\n",pos+1);continue; }
            if (KIND==192) { a[pos]=0;std::printf("2 %d\n",pos+1);continue; }
            if (KIND==193) { std::printf("1 %d\n",value());continue; }
            long long x=KIND==174?rnd.uniform(0,25):value();
            if (j%5==1) x=a[pos];
            if (j%5==2) x=low;
            if (j%5==3) x=KIND==174?25:high;
            total+=x-a[pos];a[pos]=x;
            if (KIND==174) std::printf("1 %d %c\n",pos+1,'a'+int(x));
            else std::printf("1 %d %lld\n",pos+1,x);
            continue;
        }
        int l=rnd.uniform(1,n), r=rnd.uniform(1,n);
        if (l>r) std::swap(l,r);
        if (j%6==0) { l=1;r=n; }
        if (j%6==1) l=r;
        if (j%6==2) l=1;
        if (j%6==3) r=n;
        if (mode==3 && seed==1) { l=1;r=n; }
        if (KIND==102) {
            int mask=j%4==0?1048575:j%4==1?1<<rnd.uniform(0,19):j%4==2?3:rnd.uniform(1,1048575);
            if (mode==3 && seed==1) mask=1<<19;
            std::printf("2 %d\n",mask);
        }
        if (KIND==112) std::printf("2 %d\n",l);
        if (KIND==132) std::printf("2\n");
        if (KIND==162) {
            long long d=j%5==0?1:j%5==1?a[l-1]:j%5==2?3:j%5==3?1000000000:value();
            if (mode==3 && seed==1) d=3;
            std::printf("2 %d %d %lld\n",l,r,d);
        }
        if (KIND==173) {
            long long bound=j%6==0?1:j%6==1?a[l-1]:j%6==2?std::max(1LL,a[l-1]-1):j%6==3?big:j%6==4?12:rnd.uniform(1LL,big);
            if (mode==3 && seed==1) bound=6;
            std::printf("2 %d %lld\n",l,bound);
        }
        if (KIND==174) {
            int limit=j%4==0?1:j%4==1?26:j%4==2?2:rnd.uniform(1,26);
            if (mode==3 && seed==1) limit=1;
            std::printf("2 %d %d\n",l,limit);
        }
        if (KIND==182) {
            long long target=j%5==0?1:j%5==1?big:j%5==2?total:j%5==3?a[l-1]:total+1;
            long long g=j%4==0?1:j%4==1?1000000000:j%4==2?a[l-1]:rnd.uniform(1,1000000000);
            if (mode==3 && seed==1) { target=1;g=1; }
            std::printf("2 %d %lld %lld\n",l,target,g);
        }
        if (KIND==192) std::printf("1 %d\n",mode==3 && seed==3?n:l);
        if (KIND==193) {
            int w=j%4==0?1:j%4==1?c:j%4==2?std::max(1,c/2):rnd.uniform(1,c);
            if (mode==3 && seed==1) w=1;
            std::printf("2 %d\n",w);
        }
    }
    return 0;
}
