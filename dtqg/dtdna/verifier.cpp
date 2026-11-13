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
string a=inf.readToken("[ADGT]+","A");inf.readEoln();string b=inf.readToken("[ADGT]+","B");inf.readEoln();ensuref(a.size()==b.size() && a.size()<=N_MAX,"Invalid lengths");
inf.readEof();
}
