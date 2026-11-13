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
string s=inf.readToken("[()]+","S");ensuref(2<=s.size() && s.size()<=N_MAX,"Invalid string length");inf.readEoln();inf.readInt(1,s.size()/2,"k");inf.readEoln();
inf.readEof();
}
