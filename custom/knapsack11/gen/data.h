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
    Random rnd(20261007ULL+11*1000ULL+mode*100ULL+seed);
    int n=mode==1 ? rnd.uniform(1,16) : mode==3 ? 200 : rnd.uniform(30,200);
    int sum=mode==1 ? rnd.uniform(n,100) : mode==3 ? 20000 : rnd.uniform(n,20000);
    vector<int> a=rnd.gen_sum(sum,n);
    if(seed==1) fill(a.begin(),a.end(),mode==3 ? 100 : 1);
    if(seed==2) { fill(a.begin(),a.end(),1); a[0]=sum-n+1; }
    if(seed==3) { fill(a.begin(),a.end(),2); a[0]=3; }
    if(mode==2 && seed==7) a=rnd.gen_sum(2000,n);
    if(mode==0) {
        static const vector<vector<int>> v={{1},{20000},{1,1},{1,2},{1,1,10},{2,3,7,8},{3,3,3},{7,7,7,7},{1,2,4,8,16},{9999,10001}};
        a=v[seed]; n=int(a.size());
    }
    printf("%d\n",n); emit(a);
    return 0;
}
