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
    Random rnd(20261014ULL+28*1000ULL+mode*100ULL+seed);
    int b=mode==1 ? rnd.uniform(1,8) : mode==3 ? 2000 : rnd.uniform(50,2000);
    int m=rnd.uniform(1,50); vector<int> c(10); for(int &v:c) v=rnd.uniform(1,mode==1 ? 10 : 20);
    if(seed==1) { m=1; fill(c.begin(),c.end(),1); }
    if(seed==2) { m=7; fill(c.begin(),c.end(),2); c[0]=1; }
    if(seed==3) { fill(c.begin(),c.end(),3); }
    if(seed==4) { fill(c.begin(),c.end(),2000); c[0]=1; }
    if(mode==3 && seed==0) { m=50; fill(c.begin(),c.end(),1); }
    if(mode==3 && seed==5) { m=50; c[9]=1; }
    if(mode==2 && seed==7) m=1;
    if(mode==0) {
        static const vector<vector<int>> cs={{1,2,2,2,2,2,2,2,2,2},{1,2,2,2,2,2,2,2,2,2},{1,2,2,2,2,2,2,2,2,2},{2,2,2,2,2,2,2,2,2,2},{1,2,3,4,5,6,7,8,9,10},{1,2,2,2,2,2,2,2,2,2},{1,5,5,5,5,5,5,5,5,5},{3,3,3,3,3,3,3,3,3,3},{2000,2000,2000,2000,2000,2000,2000,2000,2000,2000},{1,1,1,1,1,1,1,1,1,1}};
        static const int bs[]={1,4,3,3,5,5,3,6,2000,10},ms[]={50,2,7,2,3,1,1,7,50,1}; c=cs[seed]; b=bs[seed]; m=ms[seed];
    }
    printf("%d %d\n",b,m); emit(c);
    return 0;
}
