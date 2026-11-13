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
for(int i=0;i<3;++i){string s=inf.readToken("[0-9*]+","pattern");ensuref(1<=s.size() && s.size()<=N_MAX,"Pattern too long");inf.readEoln();}
inf.readEof();
}
