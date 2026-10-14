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
    Random rnd(20261007ULL+17*1000ULL+mode*100ULL+seed);
    int n=mode==1 ? rnd.uniform(1,16) : mode==3 ? 200 : rnd.uniform(30,200);
    int cap=mode==1 ? rnd.uniform(0,40) : mode==3 ? 20000 : rnd.uniform(0,20000);
    vector<int> w(n); vector<long long> v(n);
    for(int i=0;i<n;++i) { w[i]=rnd.uniform(1,mode==1 ? 60 : 40000); v[i]=rnd.uniform(1LL,1000000000LL); }
    if(seed==0) { cap=0; fill(w.begin(),w.end(),1); }
    if(seed==1) { fill(w.begin(),w.end(),1); fill(v.begin(),v.end(),1000000000LL); }
    if(seed==2) { fill(w.begin(),w.end(),40000); }
    if(seed==3) { fill(w.begin(),w.end(),2); }
    if(seed==4) { cap=0; fill(w.begin(),w.end(),2); }
    if(seed==5) { w[0]=min(40000,2*cap+1); v[0]=1000000000LL; }
    if(mode==2 && seed==7) cap=2000;
    if(mode==0) {
        static const vector<vector<int>> ws={{1},{2},{3},{5},{6,4,2},{1,1,1},{3,3},{40000},{2,2},{7,1}};
        static const vector<vector<long long>> vs={{7},{7},{8},{10},{10,8,5},{1,5,3},{5,6},{1000000000LL},{1000000000LL,1000000000LL},{100,1}};
        static const int caps[]={0,0,1,2,5,1,3,20000,3,3};
        w=ws[seed]; v=vs[seed]; n=int(w.size()); cap=caps[seed];
    }
    printf("%d %d\n",n,cap); for(int i=0;i<n;++i) printf("%d %lld\n",w[i],v[i]);
    return 0;
}
