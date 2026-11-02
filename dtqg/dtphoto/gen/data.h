#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>
#include "random.h"
#include "../params.h"
inline void print_row(const std::vector<int>& row){
    for(int i=0;i<int(row.size());++i)std::cout<<(i?" ":"")<<row[i];std::cout<<'\n';
}
inline int generate(int argc,char**argv,int mode){
    int seed=argc>1?std::atoi(argv[1]):0;
    if(mode==5){seed+=7;mode=0;}
    Random rng(2026110200ULL+1000*mode+seed);
    const int sizes[]={1,2,3,4,5,6,8,9,10,30,100,200};
    int n=mode==4?(seed==7?7:int(BRUTE_N_MAX)):mode==0?sizes[seed]:mode==1?rng.uniform(1,35):mode==2?3000:int(N_MAX);
    std::vector<int>standard(n),owner(n+1);std::iota(standard.begin(),standard.end(),1);
    if(seed==1)std::reverse(standard.begin(),standard.end());
    if(seed==2 || seed==6 || seed==7 || seed==8 || seed==10 || seed==11)rng.shuffle(standard.begin(),standard.end());
    if(seed==3){int lo=1,hi=n;for(int i=0;i<n;++i)standard[i]=i%2?lo++:hi--;}
    if(seed==4 || seed==5)std::rotate(standard.begin(),standard.begin()+n/3,standard.end());
    if(seed==9)for(int l=0;l<n;l+=37)std::reverse(standard.begin()+l,standard.begin()+std::min(n,l+37));
    for(int i=0;i<n;++i){
        int group=rng.uniform(0,5);
        if(seed==0)group=0;
        if(seed==1)group=1;
        if(seed==2)group=i<n/3?1:i<2*n/3?2:0;
        if(seed==3 || seed==4 || seed==8 || seed==9 || seed==10)group=i%5+1;
        if(seed==5)group=i<5?i+1:0;
        if(seed==6)group=5;
        owner[standard[i]]=group;
    }
    std::vector<std::vector<int>>photos;
    for(int k=1;k<=5;++k){
        std::vector<int>kept,moved;
        for(int x:standard)(owner[x]==k?moved:kept).push_back(x);
        if(seed==1 || seed==3 || seed==6 || seed==8 || seed==9)std::reverse(moved.begin(),moved.end());
        else rng.shuffle(moved.begin(),moved.end());
        std::vector<std::pair<int,int>>placement;
        for(int x:moved){
            int gap=rng.uniform(0,int(kept.size()));
            if(seed==2)gap=k==1?int(kept.size()):0;
            if(seed==3 || seed==5)gap=k%2?int(kept.size()):0;
            if(seed==8)gap=k<=3?0:int(kept.size());
            if(seed==9)gap=int(kept.size())/2;
            placement.push_back({gap,x});
        }
        std::stable_sort(placement.begin(),placement.end(),[](auto a,auto b){return a.first<b.first;});
        std::vector<int>row;row.reserve(n);int p=0;
        for(int gap=0;gap<=int(kept.size());++gap){
            while(p<int(placement.size()) && placement[p].first==gap)row.push_back(placement[p++].second);
            if(gap<int(kept.size()))row.push_back(kept[gap]);
        }
        photos.push_back(std::move(row));
    }
    std::cout<<n<<'\n';
    if(argc>2 && std::string(argv[2])=="witness"){
        print_row(standard);print_row(std::vector<int>(owner.begin()+1,owner.end()));
    }else for(const auto& row:photos)print_row(row);
    return 0;
}
