#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
inline int generate(int argc,char** argv,int mode) {
    using ll=long long;
    int seed=argc>1?std::atoi(argv[1]):0;
    Random rng(2026102903ULL+1000*mode+seed);
    int n=mode==3?int(N_MAX):mode==2?2000:mode==1?rng.uniform(8,30):seed==0?1:20;
    int c=mode==3?5:rng.uniform(1,5); if(seed==3) c=1;
    ll limit=mode==1?200:ll(LENGTH_MAX);
    std::vector<ll> length(n+1);
    std::cout<<n<<' '<<c<<'\n';
    for(int i=1;i<=n;++i) {
        int type=i<=c?1:rng.uniform(1,3),u=1,v=1;
        ll k=0;
        if(mode==3 && i>c) {
            if(seed==0) type=length[i-1]<=limit/2?2:1;
            if(seed==1) type=3;
            if(seed==2) type=2;
            if(seed==4) type=i%3==0?3:2;
            if(seed==5) type=3;
            if(seed==6) type=i%4==0?3:2;
        }
        if(type!=1) {
            u=rng.uniform(1,i-1);v=rng.uniform(1,i-1);
            if(mode==3 && seed==0) u=v=i-1;
            if(mode==3 && seed==1) u=rng.uniform(1,c);
            if(mode==3 && seed==2) {u=i-1;v=rng.uniform(1,c);}
            if(mode==3 && seed==4) {u=i-1;v=rng.uniform(1,c);}
            if(mode==3 && seed==5) u=i-1;
            if(mode==3 && seed==6) {u=i-1;v=rng.uniform(1,c);}
            if(type==2 && length[u]+length[v]>limit) type=1;
            if(type==3) {
                ll cap=length[u]?limit/length[u]:ll(LENGTH_MAX);
                k=std::min(cap,rng.uniform(0LL,9LL));
                if(mode>=2 && seed%2==1) k=cap;
                if(mode==3 && seed==4) k=0;
                if(mode==3 && seed==5) k=1;
                if(mode==3 && seed==6) k=cap;
                if(mode==0 && seed==2) k=0;
            }
        }
        if(type==1) {
            int x=mode==3 && seed==6?c-(i-1)%c:rng.uniform(1,c);
            if(i<=c) x=i;
            length[i]=1;std::cout<<"1 "<<x<<'\n';
        } else if(type==2) {
            length[i]=length[u]+length[v];std::cout<<"2 "<<u<<' '<<v<<'\n';
        } else {
            length[i]=length[u]*k;std::cout<<"3 "<<u<<' '<<k<<'\n';
        }
    }
    return 0;
}
