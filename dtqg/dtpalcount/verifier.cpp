#include "testlib.h"
#include "params.h"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;
int main(int argc,char**argv){
registerValidation(argc,argv);

string s=inf.readToken("[a-z]+","S");ensuref(s.size()<=N_MAX,"S too long");inf.readEoln();
int d=inf.readInt(1,3,"d");inf.readEoln();set<int> lengths;
for(int i=0;i<d;++i){int l=inf.readInt(1,N_MAX,"length");ensuref(lengths.insert(l).second,"Duplicate length");inf.readSpace();inf.readInt(1,20,"count");inf.readEoln();}
inf.readEof();
}
