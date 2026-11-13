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
int k=inf.readInt(1,K_MAX,"k");inf.readEoln();
for(int i=0;i<k;++i){if(i)inf.readSpace();inf.readInt(1,N_MAX,"length");}inf.readEoln();
for(size_t i=0;i<s.size();++i){if(i)inf.readSpace();inf.readLong(0,1000000000LL,"weight");}inf.readEoln();
inf.readEof();
}
