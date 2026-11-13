#include "testlib.h"
#include "params.h"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
int main(int argc,char**argv){
registerValidation(argc,argv);
int n=inf.readInt(2,N_MAX,"n");inf.readEoln();int px=0,py=0;
for(int i=0;i<n;++i){int x=inf.readInt(-N_MAX,N_MAX,"x");inf.readSpace();int y=inf.readInt(-N_MAX,N_MAX,"y");inf.readEoln();
if(i==0)ensuref(x==0 && y==0,"Start must be the origin");else ensuref(abs(x-px)+abs(y-py)==1,"Non-adjacent points");px=x;py=y;}
inf.readEof();
}
