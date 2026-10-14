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
    Random rnd(20261014ULL+26*1000ULL+mode*100ULL+seed);
    int n=mode==1 ? rnd.uniform(1,4) : mode==3 ? 200 : rnd.uniform(30,200);
    int w=mode==1 ? rnd.uniform(0,15) : mode==3 ? 20000 : rnd.uniform(0,20000);
    vector<int> f(n),c(n); vector<long long> v(n);
    for(int i=0;i<n;++i) { f[i]=rnd.uniform(0,mode==1 ? 20 : 20000); c[i]=rnd.uniform(1,mode==1 ? 15 : 20000); v[i]=rnd.uniform(1LL,1000000000LL); }
    if(seed==1) { fill(f.begin(),f.end(),0); fill(c.begin(),c.end(),1); fill(v.begin(),v.end(),1000000000LL); }
    if(seed==2) { fill(f.begin(),f.end(),1); fill(c.begin(),c.end(),1); }
    if(seed==3) { fill(f.begin(),f.end(),20000); fill(c.begin(),c.end(),20000); }
    if(seed==4) { fill(f.begin(),f.end(),0); for(int &value:c) value=rnd.uniform(1,10); }
    if(seed==5) w=0;
    if(mode==2 && seed==7) w=2000;
    if(mode==0) {
        static const vector<vector<int>> fs={{0},{1},{4},{4,0},{1},{0,0},{20000},{2,2},{0},{3,0}};
        static const vector<vector<int>> cs={{1},{1},{1},{2,3},{2},{2,3},{1},{1,1},{1},{2,5}};
        static const vector<vector<long long>> vs={{7},{7},{10},{5,4},{5},{5,8},{1000000000LL},{3,5},{1000000000LL},{7,12}};
        static const int ws[]={0,1,3,10,7,10,20000,8,20000,12};
        f=fs[seed]; c=cs[seed]; v=vs[seed]; n=int(f.size()); w=ws[seed];
    }
    printf("%d %d\n",n,w); for(int i=0;i<n;++i) printf("%d %d %lld\n",f[i],c[i],v[i]);
    return 0;
}
