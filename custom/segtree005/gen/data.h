#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include "random.h"
#include "../params.h"
inline int generate(int argc, char **argv, int mode) {
    int seed=argc>1 ? std::atoi(argv[1]) : 0;
    Random rnd(20261101005ULL+mode*100ULL+seed);
    const int sizes[]={1,2,3,5,8,9,17,31,32,33,65,7};
    int n=mode==0 ? sizes[seed] : mode==1 ? rnd.uniform(1,30) : mode==2 ? rnd.uniform(1000,15000) : int(N_MAX)-(seed==5);
    int m=mode==0 ? sizes[seed] : mode==1 ? rnd.uniform(1,100) : mode==2 ? rnd.uniform(1000,15000) : int(M_MAX);
    int q=mode==0 ? 80 : mode==1 ? 200 : mode==2 ? rnd.uniform(1000,15000) : int(Q_MAX);
    int pattern=mode==0 ? seed : seed%6;
    std::printf("%d %d\n",n,m);
    for(int j=0;j<m;++j) {
        int l=rnd.uniform(1,n),r=rnd.uniform(1,n);if(l>r)std::swap(l,r);
        int k=rnd.uniform(0,2) ? (j%3==0 ? 1 : j%3==1 ? 2 : 1000000000) : rnd.uniform(1,1000000000);
        if(pattern==1){l=1;r=n;k=1000000000;}
        if(pattern==2){l=1;r=std::max(1,n/2);k=1000000000;}
        if(pattern==3){l=r=j%n+1;k=1;}
        if(pattern==4){l=r=j%2 ? std::max(1,2*n/3) : std::max(1,n/3);k=1000000000;}
        if(pattern==5){l=rnd.uniform(1,std::max(1,n/2));r=rnd.uniform(std::max(1,n/2),n);k=1000000000;}
        if(pattern==6)r=n;
        if(pattern==7)l=1;
        if(pattern==8){l=r=j%n+1;k=3;}
        if(pattern==9){l=1;r=n;k=1;}
        if(pattern==10){l=r=n/2+1;k=1000000000;}
        if(pattern==11){l=j%2 ? n/2+1 : 1;r=j%2 ? n : std::max(1,n/2);k=2;}
        std::printf("%d %d %d\n",l,r,k);
    }
    std::printf("%d\n",q);
    for(int j=0;j<q;++j) {
        int l=rnd.uniform(1,n),r=rnd.uniform(1,n);if(l>r)std::swap(l,r);
        if(j%8==0){l=1;r=n;}
        if(j%8==1)l=r;
        if(j%8==2)l=1;
        if(j%8==3)r=n;
        if(j%8==4){l=1;r=1;}
        if(j%8==5){l=n;r=n;}
        if(pattern==2 && n>1){l=rnd.uniform(n/2+1,n);r=rnd.uniform(l,n);if(j==0){l=n/2+1;r=n;}}
        std::printf("%d %d\n",l,r);
    }
    return 0;
}
