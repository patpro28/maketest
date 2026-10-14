#pragma once
#include <algorithm>
#include <array>
#include <cstdio>
#include <functional>
#include <map>
#include <numeric>
#include <queue>
#include <string>
#include <utility>
#include <vector>
using namespace std;
#include <cstdlib>
#include "random.h"
inline void emit(const vector<int> &a) {
    for(int i=0;i<int(a.size());++i) printf("%s%d",i ? " " : "",a[i]);
    puts("");
}
inline int generate(int argc,char **argv,int mode) {
    int seed=argc>1 ? atoi(argv[1]) : 0;
    Random rnd(20261014ULL+24*1000ULL+mode*100ULL+seed);
    int n=mode==1 ? rnd.uniform(1,4) : mode==3 ? 100 : rnd.uniform(20,100);
    int w=mode==1 ? rnd.uniform(0,15) : mode==3 ? 10000 : rnd.uniform(0,10000);
    vector<int> c(n); vector<long long> v(n);
    for(int i=0;i<n;++i) { c[i]=rnd.uniform(1,mode==1 ? 20 : 20000); v[i]=rnd.uniform(1LL,1000000000LL); }
    if(seed==1) { fill(c.begin(),c.end(),1); fill(v.begin(),v.end(),1000000000LL); }
    if(seed==2) fill(c.begin(),c.end(),20000);
    if(seed==3) { fill(c.begin(),c.end(),3); }
    if(seed==4) { w=0; fill(c.begin(),c.end(),2); }
    if(seed==5) { w=0; fill(c.begin(),c.end(),1); }
    if(mode==2 && seed==7) w=1000;
    if(mode==0) {
        static const vector<vector<int>> cs={{1},{2},{3},{3,2},{1,1,1},{20000},{7,2},{2,2},{5},{1}};
        static const vector<vector<long long>> vs={{7},{7},{10},{5,3},{1,9,3},{1000000000LL},{100,1},{5,6},{10},{1000000000LL}};
        static const int ws[]={0,0,1,5,0,10000,3,3,2,10000}; c=cs[seed]; v=vs[seed]; n=int(c.size()); w=ws[seed];
    }
    printf("%d %d\n",n,w); for(int i=0;i<n;++i) printf("%d %lld\n",c[i],v[i]);
    return 0;
}
