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
    Random rnd(20261014ULL+22*1000ULL+mode*100ULL+seed);
    int n=mode==1 ? rnd.uniform(1,4) : mode==3 ? 40 : rnd.uniform(10,40);
    int k=mode==1 ? rnd.uniform(1,5) : mode==3 ? 40 : rnd.uniform(1,40);
    int t=rnd.uniform(1,50); vector<int> a(n); for(int &v:a) v=rnd.uniform(1,50);
    if(seed==1) { t=50; fill(a.begin(),a.end(),50); }
    if(seed==2) { t=1; fill(a.begin(),a.end(),50); }
    if(seed==3) { t=25; for(int i=0;i<n;++i) a[i]=i%2 ? 26 : 24; }
    if(seed==4) { t=1; fill(a.begin(),a.end(),1); }
    if(seed==5) { t=50; fill(a.begin(),a.end(),1); a[0]=50; }
    if(mode==2 && seed==7) k=10;
    if(mode==0) {
        static const vector<vector<int>> as={{2},{2},{1,2,3},{1,3},{2,2},{1,50},{1,2,3},{1,3},{50,50,50},{1,1,1}};
        static const int ks[]={1,4,3,3,4,2,1,4,40,40}; static const int ts[]={2,3,2,2,2,25,2,2,50,1};
        a=as[seed]; n=int(a.size()); k=ks[seed]; t=ts[seed];
    }
    printf("%d %d %d\n",n,k,t); emit(a);
    return 0;
}
