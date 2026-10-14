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
    Random rnd(20261014ULL+23*1000ULL+mode*100ULL+seed);
    int n=mode==1 ? rnd.uniform(1,4) : mode==3 ? 100 : rnd.uniform(20,100);
    int k=mode==1 ? rnd.uniform(0,15) : mode==3 ? 20000 : rnd.uniform(0,20000);
    vector<int> b(n); vector<long long> v(n);
    for(int i=0;i<n;++i) { b[i]=rnd.uniform(1,mode==1 ? 20 : 1000); v[i]=rnd.uniform(1LL,1000000000LL); }
    if(seed==1) { fill(b.begin(),b.end(),1); fill(v.begin(),v.end(),1000000000LL); }
    if(seed==2) fill(b.begin(),b.end(),mode==1 ? 20 : 1000);
    if(seed==3) { for(int i=0;i<n;++i) b[i]=i%2 ? 1 : 2; }
    if(seed==4) { b[0]=1; v[0]=1; }
    if(seed==5) k=0;
    if(mode==2 && seed==7) for(int &value:b) value=rnd.uniform(1,100);
    if(mode==0) {
        static const vector<vector<int>> bs={{1},{1},{2},{1,2},{3,5},{1000},{2,2},{1,1000},{7},{1}};
        static const vector<vector<long long>> vs={{10},{1000000000LL},{7},{3,7},{4,10},{9},{7,1},{1,1000000000LL},{11},{1000000000LL}};
        static const int ks[]={0,20000,1,4,10,1,4,20,5,1}; b=bs[seed]; v=vs[seed]; n=int(b.size()); k=ks[seed];
    }
    printf("%d %d\n",n,k); for(int i=0;i<n;++i) printf("%d %lld\n",b[i],v[i]);
    return 0;
}
