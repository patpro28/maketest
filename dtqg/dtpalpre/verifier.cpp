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
int k=inf.readInt(1,K_MAX,"k");inf.readSpace();int e=inf.readInt(0,k*(k-1),"e");inf.readEoln();
for(int i=0;i<k;++i){if(i)inf.readSpace();inf.readInt(1,N_MAX,"length");}inf.readEoln();
set<pair<int,int>> edges;
for(int i=0;i<e;++i){int u=inf.readInt(1,k,"u");inf.readSpace();int v=inf.readInt(1,k,"v");ensuref(u!=v && edges.insert({u,v}).second,"Invalid or duplicate edge");inf.readEoln();}
inf.readEof();
}
