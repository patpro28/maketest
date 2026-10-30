#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
#include "random.h"
#include "../params.h"
inline int generate(int argc,char** argv,int mode) {
    int seed=argc>1?std::atoi(argv[1]):0;
    Random rng(2026102905ULL+1000*mode+seed);
    const int sizes[]={1,2,3,4,6,9,12};
    int n=mode==3?int(N_MAX):mode==2?2000:mode==1?rng.uniform(1,12):sizes[seed];
    int q=mode==3?int(Q_MAX):mode==2?1500:mode==1?rng.uniform(1,30):20;
    std::vector<int> label(n+1);std::iota(label.begin(),label.end(),0);
    if(seed%2) rng.shuffle(label.begin()+1,label.end());
    std::vector<int> w(n+1);
    for(int i=1;i<=n;++i) {
        w[label[i]]=rng.uniform(-int(VALUE_MAX),int(VALUE_MAX));
        if(seed==0) w[label[i]]=VALUE_MAX;
        if(seed==2) w[label[i]]=0;
        if(seed==4) w[label[i]]=-int(VALUE_MAX);
    }
    std::vector<std::pair<int,int>> edges;
    for(int v=2;v<=n;++v) {
        int p=rng.uniform(1,v-1);
        if(seed==0) p=v-1;
        if(seed==1) p=1;
        if(seed==2 || seed==7) p=v/2;
        if(seed==4) p=v<=n/2?v-1:n/2;
        if(seed==5) p=v<=n/2?v-1:std::max(1,v-n/2);
        if(seed==6) p=v<=5?1:v-4;
        int a=label[p],b=label[v];if(rng.uniform_bool())std::swap(a,b);
        edges.emplace_back(a,b);
    }
    rng.shuffle(edges.begin(),edges.end());
    std::cout<<n<<' '<<q<<'\n';
    for(int i=1;i<=n;++i) std::cout<<(i>1?" ":"")<<w[i];
    std::cout<<'\n';
    for(auto [u,v]:edges) std::cout<<u<<' '<<v<<'\n';
    for(int i=0;i<q;++i) {
        int u=label[rng.uniform(1,n)],x=rng.uniform(-int(VALUE_MAX),int(VALUE_MAX));
        if(seed==0) {u=label[n];x=i%2?0:int(VALUE_MAX);}
        if(seed==1 && i%2==0) u=label[1];
        if(seed==2) x=i%3==0?int(VALUE_MAX):0;
        if(seed==4) {u=label[n/2+1];x=i%2?int(VALUE_MAX):-int(VALUE_MAX);}
        if(seed==6) u=label[std::max(1,n-i%4)];
        std::cout<<u<<' '<<x<<'\n';
    }
    return 0;
}
