#pragma once
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
#include "../params.h"
inline int generate_stages(int argc,char**argv){
    int seed=argc>1?std::atoi(argv[1]):0;
    int m=seed<2?int(M_MAX):seed<4?3:10;
    int A=seed<2?1000:1000000000,B=A;
    std::vector<std::pair<int,int>>v(m);
    for(int i=0;i<m;++i)v[i]={i%5+1,5-i%5};
    if(seed==1){A=997;B=1000;}
    if(seed==2)v={{1,1},{2,3},{5,2}};
    if(seed==3)v.assign(3,{1,1});
    if(seed==4){const std::pair<int,int>pattern[]={{5,1},{1,5},{5,4},{4,5},{5,5}};for(int i=0;i<m;++i)v[i]=pattern[i%5];A=999999937;B=999999929;}
    if(seed==5){A=(1<<29)-1;B=(1<<29)+1;}
    std::cout<<m<<' '<<A<<' '<<B<<'\n';for(auto [a,b]:v)std::cout<<a<<' '<<b<<'\n';
    return 0;
}
