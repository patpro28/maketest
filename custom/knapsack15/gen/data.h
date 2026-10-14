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
    Random rnd(20261007ULL+15*1000ULL+mode*100ULL+seed);
    int n=mode==1 ? rnd.uniform(1,20) : mode==3 ? 10000 : rnd.uniform(100,10000);
    vector<int> c(10); for(int &v:c) v=rnd.uniform(1,mode==1 ? 25 : 10000);
    if(seed==0) fill(c.begin(),c.end(),1);
    if(seed==1) { fill(c.begin(),c.end(),3); n=mode==3 ? 10000 : n; }
    if(seed==2) { fill(c.begin(),c.end(),2); c[0]=1; }
    if(seed==3) { fill(c.begin(),c.end(),10000); c[0]=1; }
    if(seed==4) { fill(c.begin(),c.end(),7); c[9]=3; }
    if(seed==5) { fill(c.begin(),c.end(),2); if(n%2==0) --n; }
    if(mode==2 && seed==6) for(int &v:c) v=rnd.uniform(1,20);
    if(mode==3 && seed==5) { n=10000; c={2,3,4,5,7,9,11,13,17,19}; }
    if(mode==2 && seed==7) fill(c.begin(),c.end(),7);
    if(mode==0) {
        static const vector<vector<int>> costs={{1,2,2,2,2,2,2,2,2,2},{1,2,2,2,2,2,2,2,2,2},{1,2,2,2,2,2,2,2,2,2},{1,5,5,5,5,5,5,5,5,5},{2,2,2,2,2,2,2,2,2,2},{2,2,2,2,2,2,2,2,2,2},{1,2,3,4,5,6,7,8,9,10},{2,3,4,4,4,4,4,4,4,4},{4,4,4,4,4,4,4,4,4,3},{5,5,5,5,5,5,5,5,5,5}};
        static const int budgets[]={1,2,3,3,3,4,5,7,6,5}; c=costs[seed]; n=budgets[seed];
    }
    printf("%d\n",n); emit(c);
    return 0;
}
