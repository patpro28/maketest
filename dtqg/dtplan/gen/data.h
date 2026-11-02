#pragma once
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
#include "random.h"
#include "../params.h"
inline int generate(int argc,char** argv,int mode){
    int seed=argc>1?std::atoi(argv[1]):0;Random rng(2026110100ULL+1000*mode+seed);
    int m=mode==3?int(M_MAX):rng.uniform(1,int(M_MAX)),A=mode<=1?rng.uniform(1,30):rng.uniform(1,1000000000),B=mode<=1?rng.uniform(1,30):rng.uniform(1,1000000000);
    std::vector<std::pair<int,int>>v(m);
    for(auto& [a,b]:v){a=rng.uniform(1,5);b=rng.uniform(1,5);}
    if(mode==0){
        if(seed==0){v={{1,1}};A=B=1;}
        if(seed==1){v={{2,3}};A=4;B=6;}
        if(seed==2){v={{2,3}};A=4;B=5;}
        if(seed==3){v={{1,1},{1,1}};A=B=2;}
        if(seed==4){v={{5,5},{5,5}};A=B=1;}
        if(seed==5){v={{1,5},{5,1}};A=1;B=1;}
        if(seed==6){v={{2,2},{4,4}};A=B=7;}
        if(seed==7){v={{1,1},{2,2},{3,3}};A=12;B=13;}
        if(seed==8){v={{5,1},{1,5}};A=6;B=6;}
        if(seed==9){v.assign(M_MAX,{1,1});A=B=30;}
    }
    if(mode==2 && seed%2==0){
        A=B=0;
        for(auto [a,b]:v){int x=rng.uniform(0,1000000);A+=a*x;B+=b*x;}
        if(!A)A=B=1;
    }
    if(mode==3){
        A=B=1000000000;
        if(seed==0)v.assign(M_MAX,{1,1});
        if(seed==1)v.assign(M_MAX,{5,5});
        if(seed==2){v.assign(M_MAX,{2,4});A=500000000;B=1000000000;}
        if(seed==3){v.assign(M_MAX,{2,4});A=500000001;B=1000000000;}
        if(seed==4)for(int i=0;i<m;++i)v[i]={i%5+1,i%5+1};
        if(seed==5){for(int i=0;i<m;++i)v[i]={i%5+1,5-i%5};A=999999997;B=999999999;}
        if(seed==6){v.assign(M_MAX,{1,1});B=999999999;}
        if(seed==7){A=1;B=1000000000;}
        if(seed==8){A=1000000000;B=1;}
        if(seed==9){const std::pair<int,int>pattern[]={{1,5},{5,1},{2,4},{4,2},{3,3},{1,4},{4,1},{2,5},{5,2},{5,5}};for(int i=0;i<m;++i)v[i]=pattern[i%10];A=999999937;B=999999929;}
        if(seed==10){v.assign(M_MAX,{5,5});A=B=999999999;}
        if(seed==11){const std::pair<int,int>pattern[]={{1,1},{1,2},{1,3},{1,4},{1,5},{5,1},{5,2},{5,3},{5,4},{5,5}};for(int i=0;i<m;++i)v[i]=pattern[i%10];A=(1<<29)-1;B=(1<<29)+1;}
    }
    std::cout<<v.size()<<' '<<A<<' '<<B<<'\n';
    for(auto [a,b]:v)std::cout<<a<<' '<<b<<'\n';
    return 0;
}
