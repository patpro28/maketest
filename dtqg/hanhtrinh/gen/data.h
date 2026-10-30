#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <tuple>
#include <vector>
#include "random.h"
#include "../params.h"
inline int generate(int argc,char** argv,int mode) {
    using ll=long long;
    int seed=argc>1?std::atoi(argv[1]):0;
    Random rng(2026102901ULL+1000*mode+seed);
    int n=mode==3?int(N_MAX):mode==2?rng.uniform(10,30):rng.uniform(1,6);
    int s=rng.uniform(1,n),t=rng.uniform(1,n);
    ll k=mode>=2?rng.uniform(0LL,ll(K_MAX)):rng.uniform(0LL,12LL);
    std::vector<std::tuple<int,int,int>> e;
    if(mode==0) {
        if(seed==0) { n=1;s=t=1;k=0; }
        if(seed==1) { n=2;s=1;t=2;k=1; }
        if(seed==2) { n=1;s=t=1;k=K_MAX;e={{1,1,-int(VALUE_MAX)}}; }
        if(seed==3) { n=2;s=1;t=2;k=1;e={{1,2,8},{1,2,-5},{1,2,3}}; }
        if(seed==4) { n=2;s=t=1;k=3;e={{1,2,7},{2,1,4}}; }
        if(seed==5) { n=3;s=1;t=2;k=5;e={{1,2,-3},{3,3,int(VALUE_MAX)}}; }
        if(seed==6) { n=2;s=1;t=2;k=1;e={{1,2,-1}}; }
    } else {
        int m=mode==3?int(M_MAX):mode==2?rng.uniform(0,1000):rng.uniform(0,3*n*n);
        if(mode==3 && seed==1) {
            s=1;t=30;
            for(int u=1;u<=n;++u) e.emplace_back(u,u%n+1,1);
        } else for(int i=0;i<m;++i) {
            int u=rng.uniform(1,n),v=rng.uniform(1,n),w=rng.uniform(-int(VALUE_MAX),int(VALUE_MAX));
            if(mode==3 && seed==0) { u=i/n%n+1;v=i%n+1;w=VALUE_MAX; }
            if(mode==3 && seed==2) { u=i/n%n+1;v=i%n+1;w=-int(VALUE_MAX); }
            if(mode==3 && seed==3) { u=rng.uniform(1,n/2);v=rng.uniform(1,n/2);s=1;t=n; }
            if(mode==3 && seed==4) { u=1;v=(i%2)+1; }
            e.emplace_back(u,v,w);
        }
        if(mode==3) {
            k=seed==5?0:seed==6?(1LL<<39)+12345:ll(K_MAX)-seed;
            if(seed==0 || seed==2) k=K_MAX;
            if(seed==5) {s=1;t=2;}
        }
    }
    std::cout<<n<<' '<<e.size()<<' '<<s<<' '<<t<<' '<<k<<'\n';
    for(auto [u,v,w]:e) std::cout<<u<<' '<<v<<' '<<w<<'\n';
    return 0;
}
