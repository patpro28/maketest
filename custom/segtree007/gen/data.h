#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "random.h"
#include "../params.h"
constexpr int KIND=7;
inline int generate(int argc,char **argv,int mode) {
    int seed=argc>1 ? std::atoi(argv[1]) : 0;
    Random rnd(20261102000ULL+KIND*10000ULL+mode*100ULL+seed);
    const int sizes[]={1,2,3,5,8,9,17,31,32,33,65,7};
    int n=mode==0 ? sizes[seed] : mode==1 ? rnd.uniform(1,30) : mode==2 ? rnd.uniform(1000,15000) : int(N_MAX)-(seed==5);
    int q=mode==0 ? 80 : mode==1 ? 200 : mode==2 ? rnd.uniform(1000,15000) : int(Q_MAX);
    int pattern=mode==0 ? seed : seed%6;
    const int low=VALUE_MIN,high=VALUE_MAX;
    auto value=[&]() -> int {
        const int values[]={0,1,2,3,4,6,7,10,12,15,18,30,999999937,999999929,999999893,1000000000};
        if(rnd.uniform(0,2)==0)return rnd.uniform(low,high);
        int x;do{x=values[rnd.uniform(0,15)];}while(x<low);return x;
    };
    std::vector<int>a(n);
    for(int i=0;i<n;++i) {
        int x=value();
        if(pattern==1)x=low;
        if(pattern==2)x=high;
        if(pattern==3)x=KIND==7 ? (i%2 ? 12 : 18) : (i%2 ? 1 : 2);
        if(pattern==4)x=KIND==7 ? (i%3==0 ? 999999937 : i%3==1 ? 999999929 : 999999893) : (i%3==0 ? 0 : i%3==1 ? 1 : high);
        if(pattern==5)x=KIND==7 ? (i%4==0 ? 1 : i%4==1 ? 6 : i%4==2 ? 10 : 15) : i%17;
        if(pattern==6)x=KIND==7 ? 1 : 0;
        if(pattern==7)x=KIND==7 ? (1<<(i%30)) : n-i;
        if(pattern==8)x=KIND==7 ? (i%2 ? 999999937 : 999999929) : i%2 ? 0 : high;
        if(pattern==9)x=KIND==7 ? 2520 : 7;
        if(pattern==10)x=KIND==7 ? (i%2 ? 12 : 18) : i%2 ? 3 : 2;
        if(pattern==11)x=KIND==7 ? 6 : 100;
        if(pattern==11 && KIND!=7 && (i==0 || i+1==n))x=0;
        if(mode==3 && seed==1)x=KIND==7 ? 1 : 7;
        if(mode==3 && seed==2)x=KIND==6 ? (i+1==n ? 1 : 0) : KIND==7 ? 1000000000 : 1000000000;
        a[i]=x;
    }
    std::printf("%d %d\n",n,q);
    for(int i=0;i<n;++i)std::printf("%d%c",a[i],i+1==n?'\n':' ');
    for(int j=0;j<q;++j) {
        int l=rnd.uniform(1,n),r=rnd.uniform(1,n);if(l>r)std::swap(l,r);
        if(j%8==0){l=1;r=n;}
        if(j%8==1)l=r;
        if(j%8==2)l=1;
        if(j%8==3)r=n;
        if(j%8==4){l=1;r=1;}
        if(j%8==5){l=n;r=n;}
        if(j%8==6){r=std::min(n,l+1);}
        if(mode==3 && seed==2){l=1;r=n;}
        std::printf("%d %d\n",l,r);
    }
    return 0;
}
