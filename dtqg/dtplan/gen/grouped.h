#pragma once
#include <string>
#include "data.h"
#include "stress.h"
#include "stages.h"

inline int replay(int mode,int seed){
    std::string text=std::to_string(seed),program="generator";
    char* argv[]={program.data(),text.data()};
    if(mode==4)return generate_stress(2,argv);
    if(mode==5)return generate_stages(2,argv);
    return generate(2,argv,mode);
}

inline int additional(int group,int seed){
    Random rng(2026110200ULL+group*100+seed);
    int m=group==1?20:group==2?seed%3+1:group==3?seed%7+4:seed%10+11;
    int A=group==1?1000:rng.uniform(1001,1000000000);
    int B=group==1?1000:rng.uniform(1001,1000000000);
    std::vector<std::pair<int,int>>v(m);
    for(auto& [a,b]:v){a=rng.uniform(1,5);b=rng.uniform(1,5);}
    if(group==1){
        if(seed==0)v.assign(m,{1,1});
        if(seed==1){for(int i=0;i<m;++i)v[i]={i%2?5:1,i%2?1:5};A=999;B=1000;}
        if(seed==2){A=1000;B=997;}
    }else if(group==2){
        if(seed==0){v={{1,1}};A=B=1000000000;}
        if(seed==1){v={{2,3},{4,5}};A=999999999;B=1000000000;}
        if(seed==2){v={{1,1},{2,3},{5,2}};A=666666666;B=777777777;}
        if(seed==3){v={{5,5}};A=B=999999999;}
        if(seed==4){v={{1,5},{5,1}};A=B=999999996;}
        if(seed==5){v.assign(3,{1,1});A=B=(1<<29)+1;}
        if(seed==6){v={{3,5}};A=600000000;B=1000000000;}
        if(seed==7){v={{5,1},{1,5}};A=1000000000;B=1001;}
    }else if(group==3){
        if(seed==0){v.assign(m,{1,1});A=B=1000000000;}
        if(seed==1){v.assign(m,{5,5});A=B=1000000000;}
        if(seed==2){for(int i=0;i<m;++i)v[i]={i%2?5:1,i%2?1:5};A=999999997;B=999999999;}
        if(seed==3){for(int i=0;i<m;++i)v[i]={i%5+1,i%5+1};A=B=(1<<29)-1;}
        if(seed==4){A=1000000000;B=1001;}
        if(seed==5){A=B=(1<<29)+1;}
        if(seed==6){A=999999937;B=999999929;}
    }else{
        if(seed%4==0){
            for(int i=0;i<m;++i){int a=5,b=i%5+1;if(i%2)std::swap(a,b);v[i]={a,b};}
            A=999999937;B=999999929;
        }
        if(seed%4==1){A=B=0;for(auto [a,b]:v){int x=rng.uniform(1,1000000);A+=a*x;B+=b*x;}}
        if(seed%4==2){v.assign(m,{seed%5+1,seed%5+1});A=B=1000000000;}
        if(seed==11){A=1001;B=1000000000;}
        if(seed==12){A=(1<<29)-1;B=(1<<29)+1;}
    }
    std::cout<<v.size()<<' '<<A<<' '<<B<<'\n';
    for(auto [a,b]:v)std::cout<<a<<' '<<b<<'\n';
    return 0;
}

inline int generate_group(int argc,char**argv,int group){
    const int seed=argc>1?std::atoi(argv[1]):0;
    if(group==1){
        if(seed<10)return replay(0,seed);
        if(seed<20)return replay(1,seed-10);
        if(seed<22)return replay(5,seed-20);
        return additional(group,seed-22);
    }
    if(group==2){
        if(seed<2)return replay(5,seed+2);
        return additional(group,seed-2);
    }
    if(group==3){
        if(seed==0)return replay(2,3);
        if(seed<3)return replay(5,seed+3);
        return additional(group,seed-3);
    }
    if(seed<12)return replay(3,seed);
    if(seed<19){const int seeds[]={0,1,2,4,5,6,7};return replay(2,seeds[seed-12]);}
    if(seed<27)return replay(4,seed-19);
    return additional(group,seed-27);
}
