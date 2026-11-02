#pragma once
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
#include "random.h"
#include "../params.h"
inline int generate_stress(int argc,char**argv){
    int seed=argc>1?std::atoi(argv[1]):0;Random rng(2026110103ULL+seed);
    std::vector<std::pair<int,int>>v;
    if(seed<=2){
        for(int i=0;i<int(M_MAX);++i){int a=5,b=i%5+1;if(i%2)std::swap(a,b);v.emplace_back(a,b);}
        if(seed==1)for(auto& [a,b]:v)std::swap(a,b);
        if(seed==2)rng.shuffle(v.begin(),v.end());
    }else if(seed==3){
        const std::pair<int,int>pattern[]={{5,1},{1,5},{5,4},{4,5},{5,5},{4,4},{4,1},{1,4}};
        for(int i=0;i<int(M_MAX);++i)v.push_back(pattern[i%8]);
    }else{
        const int sizes[]={20,20,20,20,11,15,19,20};
        for(int i=0;i<sizes[seed];++i)v.emplace_back(rng.uniform(1,5),rng.uniform(1,5));
    }
    int A=999999937,B=999999929;
    if(seed==1)std::swap(A,B);
    std::cout<<v.size()<<' '<<A<<' '<<B<<'\n';for(auto [a,b]:v)std::cout<<a<<' '<<b<<'\n';
    return 0;
}
