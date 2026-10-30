#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <tuple>
#include <vector>
#include "random.h"
#include "../params.h"
inline int generate(int argc,char** argv,int mode){
    const int kind=5;
    int seed=argc>1?std::atoi(argv[1]):0;
    Random rng(2026103000ULL+100000*kind+1000*mode+seed);
    const int sizes[]={1,2,3,4,5,8,12};
    int n=mode==3?int(N_MAX):mode==2?3000:mode==1?rng.uniform(1,18):sizes[seed];
    int q=mode==3?200000:mode==2?4000:mode==1?40:25;
    std::vector<int> label(n+1),parent(n+1),depth(n+1),size(n+1,1),color(n+1),k(n+1),a(n+1),w(n+1);
    std::iota(label.begin(),label.end(),0);
    if(seed%2 && n>2)rng.shuffle(label.begin()+2,label.end());
    std::vector<std::tuple<int,int,char>>edges;
    for(int v=2;v<=n;++v){
        int p=rng.uniform(1,v-1);
        if(seed==0)p=v-1;
        if(seed==1)p=1;
        if(seed==2 || seed==7)p=v/2;
        if(seed==4)p=v<=n/2?v-1:std::max(1,n/2);
        if(seed==5)p=v<=n/2?v-1:std::max(1,v-n/2);
        if(seed==6)p=v<=5?1:v-4;
        parent[v]=p;depth[v]=depth[p]+1;
        char c=char('a'+rng.uniform(0,9));
        if(seed==0 || seed==1)c='a';
        if(seed==2)c=char('a'+depth[v]%3);
        if(seed==4)c=char('a'+rng.uniform(0,1));
        if(seed==5)c='j';
        if(seed==6)c=char('a'+v%10);
        int x=label[p],y=label[v];if(rng.uniform_bool())std::swap(x,y);
        edges.emplace_back(x,y,c);
    }
    for(int v=n;v>=2;--v)size[parent[v]]+=size[v];
    for(int i=1;i<=n;++i){
        int u=label[i];
        color[u]=rng.uniform(1,1000000000);
        if(seed==0)color[u]=i;
        if(seed==1)color[u]=1000000000;
        if(seed==2 || seed==4)color[u]=i%3+1;
        if(seed==5)color[u]=i%7==0?999999937:1;
        if(seed==6)color[u]=1000000000-i;
        if(seed==7)color[u]=rng.uniform(1,1000);
        k[u]=rng.uniform(0,std::min(n,12));
        if(seed==0)k[u]=n-i;
        if(seed==1)k[u]=i==1?std::min(n,2):0;
        if(seed==2)k[u]=i%5;
        if(seed==4 || seed==5)k[u]=n;
        if(seed==6)k[u]=rng.uniform(0,n);
        if(seed==7)k[u]=rng.uniform(0,std::min(n,32));
        if(mode==0 && seed==2)k[u]=0;
        k[u]=std::min(k[u],n);
        a[u]=rng.uniform(0,1000000000);w[u]=rng.uniform(1,1000);
        if(seed==0){a[u]=i-1;w[u]=1;}
        if(seed==1){a[u]=i==1?0:1000000000;w[u]=i==1?1000:1;}
        if(seed==2){a[u]=i%2?0:1000000000;w[u]=i%3?1:1000;}
        if(seed==4){a[u]=42;w[u]=1000;}
        if(seed==5){a[u]=1000000000-i*100;w[u]=1000;}
        if(seed==6)a[u]=i>n*3/4?0:1000000000;
        if(seed==7){a[u]=rng.uniform(0,5)*100000000;w[u]=rng.uniform(1,2);}
    }
    rng.shuffle(edges.begin(),edges.end());
    std::cout<<n;if(kind==2)std::cout<<' '<<q;std::cout<<'\n';
    if(kind==1 || kind==2){for(int u=1;u<=n;++u)std::cout<<(u>1?" ":"")<<color[u];std::cout<<'\n';}
    if(kind==3 || kind==5){for(int u=1;u<=n;++u)std::cout<<(u>1?" ":"")<<k[u];std::cout<<'\n';}
    if(kind==4)for(int u=1;u<=n;++u)std::cout<<a[u]<<' '<<w[u]<<'\n';
    for(auto [u,v,c]:edges){std::cout<<u<<' '<<v;if(kind==5)std::cout<<' '<<c;std::cout<<'\n';}
    if(kind==2)for(int i=0;i<q;++i){
        int original=i%3==0?1:rng.uniform(1,i%3==1?std::min(n,512):n);
        int take=rng.uniform(0,std::min(32,size[original]));
        if(i%7==0)take=0;if(i%7==1)take=n;if(i%7==2)take=1;
        if(i%7==3)take=size[original]/2;
        std::cout<<label[original]<<' '<<take<<'\n';
    }
    return 0;
}
