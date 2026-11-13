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

int m=inf.readInt(1,K_MAX,"m");inf.readSpace();inf.readInt(0,N_MAX,"A");inf.readSpace();inf.readInt(0,N_MAX,"B");inf.readSpace();inf.readInt(0,m,"K");inf.readEoln();
for(int i=0;i<m;++i){inf.readInt(1,5,"a");inf.readSpace();inf.readInt(1,5,"b");inf.readEoln();}
inf.readEof();
}
