#pragma once
#include <algorithm>
#include <array>
#include <cstdio>
#include <functional>
#include <numeric>
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
    Random rnd(20261007ULL+19*1000ULL+mode*100ULL+seed);
    int n=mode==1 ? rnd.uniform(1,16) : mode==3 ? 200 : rnd.uniform(30,200);
    int budget=mode==1 ? rnd.uniform(0,40) : mode==3 ? 500 : rnd.uniform(0,500);
    vector<int> p(n),c(n); vector<long long> v(n);
    for(int i=0;i<n;++i) { p[i]=i ? rnd.uniform(1,i) : 0; c[i]=rnd.uniform(1,mode==1 ? 20 : 30); v[i]=rnd.uniform(1LL,1000000000LL); }
    if(seed==0) { for(int i=1;i<n;++i) p[i]=i; fill(c.begin(),c.end(),1); fill(v.begin(),v.end(),1000000000LL); }
    if(seed==1) { for(int i=1;i<n;++i) p[i]=1; fill(c.begin(),c.end(),1); }
    if(seed==2) { for(int i=1;i<n;++i) p[i]=(i+1)/2; fill(c.begin(),c.end(),1); }
    if(seed==3) c[0]=500;
    if(seed==4) { fill(c.begin(),c.end(),2); c[0]=1; }
    if(seed==5) { budget=0; }
    if(mode==3 && (seed==1 || seed==2)) { for(int &cost:c) cost=rnd.uniform(1,10); c[0]=1; }
    if(mode==2 && seed==7) { for(int j=1;j<n;++j) p[j]=j; fill(c.begin(),c.end(),1); }
    if(mode==0) {
        static const vector<vector<int>> ps={{0},{0},{0,1},{0,1,1,2},{0,1,2},{0,1,1},{0,1,1},{0,1,2,3},{0,1},{0,1,1,2,2}};
        static const vector<vector<int>> cs={{1},{1},{2,1},{2,2,3,1},{1,1,1},{5,1,1},{1,2,2},{1,1,1,1},{500,1},{1,1,2,3,1}};
        static const vector<vector<long long>> vs={{1},{1},{1,100},{3,6,10,5},{1,2,100},{1,100,100},{1,10,9},{1000000000LL,1000000000LL,1000000000LL,1000000000LL},{1,1000000000LL},{1,2,4,8,16}};
        static const int bs[]={0,1,1,5,2,5,3,4,500,4};
        p=ps[seed]; c=cs[seed]; v=vs[seed]; n=int(p.size()); budget=bs[seed];
    }
    printf("%d %d\n",n,budget); for(int i=0;i<n;++i) printf("%d %d %lld\n",p[i],c[i],v[i]);
    return 0;
}
