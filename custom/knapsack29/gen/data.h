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
    Random rnd(20261014ULL+29*1000ULL+mode*100ULL+seed);
    int n=mode==1 ? rnd.uniform(1,4) : mode==3 ? 50 : rnd.uniform(10,50);
    int q=mode==1 ? 10 : mode==3 ? 100000 : 2000;
    vector<int> a(n); for(int &v:a) v=rnd.uniform(mode==3 ? 5000 : 1,mode==1 ? 20 : 1000000);
    a[0]=mode==1 ? rnd.uniform(1,10) : mode==3 ? 5000 : rnd.uniform(1,5000);
    if(mode==3) a.back()=1000000;
    if(seed==1) { for(int &v:a) { v=2*(v/2); if(v==0) v=2; } }
    if(seed==2) a[0]=1;
    if(seed==3) fill(a.begin(),a.end(),mode==1 ? 7 : 5000);
    if(seed==4) { fill(a.begin(),a.end(),1000000); a[0]=mode==1 ? 5 : 5000; }
    if(seed==5) { fill(a.begin(),a.end(),mode==1 ? 6 : 5001); a[0]=mode==1 ? 5 : 5000; }
    if(mode==2 && seed==7) a[0]=100;
    vector<long long> queries(q);
    for(int i=0;i<q;++i) queries[i]=mode==1 ? rnd.uniform(0LL,100LL) : i%2 ? rnd.uniform(0LL,30000000LL) : rnd.uniform(0LL,1000000000000000000LL);
    queries[0]=0;
    if(mode!=1) queries[1]=1000000000000000000LL;
    if(mode==0) {
        static const vector<vector<int>> as={{1},{4},{4,6},{4,7},{6,10},{5000,5001},{2,4},{1,1000000},{5000},{5000,1000000}};
        static const vector<vector<long long>> xs={{0,1,1000000000000000000LL},{0,1,4,8,1000000000000000000LL},{0,2,4,6,8,10},{0,5,8,11,13,21},{12,14,16,999999999999999999LL},{24994999,24995000,1000000000000000000LL},{1,2,3,4,999999999999999999LL},{0,1,999999999999999999LL},{0,4999,5000,1000000000000000000LL},{0,5000,1000000,999999999999999999LL}};
        a=as[seed]; queries=xs[seed]; n=int(a.size()); q=int(queries.size());
    }
    printf("%d %d\n",n,q); emit(a); for(long long x:queries) printf("%lld\n",x);
    return 0;
}
