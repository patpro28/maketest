#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include "random.h"
#include "../params.h"
inline int generate(int argc,char** argv,int mode) {
    int seed=argc>1?std::atoi(argv[1]):0;
    Random rng(2026102904ULL+1000*mode+seed);
    const int sizes[]={1,2,3,4,5,8,11};
    int n=mode==3?int(N_MAX):mode==2?1000:mode==1?rng.uniform(1,16):sizes[seed];
    int q=mode==3?int(Q_MAX):mode==2?1500:mode==1?rng.uniform(1,40):15;
    std::cout<<n<<' '<<q<<'\n';
    for(int i=0;i<n;++i) {
        int w=rng.uniform(-int(VALUE_MAX),int(VALUE_MAX));
        if(mode==0) w=seed==0?-7:seed==1?9:seed==2?0:seed==3?int(VALUE_MAX):i%2?100:-3;
        if(mode==3 && seed==0) w=VALUE_MAX;
        if(mode==3 && seed==3) w=i%2?int(VALUE_MAX):-int(VALUE_MAX);
        if(mode==3 && seed==4) w=0;
        if(mode==3 && seed==6) w=n-i;
        std::cout<<(i?" ":"")<<w;
    }
    std::cout<<'\n';
    for(int i=0;i<q;++i) {
        bool query=i==0 || i==q-1 || rng.uniform_bool();
        if(mode==3 && seed==0) query=true;
        if(mode==3 && seed==1) query=(i%2==1 || i==q-1);
        if(mode==3 && seed==5) query=i==q-1;
        if(query) {
            int l=rng.uniform(1,n),r=rng.uniform(1,n);if(l>r) std::swap(l,r);
            if(i==0 || i==q-1 || (mode==3 && (seed==0 || seed==1))) {l=1;r=n;}
            if(mode==3 && seed==2) r=std::min(n,l+2);
            std::cout<<"2 "<<l<<' '<<r<<'\n';
        } else {
            int p=rng.uniform(1,n),x=rng.uniform(-int(VALUE_MAX),int(VALUE_MAX));
            if(mode==3 && seed==1) {p=n/2;x=i%4==0?int(VALUE_MAX):-int(VALUE_MAX);}
            if(mode==3 && seed==4) x=(i%3-1)*int(VALUE_MAX);
            std::cout<<"1 "<<p<<' '<<x<<'\n';
        }
    }
    return 0;
}
