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
    Random rnd(20261007ULL+14*1000ULL+mode*100ULL+seed);
    int n=mode==1 ? rnd.uniform(2,16) : mode==3 ? 60 : rnd.uniform(20,60);
    int sum=mode==1 ? rnd.uniform(n,100) : mode==3 ? 6000 : rnd.uniform(n,6000);
    vector<int> a=rnd.gen_sum(sum,n);
    if(seed==1) fill(a.begin(),a.end(),mode==3 ? 100 : 1);
    if(seed==2) { fill(a.begin(),a.end(),1); a[0]=sum-n+1; }
    if(seed==3 && n%2==0) { a.pop_back(); --n; }
    if(mode==2 && seed==7) a=rnd.gen_sum(600,n);
    if(mode==0) {
        static const vector<vector<int>> v={{1,1},{1,5999},{1,2,3},{1,1,100},{1,2,3,4,10},{5,5,5,5},{2,2,2,2,2},{1,1,1,1,1,100},{1,2,4,8,16,32},{10,11,12,13,14,15,16}};
        a=v[seed]; n=int(a.size());
    }
    printf("%d\n",n); emit(a);
    return 0;
}
