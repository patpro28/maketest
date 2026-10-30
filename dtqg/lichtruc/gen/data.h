#pragma once
#include <cstdlib>
#include <iostream>
#include "random.h"
#include "../params.h"
inline int generate(int argc,char** argv,int mode) {
    using ll=long long;
    int seed=argc>1?std::atoi(argv[1]):0;
    Random rng(2026102902ULL+1000*mode+seed);
    int p=mode==3?int(P_MAX):mode==2?2000:rng.uniform(1,6);
    ll d=mode>=2?rng.uniform(0LL,ll(D_MAX)):rng.uniform(0LL,30LL);
    if(mode==0) { const ll ds[]={0,1,2,3,5,13,1000000000000LL}; d=ds[seed];p=seed<5?1:seed==5?5:2; }
    if(mode==3) {
        const ll ds[]={1000000000000LL,999999999999LL,0,1000000000000LL,999999999999LL,100000,1000000000000LL,99999};
        d=ds[seed]; if(seed==3) p=99991;
    }
    std::cout<<p<<' '<<d<<'\n';
    for(int i=0;i<p;++i) {
        for(int j=0;j<3;++j) {
            int w=rng.uniform(-int(VALUE_MAX),int(VALUE_MAX));
            if(mode==0) w=seed==0?-7:seed==1?j-1:seed==2?10:seed==3?(j==0?100:-100):seed==4?(j==0?5:1):seed==6?(j==(i%3)?999999:0):w;
            if(mode==3 && seed==0) w=VALUE_MAX;
            if(mode==3 && seed==1) w=j==0?int(VALUE_MAX):-int(VALUE_MAX);
            if(mode==3 && seed==2) w=0;
            if(mode==3 && seed==4) w=j==i%3?int(VALUE_MAX):0;
            if(mode==3 && seed==6) w=-rng.uniform(1,int(VALUE_MAX));
            std::cout<<(j?" ":"")<<w;
        }
        std::cout<<'\n';
    }
    return 0;
}
